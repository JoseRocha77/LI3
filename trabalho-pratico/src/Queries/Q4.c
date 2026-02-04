#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <time.h>
#include "Queries/Q4.h"
#include "Entidades/artists.h"
#include "Entidades/musics.h"
#include "Entidades/history.h"
#include "HashParser/hash.h"
#include "Utilitarias/utilitarias.h"

#define MAX_TOP 10

extern GHashTable *tabela_history;
extern GHashTable *tabela_artistas;
extern GHashTable *tabela_musicas;

typedef struct _ArtistPlaytime {
    char *artist_id;
    int playtime;
};

gint compare_playtime_desc(gconstpointer a, gconstpointer b) {
    const ArtistPlaytime *artist_a = (const ArtistPlaytime *)a;
    const ArtistPlaytime *artist_b = (const ArtistPlaytime *)b;

    if (artist_a->playtime > artist_b->playtime) {
        return -1;  // a vem antes de b
    } else if (artist_a->playtime < artist_b->playtime) {
        return 1;   // b vem antes de a
    }
    return 0;       // a e b são iguais
}


#define MAX_DATE_LENGTH 11 // Formato "YYYY/MM/DD"
char *calcular_inicio_da_semana(const char *timestamp, const char *inicio_semana) {
    struct tm tm_inicio = {0}, tm_timestamp = {0};
    time_t time_inicio, time_ts;

    // Converter strings para struct tm
    if (!strptime(inicio_semana, "%Y/%m/%d", &tm_inicio)) {
        fprintf(stderr, "Erro ao converter inicio_semana para struct tm: %s\n", inicio_semana);
        return NULL;
    }

    if (!strptime(timestamp, "%Y/%m/%d %H:%M:%S", &tm_timestamp)) {
        fprintf(stderr, "Erro ao converter timestamp para struct tm: %s\n", timestamp);
        return NULL;
    }

    // Transformar struct tm em time_t
    time_inicio = mktime(&tm_inicio);
    time_ts = mktime(&tm_timestamp);

    if (time_inicio == -1 || time_ts == -1) {
        fprintf(stderr, "Erro ao calcular time_t (time_inicio=%ld, time_ts=%ld).\n", time_inicio, time_ts);
        return NULL;
    }

    // Ajustar início da semana parcial com base no `inicio_semana`
    struct tm *tm_adjusted = localtime(&time_ts);

    // Calcular a diferença entre `inicio_semana` e o dia do `timestamp`
    double diff_days = difftime(time_ts, time_inicio) / (60 * 60 * 24);

    if (diff_days < 0) {
        fprintf(stderr, "O timestamp é anterior ao início da semana: %s\n", timestamp);
        return NULL;
    }

    // Verificar se estamos na mesma semana parcial
    int days_to_next_saturday = 6 - tm_inicio.tm_wday; // Dias até o próximo sábado
    if ((int)diff_days <= days_to_next_saturday) {
        // Estamos na mesma semana parcial iniciada por `inicio_semana`
        char *result = (char *)malloc(MAX_DATE_LENGTH * sizeof(char));
        if (result == NULL) {
            fprintf(stderr, "Erro ao alocar memória para a string de data.\n");
            return NULL;
        }

        if (strftime(result, MAX_DATE_LENGTH, "%Y/%m/%d", localtime(&time_inicio)) == 0) {
            fprintf(stderr, "Erro ao formatar a data.\n");
            free(result);
            return NULL;
        }

        return result; // Retorna o início da semana parcial
    }

    // Caso contrário, avançar para a semana correspondente
    int weeks_offset = ((int)diff_days - days_to_next_saturday) / 7;
    time_inicio += weeks_offset * 7 * 24 * 60 * 60;

    char *result = (char *)malloc(MAX_DATE_LENGTH * sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a string de data.\n");
        return NULL;
    }

    if (strftime(result, MAX_DATE_LENGTH, "%Y/%m/%d", localtime(&time_inicio)) == 0) {
        fprintf(stderr, "Erro ao formatar a data.\n");
        free(result);
        return NULL;
    }

    return result;
}


