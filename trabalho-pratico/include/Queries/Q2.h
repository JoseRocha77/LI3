#ifndef Q2_H
#define Q2_H

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Entidades/artists.h"
#include "Entidades/musics.h"
#include "HashParser/hash.h"
#include "Validacoes/validation.h"
#include "Utilitarias/utilitarias.h"

/**
 * @brief Compara dois artistas com base na duração total de suas músicas e IDs.
 * 
 * @param a Ponteiro para o primeiro artista.
 * @param b Ponteiro para o segundo artista.
 * @param duracoes_totais Tabela de hash contendo a duração total das músicas para cada artista.
 * @return Valor negativo se o primeiro artista for maior, positivo se o segundo for maior, ou 0 se forem iguais.
 */
gint compare_artists(gconstpointer a, gconstpointer b, gpointer duracoes_totais);

/**
 * @brief Exibe os top N artistas com maior duração total de músicas, filtrados por país.
 * 
 * @param N Número máximo de artistas a serem exibidos.
 * @param country_filter String com o nome do país para filtrar os artistas (NULL para desativar o filtro).
 * @param tabela_artistas Tabela de hash contendo os dados dos artistas.
 * @param tabela_musicas Tabela de hash contendo os dados das músicas associadas aos artistas.
 * @param output_file Ponteiro para o arquivo onde a saída será escrita.
 */
void output_artists(gint N, const gchar *country_filter, GHashTable *tabela_artistas, GHashTable *tabela_musicas, FILE *output_file);

#endif // Q2_H
