#ifndef RECOMENDADOR_H
#define RECOMENDADOR_H

#include <glib.h>
#include <stdio.h>

/**
 * @file recomendador.h
 * @brief Declarações de funções para criação de matriz de géneros, cálculo de similaridade e recomendação de utilizadores.
 *
 * Este cabeçalho contém as funções para criar uma matriz que relaciona utilizadores aos géneros musicais que ouviram,
 * calcular a similaridade entre dois utilizadores e recomendar utilizadores com gostos semelhantes.
 */

/**
 * @brief Cria uma matriz que mapeia utilizadores para géneros musicais e suas contagens.
 * 
 * A matriz será representada por uma tabela de hash onde:
 * - A chave é o `username` do utilizador.
 * - O valor é uma tabela de hash que mapeia géneros musicais para o número de vezes que o utilizador ouviu músicas desse género.
 *
 * @return Um ponteiro para a tabela de hash representando a matriz de utilizadores e géneros.
 *
 * @note O chamador é responsável por liberar a memória da matriz usando `g_hash_table_destroy`.
 */
GHashTable* criar_matriz_utilizadores_generos();

/**
 * @brief Calcula a similaridade entre dois utilizadores com base em suas tabelas de géneros.
 * 
 * A similaridade é definida como a soma das interseções de contagens de géneros entre os dois utilizadores.
 *
 * @param generos_target A tabela de géneros do utilizador alvo.
 * @param generos_outro A tabela de géneros de outro utilizador.
 * @return Um valor inteiro representando a similaridade calculada.
 */
gint calcular_similaridade(GHashTable *generos_target, GHashTable *generos_outro);

/**
 * @brief Recomenda utilizadores semelhantes a um dado utilizador.
 * 
 * Esta função identifica os utilizadores mais semelhantes ao utilizador especificado com base na matriz de géneros
 * e escreve os resultados no arquivo de saída fornecido.
 * 
 * @param username O nome de utilizador para o qual as recomendações serão geradas.
 * @param nr_utilizadores O número de utilizadores semelhantes a retornar.
 * @param output_file O arquivo onde os utilizadores recomendados serão escritos.
 *
 * @note A matriz de géneros é criada internamente e liberada após o uso.
 * Caso o utilizador especificado não seja encontrado, uma mensagem é escrita no arquivo de saída.
 */
void recomendar_utilizadores(const gchar *username, gint nr_utilizadores, FILE *output_file);

#endif // RECOMENDADOR_H