// Função que chama calcular_inicio_da_semana e retorna uma chave
char *obter_chave_semana(const char *timestamp, const char *inicio_semana) {
    return calcular_inicio_da_semana(timestamp, inicio_semana);
}


int data_esta_no_intervalo(const char *data, const char *begin_date, const char *end_date) {
    return (!begin_date || strcmp(data, begin_date) >= 0) && (!end_date || strcmp(data, end_date) <= 0);
}

void atualizar_tempo_reproducao(GHashTable *playtime_table, const char *artist_id, int duration) {
    if (!artist_id || strcmp(artist_id, "") == 0) {
        printf("Erro: artist_id inválido em atualizar_tempo_reproducao.\n");
        return;
    }

    if (!playtime_table) {
        printf("Erro: tabela de tempo não inicializada.\n");
        return;
    }

    int *current_playtime = g_hash_table_lookup(playtime_table, artist_id);
    if (!current_playtime) {
        current_playtime = malloc(sizeof(int));
        *current_playtime = 0;
        g_hash_table_insert(playtime_table, g_strdup(artist_id), current_playtime);
    }
    *current_playtime += duration;
}

GHashTable *agrupar_tempo_por_semana(const char *begin_date, const char *end_date) {
    printf("Iniciando agrupar_tempo_por_semana com begin_date=%s, end_date=%s\n", begin_date, end_date);
    if (tabela_history == NULL) {
        printf("Erro: tabela_history está vazia ou não inicializada.\n");
        return NULL;
    }

    GHashTable *weekly_playtime = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)g_hash_table_destroy);
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, tabela_history);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        //printf("Processando registro com chave=%s\n", (char *)key);

        History *record = (History *)value;
        char *timestamp = get_timestamp(record);
        //printf("Timestamp do registro: %s\n", timestamp);

        if (!data_esta_no_intervalo(timestamp, begin_date, end_date)) {
            //printf("Timestamp fora do intervalo: %s\n", timestamp);
            continue;
        }

        char *week_key = obter_chave_semana(timestamp, begin_date);
        printf("Chave da semana gerada: %s\n", week_key);

        GHashTable *playtime_table = g_hash_table_lookup(weekly_playtime, week_key);
        if (!playtime_table) {
            //printf("Tabela de playtime para a semana %s não encontrada. Criando nova.\n", week_key);
            playtime_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free);
            g_hash_table_insert(weekly_playtime, g_strdup(week_key), playtime_table);
        }

        Music *music = buscar_musica(get_idmusic(record));
        if (!music) {
            printf("Erro: Música com ID %s não encontrada no registro.\n", get_idmusic(record));
            continue;
        }
        //printf("Música encontrada: ID=%s\n", get_idmusic(record));

        for (GList *l = get_idartistsm(music); l != NULL; l = l->next) {
            char *artist_id = (char *)l->data;
            int duration = converter_duracao_para_segundos(get_duration(record));
            //printf("Atualizando tempo de reprodução para artista %s com duração %d segundos.\n", artist_id, duration);
            atualizar_tempo_reproducao(playtime_table, artist_id, duration);
        }

        g_free(week_key);
    }

    printf("Número de semanas processadas: %u\n", g_hash_table_size(weekly_playtime));
    return weekly_playtime;
}

