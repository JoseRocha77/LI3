#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Entidades/users.h"
#include "Entidades/history.h"
#include "Entidades/musics.h"
#include "Entidades/artists.h"
#include "Entidades/albuns.h"
#include "Utilitarias/utilitarias.h"
#include "Queries/Q6.h"
#include "HashParser/hash.h" 

struct _ArtistaInfo {
    gchar *id;
    gint duracao;
    gint num_musicas;
};

void liberar_artista_info(ArtistaInfo *artista_info) {
    if (artista_info == NULL) return;

    // Libera o campo 'id', se alocado dinamicamente
    if (artista_info->id != NULL) {
        g_free(artista_info->id);
        artista_info->id = NULL;  // Por segurança
    }

    // Libera a struct em si
    g_free(artista_info);
}

gint comparar_artistas(gconstpointer a, gconstpointer b) {
    const ArtistaInfo *artista_a = (const ArtistaInfo *)a;
    const ArtistaInfo *artista_b = (const ArtistaInfo *)b;

    // Ordena por tempo de audição em ordem decrescente
    if (artista_a->duracao != artista_b->duracao) {
        return artista_b->duracao - artista_a->duracao;
    }

    // Desempata por ID lexicograficamente
    return g_ascii_strcasecmp(artista_a->id, artista_b->id);
}


extern GHashTable *tabela_history; 

// Função para obter o histórico de um usuário
GList* get_historico(User *user) {
    if (!user) {
        printf("Usuário inválido.\n");
        return NULL;
    }

    GList *historico_usuario = NULL;
    gchar *user_id = get_username(user);

    //printf("Obtendo histórico para o usuário: %s\n", user_id);

    // Iterar sobre os históricos para filtrar pelo usuário
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, tabela_history);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        History *hist = (History *)value;
        //printf("Verificando histórico com ID de usuário: %s\n", get_iduser(hist));

        if (g_strcmp0(get_iduser(hist), user_id) == 0) {
            //printf("Adicionando ao histórico do usuário.\n");
            historico_usuario = g_list_append(historico_usuario, hist);
        }
    }
    return historico_usuario;
}

// Função para filtrar histórico por ano
GList* filtrar_historico_por_ano(GList *historico, gint ano) {
    GList *historico_filtrado = NULL;

    //printf("Filtrando histórico para o ano: %d\n", ano);

    for (GList *node = historico; node; node = node->next) {
        History *hist = (History *)node->data;
        const gchar *timestamp = get_timestamp(hist);

        if (timestamp) {
            gint ano_hist;
            sscanf(timestamp, "%4d", &ano_hist);
            //printf("Ano do histórico: %d\n", ano_hist);

            if (ano_hist == ano) {
                //printf("Adicionando histórico para o ano %d\n", ano);
                historico_filtrado = g_list_append(historico_filtrado, hist);
            }
        }
    }
    return historico_filtrado;
}

// Função para calcular o artista mais ouvido
gchar* calcular_artista_mais_ouvido(GHashTable *artistas) {
    GList *keys = g_hash_table_get_keys(artistas);
    gchar *artista_preferido = NULL;
    gint tempo_maximo = 0;

    for (GList *l = keys; l != NULL; l = l->next) {
        gchar *artista_id = (gchar *)l->data;
        ArtistaInfo *info = g_hash_table_lookup(artistas, artista_id);

        if (info->duracao > tempo_maximo || 
            (info->duracao == tempo_maximo && g_ascii_strcasecmp(artista_id, artista_preferido) < 0)) {
            if (artista_preferido) g_free(artista_preferido);
            artista_preferido = g_strdup(artista_id);
            tempo_maximo = info->duracao;
        }
    }

    g_list_free(keys); 
    return artista_preferido;
}


// Função para calcular o gênero mais ouvido
gchar* calcular_genero_mais_ouvido(GHashTable *generos) {
    //printf("DEBUG: Iniciando cálculo do gênero mais ouvido\n");
    GList *keys = g_hash_table_get_keys(generos);
    gchar *genero_preferido = NULL;
    gint max_count = 0;

    for (GList *l = keys; l != NULL; l = l->next) {
        gchar *genero = (gchar *)l->data;
        gint *count = g_hash_table_lookup(generos, genero);

        //printf("DEBUG: Gênero: %s, Contagem: %d\n", genero, count ? *count : 0);

        if (count && *count > max_count) {
            max_count = *count;
            genero_preferido = g_strdup(genero); 
        }
    }

    //printf("DEBUG: Gênero mais ouvido: %s, Contagem: %d\n", genero_preferido, max_count);
    g_list_free(keys);
    return genero_preferido;
}

