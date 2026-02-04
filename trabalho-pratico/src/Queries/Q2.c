#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Entidades/artists.h"
#include "Entidades/musics.h"
#include "HashParser/hash.h" 
#include "Validacoes/validation.h"
#include "Utilitarias/utilitarias.h"

// Função de comparação para ordenar os artistas por duração e ID
gint compare_artists(gconstpointer a, gconstpointer b, gpointer duracoes_totais) {
    const Artist *artistA = (const Artist *)a;
    const Artist *artistB = (const Artist *)b;

    const gchar *idA = get_idartista(artistA);
    const gchar *idB = get_idartista(artistB);

    gint duracaoA = GPOINTER_TO_INT(g_hash_table_lookup(duracoes_totais, idA));
    gint duracaoB = GPOINTER_TO_INT(g_hash_table_lookup(duracoes_totais, idB));

    if (duracaoA != duracaoB) return duracaoB - duracaoA;  // Ordem decrescente de duração
    return g_strcmp0(idA, idB); // Ordem crescente de ID
}

// Exibe os top N artistas com maior discografia
void output_artists(gint N, const gchar *country_filter, GHashTable *tabela_artistas, GHashTable *tabela_musicas, FILE *output_file) {

    if (N == 0) {
        fprintf(output_file, "\n");
        return;
    }

    GList *filtered_artists = NULL;
    GHashTable *duracoes_totais = g_hash_table_new(g_str_hash, g_str_equal);

    // Pré-calcula a duração total das músicas para cada artista e armazena em `duracoes_totais`
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, tabela_artistas);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Artist *artist = (Artist *)value;

        const gchar *country = get_country(artist);
        const gchar *idartista = get_idartista(artist);

        // Filtra por país, se especificado
        if (!country_filter || g_strcmp0(country, country_filter) == 0) {
            gint duracao_total = get_discografia(artist);
            g_hash_table_insert(duracoes_totais, (gpointer)idartista, GINT_TO_POINTER(duracao_total));
            filtered_artists = g_list_append(filtered_artists, artist);
        }
    }

    // Ordena os artistas por duração e ID usando as durações pré-calculadas
    filtered_artists = g_list_sort_with_data(filtered_artists, (GCompareDataFunc)compare_artists, duracoes_totais);

    for (GList *a = filtered_artists; a != NULL && N > 0; a = a->next, N--) {
        Artist *artist = (Artist *)a->data;

        const gchar *name = get_name(artist);
        const gchar *type = get_type(artist);
        const gchar *country = get_country(artist);
        const gchar *idartista = get_idartista(artist);

        gint duracao_total = GPOINTER_TO_INT(g_hash_table_lookup(duracoes_totais, idartista));
        gchar *duracao_formatada = converter_segundos_para_duracao(duracao_total);

        fprintf(output_file, "%s;%s;%s;%s\n", name, type, duracao_formatada, country);
        free(duracao_formatada);
    }

    // Libera memória
    g_list_free(filtered_artists);
    g_hash_table_destroy(duracoes_totais);
}

