#include <glib.h>
#include <stdio.h>
#include <string.h>
#include "Queries/Q1.h"    
#include "Queries/Q2.h"
#include "Queries/Q3.h"
#include "Utilitarias/utilitarias.h"
#include "HashParser/hash.h" 

struct _GeneroLikes {
    gchar *genero;
    gint like_count;
};

void liberar_genero_aux(gpointer key, gpointer value, gpointer user_data) {
    (void)user_data; // Ignorado, não usado aqui
    g_free(key);     // Libera a chave (gênero)
    g_free(value);   // Libera o valor (contagem de likes)
}

// Função auxiliar para incrementar contagem de likes por genero na hash table
void incrementar_genero(GHashTable *tabela, const gchar *genero) {
    gint *count = (gint *)g_hash_table_lookup(tabela, genero);
    //printf("Verificando genero: %s\n", genero); 
    if (!count) {
        count = g_new(gint, 1);
        *count = 1;
        g_hash_table_insert(tabela, g_strdup(genero), count);
        //printf("Genero '%s' inserido na tabela com contagem inicial de 1.\n", genero); 
    } else {
        (*count)++;
        //printf("Genero '%s' já existe. Contagem incrementada para %d.\n", genero, *count); 
    }
}

// Função de comparação para ordenar gêneros por número de likes, ordem alfabetica como desempate
int comparar_likes(const void *a, const void *b) {
    GeneroLikes *g1 = (GeneroLikes *)a;
    GeneroLikes *g2 = (GeneroLikes *)b;
    int cmp = g2->like_count - g1->like_count;
    //printf("Comparando '%s' (%d likes) com '%s' (%d likes)\n", g1->genero, g1->like_count, g2->genero, g2->like_count); 
    return (cmp != 0) ? cmp : strcmp(g1->genero, g2->genero);
}

void querie3(int idade_min, int idade_max, FILE *output_file) {
    //printf("Iniciando função querie3 com faixa etária %d - %d.\n", idade_min, idade_max); 

    // Inicializar a hash table para armazenar contagem de likes por genero
    GHashTable *tabela_generos = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);

    //printf("Número de usuários na tabela: %d\n", g_hash_table_size(tabela_utilizadores));  

    // Itera sobre os usuarios e aplica o filtro da faixa etária
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, tabela_utilizadores);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        User *user = (User *)value;
        int idade = calcular_idade(get_datadenascimento(user));
        //printf("Calculando idade do usuário '%s': %d\n", get_username(user), idade);                                                  

        if (idade >= idade_min && idade <= idade_max) {
            //printf("Usuário '%s' dentro da faixa etária.\n", get_username(user)); // Debug

            for (GList *node = get_idsdasmusicaspreferidas(user); node; node = node->next) {
                gchar *musica_id = (gchar *)node->data;
                char *musica_id_tratada = tratar_lista_id(musica_id);

                // if (!musica_id_tratada || strlen(musica_id_tratada) == 0) {
                //     //printf("ID de música vazio ou inválido após limpeza: %s\n", musica_id);
                //     //g_free(musica_id_tratada); // Certifique-se de liberar a memória
                //     continue;
                // }

                //printf("Buscando música com ID: %s\n", musica_id_tratada);
                Music *musica = buscar_musica(musica_id_tratada);
                if (musica) {
                    incrementar_genero(tabela_generos, get_genero_musica(musica));
                } else {
                    //printf("Música com ID '%s' não encontrada.\n", musica_id_tratada);
                }

                free(musica_id_tratada); // Libere a memória após o uso
            }
        }
    }

    // Verificando a tabela de músicas
    //printf("Número de músicas na tabela: %d\n", g_hash_table_size(tabela_musicas));  
    GHashTableIter music_iter;
    g_hash_table_iter_init(&music_iter, tabela_musicas);
    while (g_hash_table_iter_next(&music_iter, &key, &value)) {
        //printf("Música na tabela: ID='%s', Gênero='%s'\n", (gchar *)key, ((Music *)value)->generomusica);  
    }

    // Preparação do array para ordenar gêneros por popularidade
    int num_generos = g_hash_table_size(tabela_generos);                                                                                
    //printf("Número de gêneros encontrados: %d\n", num_generos); 

    GeneroLikes *generos = g_new(GeneroLikes, num_generos);
    GHashTableIter genre_iter;
    gpointer genre_key, genre_value;
    int i = 0;
    g_hash_table_iter_init(&genre_iter, tabela_generos);

    while (g_hash_table_iter_next(&genre_iter, &genre_key, &genre_value)) {
        generos[i].genero = g_strdup((gchar *)genre_key);
        generos[i++].like_count = *(gint *)genre_value;
        //printf("Genero '%s' com %d likes adicionado ao array.\n", generos[i - 1].genero, generos[i - 1].like_count); 
    }

    qsort(generos, num_generos, sizeof(GeneroLikes), comparar_likes);

    // Se output_file é NULL, abre o arquivo padrão para escrita
    FILE *output = output_file ? output_file : fopen("resultados/command_output.txt", "w");
    if (output) {
        if (num_generos == 0) {
        // Caso não haja gêneros encontrados, escreve uma linha vazia no arquivo
        fprintf(output, "\n");
        } else {
            for (i = 0; i < num_generos; i++) {
            fprintf(output, "%s;%d\n", generos[i].genero, generos[i].like_count);
            g_free(generos[i].genero);  // Libera memória alocada para o nome do gênero
            }
        }
    //printf("Resultados escritos com sucesso.\n");
    } else {
    //printf("Erro ao abrir o arquivo de saída.\n");
    }

    g_free(generos);
    // Liberação da tabela_generos utilizando função auxiliar
    g_hash_table_foreach(tabela_generos, liberar_genero_aux, NULL);
    g_hash_table_destroy(tabela_generos);
}
