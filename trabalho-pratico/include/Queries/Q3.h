#ifndef Q3_H
#define Q3_H

#include <glib.h>
#include <stdio.h>
#include <string.h>
#include "HashParser/hash.h"

/**
 * @brief Estrutura que representa um gênero musical e sua contagem de likes.
 */

typedef struct _GeneroLikes GeneroLikes;

/**
 * @brief Libera os recursos associados a uma tabela de gêneros musicais.
 * 
 * @param key Chave da tabela (nome do gênero).
 * @param value Valor da tabela (contagem de likes).
 * @param user_data Dados adicionais (não utilizados).
 */
void liberar_genero_aux(gpointer key, gpointer value, gpointer user_data);

/**
 * @brief Incrementa a contagem de likes de um gênero musical em uma tabela de hash.
 * 
 * @param tabela Tabela de hash contendo as contagens de likes por gênero.
 * @param genero Nome do gênero musical.
 */
void incrementar_genero(GHashTable *tabela, const gchar *genero);

/**
 * @brief Compara dois gêneros musicais com base no número de likes.
 * 
 * @param a Ponteiro para o primeiro gênero.
 * @param b Ponteiro para o segundo gênero.
 * @return Resultado da comparação: negativo, positivo ou zero.
 */
int comparar_likes(const void *a, const void *b);

/**
 * @brief Executa a Query 3 para calcular os gêneros musicais mais populares em uma faixa etária.
 * 
 * @param idade_min Idade mínima para considerar na análise.
 * @param idade_max Idade máxima para considerar na análise.
 * @param output_file Ponteiro para o arquivo de saída.
 */
void querie3(int idade_min, int idade_max, FILE *output_file);

#endif // Q3_H