void calcular_top_10(GHashTable *weekly_playtime, GHashTable *artist_top_count) {
    GHashTableIter week_iter;
    gpointer week_key, playtime_table;
    g_hash_table_iter_init(&week_iter, weekly_playtime);

    while (g_hash_table_iter_next(&week_iter, &week_key, &playtime_table)) {
        GHashTable *artists_playtime = (GHashTable *)playtime_table;

        GList *sorted_artists = NULL;
        GHashTableIter artist_iter;
        gpointer artist_id, playtime;
        g_hash_table_iter_init(&artist_iter, artists_playtime);

        //printf("Semana: %s\n", (char *)week_key);  // DEBUG: Semana atual sendo processada

        while (g_hash_table_iter_next(&artist_iter, &artist_id, &playtime)) {
            ArtistPlaytime *ap = malloc(sizeof(ArtistPlaytime));
            ap->artist_id = g_strdup((char *)artist_id);
            ap->playtime = *(int *)playtime;

            sorted_artists = g_list_insert_sorted_with_data(sorted_artists, ap, (GCompareDataFunc)compare_playtime_desc, NULL);

            // DEBUG: Mostrar o tempo de reprodução do artista antes da ordenação
            //printf("Artista: %s, Playtime: %d\n", ap->artist_id, ap->playtime);
        }

        //printf("Artistas ordenados por playtime para a semana %s:\n", (char *)week_key);  // DEBUG
        for (GList *l = sorted_artists; l != NULL; l = l->next) {
            ArtistPlaytime *ap = (ArtistPlaytime *)l->data;
            //printf("  - Artista: %s, Playtime: %d\n", ap->artist_id, ap->playtime);
        }

        int rank = 0;
        for (GList *l = sorted_artists; l != NULL && rank < MAX_TOP; l = l->next, rank++) {
            ArtistPlaytime *ap = (ArtistPlaytime *)l->data;

            // DEBUG: Mostrar o artista no ranking
            //printf("Rank: %d, Artista: %s, Playtime: %d\n", rank + 1, ap->artist_id, ap->playtime);

            // Verifica e atualiza a contagem de semanas ou toques
            int *count = g_hash_table_lookup(artist_top_count, ap->artist_id);
            if (!count) {
                count = malloc(sizeof(int));
                *count = 0;
                g_hash_table_insert(artist_top_count, g_strdup(ap->artist_id), count);
            }
            (*count)++;

            // DEBUG: Mostrar a contagem atualizada do artista
            //printf("Artista: %s, Contagem de Top 10: %d\n", ap->artist_id, *count);

            // Libera memória
            g_free(ap->artist_id);
            free(ap);
        }

        g_list_free(sorted_artists);
    }
}


void query4(char *begin_date, char *end_date, FILE *output_file) {
    if (!begin_date) {
        begin_date = "1901/12/13";
    }
    if (!end_date) {
        end_date = "2038/01/19";
    }

    GHashTable *weekly_playtime = agrupar_tempo_por_semana(remove_aspas(begin_date), remove_aspas(end_date));
    GHashTable *artist_top_count = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free);

    //fprintf(stderr, "Begin Date: %s, End Date: %s\n", begin_date, end_date);


    calcular_top_10(weekly_playtime, artist_top_count);

    char *top_artist_id = NULL;
    int max_count = -1;

    GHashTableIter iter;
    gpointer artist_id, count;
    g_hash_table_iter_init(&iter, artist_top_count);

    while (g_hash_table_iter_next(&iter, &artist_id, &count)) {
        int artist_count = *(int *)count;

        // Diagnóstico: Verifica os valores de contagem para cada artista
        //printf("Artista: %s, Contagem: %d\n", (char *)artist_id, artist_count);

        if (artist_count > max_count || (max_count == artist_count && strcmp((char *)artist_id, top_artist_id) < 0)) {
            top_artist_id = (char *)artist_id;
            max_count = artist_count;
        }
    }

    if (top_artist_id) {
        Artist *artist = buscar_artista(top_artist_id);
        if (artist) {
            //printf("Top artista: %s, tipo: %s, contagem: %d\n", get_idartista(artist), get_type(artist), max_count);
            fprintf(output_file, "%s;%s;%d\n", get_idartista(artist), get_type(artist), max_count);
        }
    }

    g_hash_table_destroy(weekly_playtime);
    g_hash_table_destroy(artist_top_count);
}