// Função para calcular o álbum favorito
gchar* calcular_album_favorito(GHashTable *albuns) {
    //printf("DEBUG: Iniciando cálculo do álbum favorito\n");
    GList *keys = g_hash_table_get_keys(albuns);
    gchar *album_preferido = NULL;
    gint max_count = 0;

    for (GList *l = keys; l != NULL; l = l->next) {
        gchar *album_id = (gchar *)l->data;
        gint *count = g_hash_table_lookup(albuns, album_id);

        //printf("DEBUG: Álbum: %s, Contagem: %d\n", album_id, count ? *count : 0);

        if (count && *count > max_count) {
            max_count = *count;
            album_preferido = g_strdup(album_id);
        }
    }

    //printf("DEBUG: Álbum favorito: %s, Contagem: %d\n", album_preferido, max_count);
    g_list_free(keys);
    return album_preferido;
}


// Função para comparar duas datas no formato "YYYY/MM/DD" e retornar a mais recente
const gchar* obter_data_mais_recente(const gchar *data1, const gchar *data2) {
    if (!data1 || !data2) {
        printf("[ERRO] Uma ou ambas as datas são nulas.\n");
        return NULL;
    }

    // Dividir as strings de data em partes (ano, mês, dia)
    gint ano1, mes1, dia1;
    gint ano2, mes2, dia2;

    if (sscanf(data1, "%d/%d/%d", &ano1, &mes1, &dia1) != 3 ||
        sscanf(data2, "%d/%d/%d", &ano2, &mes2, &dia2) != 3) {
        printf("[ERRO] Formato de data inválido. Datas: '%s', '%s'\n", data1, data2);
        return NULL;
    }

    // Comparar ano, depois mês, e finalmente dia
    if (ano1 > ano2 || (ano1 == ano2 && mes1 > mes2) || (ano1 == ano2 && mes1 == mes2 && dia1 > dia2)) {
        return data1;
    } else {
        return data2;
    }
}

// Função para calcular o dia mais ativo 
gchar* calcular_dia_mais_ativo(GHashTable *dias) {
    //printf("[DEBUG] Iniciando cálculo do dia mais ativo\n");

    GList *keys = g_hash_table_get_keys(dias);
    //printf("[DEBUG] Conteúdo da tabela de dias:\n");
    for (GList *l = keys; l != NULL; l = l->next) {
        gchar *dia = (gchar *)l->data;
        gint *count = g_hash_table_lookup(dias, dia);
        if (count) {
            //printf("[DEBUG] Dia: %s, Contagem: %d\n", dia, *count);
        }
    }
    g_list_free(keys);

    // Agora, vamos continuar com o cálculo do dia mais ativo
    gchar *dia_mais_ativo = NULL;
    gint max_count = 0;

    // Iterando por todos os dias na hash table
    keys = g_hash_table_get_keys(dias);
    for (GList *l = keys; l != NULL; l = l->next) {
        gchar *dia = (gchar *)l->data;
        gint *count = g_hash_table_lookup(dias, dia);
        //printf("[DEBUG] Dia: %s, Contagem: %d\n", dia, count ? *count : 0);

        if (count) {
            // Se ainda não houver um "dia mais ativo", ou se a contagem for maior, ou se for o mesmo com data mais recente
            if (dia_mais_ativo == NULL || *count > max_count ||
                (*count == max_count && obter_data_mais_recente(dia, dia_mais_ativo) == dia)) {
                
                //printf("[DEBUG] Avaliando substituição: dia_mais_ativo=%s, novo_dia=%s\n", dia_mais_ativo ? dia_mais_ativo : "null", dia);

                if (dia_mais_ativo) {
                    g_free(dia_mais_ativo); 
                }
                dia_mais_ativo = g_strdup(dia);
                max_count = *count; 

                //printf("[DEBUG] Novo dia mais ativo: %s com %d audições.\n", dia_mais_ativo, max_count);
            }
        }
    }


    g_list_free(keys);
    //printf("[DEBUG] Dia mais ativo final: %s, Contagem: %d\n", dia_mais_ativo, max_count);
    return dia_mais_ativo;
}

