#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashParser/hash.h"
#include "Entidades/users.h"
#include "Entidades/musics.h"

GHashTable* criar_matriz_utilizadores_generos() {
    GHashTable *matriz = g_hash_table_new_full(
        g_str_hash, g_str_equal, g_free, (GDestroyNotify)g_hash_table_destroy
    );

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, tabela_utilizadores);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        User *user = (User *)value;
        GHashTable *generos_count = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);

        for (GList *node = get_idsdasmusicaspreferidas(user); node != NULL; node = node->next) {
            gchar *idmusica = (gchar *)node->data;
            Music *musica = buscar_musica(idmusica);

            if (musica) {
                gchar *genero = get_genero_musica(musica);
                if (genero) {
                    gint *count = g_hash_table_lookup(generos_count, genero);

                    if (count) {
                        (*count)++;
                    } else {
                        gint *novo_count = g_new(gint, 1);
                        *novo_count = 1;
                        g_hash_table_insert(generos_count, g_strdup(genero), novo_count);
                    }
                }
            }
        }

        g_hash_table_insert(matriz, g_strdup(get_username(user)), generos_count);
    }

    return matriz;
}

gint calcular_similaridade(GHashTable *generos_target, GHashTable *generos_outro) {
    gint similaridade = 0;

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, generos_target);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        gint *target_count = (gint *)value;
        gint *outro_count = g_hash_table_lookup(generos_outro, key);

        if (outro_count) {
            similaridade += (*target_count < *outro_count ? *target_count : *outro_count);
        }
    }

    return similaridade;
}

typedef struct {
    gchar *username;
    gint similaridade;
} SimilaridadeEntry;

gint comparar_similaridades(const SimilaridadeEntry *a, const SimilaridadeEntry *b) {
    return b->similaridade - a->similaridade;
}

void recomendar_utilizadores(const gchar *username, gint nr_utilizadores, FILE *output_file) {
    GHashTable *matriz = criar_matriz_utilizadores_generos();
    GHashTable *target_user_generos = g_hash_table_lookup(matriz, username);

    if (!target_user_generos) {
        fprintf(output_file, "\n");
        g_hash_table_destroy(matriz);
        return;
    }

    GHashTableIter iter;
    gpointer key, value;
    GArray *resultados = g_array_new(FALSE, FALSE, sizeof(SimilaridadeEntry));

    g_hash_table_iter_init(&iter, matriz);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        gchar *outro_user = (gchar *)key;
        GHashTable *outro_generos = (GHashTable *)value;

        if (g_strcmp0(username, outro_user) == 0) continue;

        gint similaridade = calcular_similaridade(target_user_generos, outro_generos);
        SimilaridadeEntry entry = { g_strdup(outro_user), similaridade };
        g_array_append_val(resultados, entry);
    }

    g_array_sort(resultados, (GCompareFunc)comparar_similaridades);

    for (guint i = 0; i < nr_utilizadores && i < resultados->len; i++) {
        SimilaridadeEntry entry = g_array_index(resultados, SimilaridadeEntry, i);
        fprintf(output_file, "%s\n", entry.username);
        g_free(entry.username);
    }

    g_array_free(resultados, TRUE);
    g_hash_table_destroy(matriz);
}