// Função para calcular a hroa mais comum que o user ouviu a musica
gchar* calcular_hora_mais_comum(GHashTable *horas) {
    //printf("DEBUG: Iniciando cálculo da hora com maior tempo de audição\n");
    GList *keys = g_hash_table_get_keys(horas);
    gchar *hora_mais_comum = NULL;
    gint max_tempo = 0;

    for (GList *l = keys; l != NULL; l = l->next) {
        gchar *hora = (gchar *)l->data;
        gint *tempo = g_hash_table_lookup(horas, hora);

        //printf("DEBUG: Hora: %s, Tempo de audição acumulado: %d segundos\n", hora, tempo ? *tempo : 0);

        if (tempo && (*tempo > max_tempo || (*tempo == max_tempo && (!hora_mais_comum || g_ascii_strcasecmp(hora, hora_mais_comum) < 0)))) {
            max_tempo = *tempo;
            if (hora_mais_comum) g_free(hora_mais_comum);
            hora_mais_comum = g_strdup(hora);
        }
    }

    //printf("DEBUG: Hora com maior tempo de audição: %s, Tempo acumulado: %d segundos\n", hora_mais_comum ? hora_mais_comum : "N/A", max_tempo);
    g_list_free(keys); 
    return hora_mais_comum;
}


// Função para dar print da lista dos N artistas mais ouvidos peo user
void listar_top_artistas_utilizador(GHashTable *artistas, gint N, FILE *output_file) {
    if (!artistas || g_hash_table_size(artistas) == 0) {
        fprintf(output_file, "\n");
        return;
    }

    GList *artistas_lista = NULL;
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, artistas);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        ArtistaInfo *info = (ArtistaInfo *)value;
        artistas_lista = g_list_prepend(artistas_lista, info);
    }

    artistas_lista = g_list_sort(artistas_lista, (GCompareFunc)comparar_artistas);


    GList *node = artistas_lista;
    for (gint i = 0; i < N && node != NULL; i++, node = node->next) {
        ArtistaInfo *info = (ArtistaInfo *)node->data;
        gchar *tempo_formatado = converter_segundos_para_duracao(info->duracao);

        fprintf(output_file, "%s;%d;%s\n", info->id, info->num_musicas, tempo_formatado);
        g_free(tempo_formatado);
    }

    g_list_free(artistas_lista);
}



// Função princiapl da query 6 
void query6(const gchar *user_id, gint ano, gint N, FILE *output_file) {
    //printf("[INFO] Iniciando Query 6 para user_id: %s, ano: %d, N: %d\n", user_id, ano, N);
    
    int escreveu = 0;
    gchar *artista_preferido = NULL;
    gint tempo_maximo = 0;


    User *user = buscar_user(user_id);
    if (!user) {
        //printf("[ERRO] Usuário %s não encontrado ou sem histórico.\n", user_id);
        fprintf(output_file, "\n");
        return;
    }
    //printf("[INFO] Usuário %s encontrado. Carregando histórico completo...\n", user_id);

    GList *historico_completo = get_historico(user);
    GList *historico = filtrar_historico_por_ano(historico_completo, ano);
    if (!historico) {
        //printf("[ERRO] Nenhum histórico encontrado para o ano %d.\n", ano);
        fprintf(output_file, "\n");
        return;
    }
    //printf("[INFO] Histórico filtrado com sucesso. Iniciando processamento...\n");

    gint total_seconds = 0;
    GHashTable *musicas_distintas = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    GHashTable *artistas = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
    GHashTable *generos = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
    GHashTable *albuns = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
    GHashTable *dias = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);   
    GHashTable *horas = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);

    for (GList *node = historico; node != NULL; node = node->next) {
        History *entry = (History *)node->data;
        const gchar *musica_id = get_idmusic(entry);
        if (!musica_id) continue;

        Music *musica = buscar_musica(musica_id);
        if (!musica) continue;

        gint duracao = converter_duracao_para_segundos(get_duration(entry));
        total_seconds += duracao;

        g_hash_table_add(musicas_distintas, g_strdup(musica_id));

        GList *artistas_lista = get_idartistsm(musica);

        for (GList *node = artistas_lista; node != NULL; node = node->next) {
        gchar *artista_id = (gchar *)node->data;
        ArtistaInfo *info = g_hash_table_lookup(artistas, artista_id);

            if (!info) {
                info = g_new0(ArtistaInfo, 1);
                info->id = g_strdup(artista_id);
                info->duracao = 0;
                info->num_musicas = 0;
                g_hash_table_insert(artistas, g_strdup(artista_id), info);
            }

            info->duracao += duracao; 
            info->num_musicas++;

        }
                
        gchar *genero = get_genero_musica(musica);
        if (genero) {
            //printf("[INFO] Gênero encontrado: %s\n", genero);
            gint *genero_time = g_hash_table_lookup(generos, genero);
            if (!genero_time) {
                genero_time = g_new(gint, 1);
                *genero_time = 0;
                g_hash_table_insert(generos, g_strdup(genero), genero_time);
            }
            *genero_time += duracao;
        }

        gchar *album = get_idalbum(musica);
        if (album) {
            //printf("[INFO] Álbum encontrado: %s\n", album);
            gint *album_time = g_hash_table_lookup(albuns, album);
            if (!album_time) {
                album_time = g_new(gint, 1);
                *album_time = 0;
                g_hash_table_insert(albuns, g_strdup(album), album_time);
            }
            *album_time += duracao;
        }

        gchar *dia = get_dia_audicao(get_timestamp(entry));
        if (dia) {
            //printf("[DEBUG] Dia da audição extraído: %s\n", dia);

            gint *dia_count = g_hash_table_lookup(dias, dia);
            //printf("[DEBUG] Verificando dia %s na tabela. Contagem encontrada: %p\n", dia, dia_count);

            if (!dia_count) {
                // Novo dia, criar entrada na hash table
                dia_count = g_new(gint, 1);
                *dia_count = 1; // Inicializa contagem
                g_hash_table_insert(dias, g_strdup(dia), dia_count);
                //printf("[DEBUG] Novo dia inserido: %s com contagem inicial 1\n", dia);
            }else {
                (*dia_count)++;
                //printf("[DEBUG] Incrementando dia %s para %d\n", dia, *dia_count);
            }
            g_free(dia);
        } 

        gchar *hora = get_hora_audicao(get_timestamp(entry));
        if (hora) {
            //printf("[DEBUG] Hora extraída: %s\n", hora);

            gint *hora_time = g_hash_table_lookup(horas, hora);
            if (!hora_time) {
                hora_time = g_new(gint, 1);
                *hora_time = 0;
                g_hash_table_insert(horas, g_strdup(hora), hora_time);
                //printf("[DEBUG] Nova hora inserida: %s com tempo inicial %d segundos\n", hora, *hora_time);
            }

            *hora_time += duracao;
            //printf("[DEBUG] Hora: %s, Tempo acumulado: %d segundos\n", hora, *hora_time);
            g_free(hora);
        } 

    }

    //printf("[INFO] Processamento de músicas concluído. Calculando estatísticas...\n");

    gchar *tempo_total = converter_segundos_para_duracao(total_seconds);
    gint num_distinct_songs = g_hash_table_size(musicas_distintas);
    //printf("[RESUMO] Tempo total de audição: %s, Número de músicas distintas: %d\n", tempo_total, num_distinct_songs);

    artista_preferido = calcular_artista_mais_ouvido(artistas);
    gchar *genero_preferido = calcular_genero_mais_ouvido(generos);
    gchar *album_preferido = calcular_album_favorito(albuns);
    gchar *dia_mais_ativo = calcular_dia_mais_ativo(dias);
    gchar *hora_mais_comum = calcular_hora_mais_comum(horas);

    //printf("[RESUMO] Artista preferido: %s, Gênero preferido: %s, Álbum favorito: %s\n", artista_preferido, genero_preferido, album_preferido);

    //printf("[RESUMO] Dia mais ativo: %s, Hora mais comum: %s\n", dia_mais_ativo, hora_mais_comum);

    fprintf(output_file, "%s;%d;%s;%s;%s;%s;%s\n", tempo_total, num_distinct_songs, artista_preferido, dia_mais_ativo, genero_preferido, album_preferido, hora_mais_comum);
    escreveu = 1;

    // Lista os artistas mais ouvidos (se N > 0)
    if (N > 0) {
        listar_top_artistas_utilizador(artistas, N, output_file);
    }

    if (escreveu == 0) {
        fprintf(output_file, "\n");
    }

    //printf("[INFO] Liberação de memória iniciada...\n");
    g_free(tempo_total);
    g_free(artista_preferido);
    g_free(genero_preferido);
    g_free(album_preferido);
    g_free(dia_mais_ativo);
    g_free(hora_mais_comum);
    g_hash_table_destroy(musicas_distintas);
    g_hash_table_destroy(artistas);
    g_hash_table_destroy(generos);
    g_hash_table_destroy(albuns);
    g_hash_table_destroy(dias);
    g_hash_table_destroy(horas);
    g_list_free(historico);
    g_list_free(historico_completo);
    //printf("[INFO] Query 6 finalizada com sucesso.\n");
}
