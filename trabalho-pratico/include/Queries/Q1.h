#ifndef Q1_H
#define Q1_H

#include <stdio.h>
#include <glib.h>
#include "HashParser/hash.h" 

/**
 * @brief Lista o resumo do utilizador, incluindo informações básicas.
 * 
 * Exibe informações como email, primeiro nome, apelido, idade e país de residência.
 * Caso o utilizador não seja encontrado, uma linha vazia será escrita no arquivo de saída.
 * 
 * @param utilizador_id Ponteiro para o ID do utilizador cujas informações serão resumidas.
 * @param output_file Ponteiro para o arquivo onde a saída será escrita.
 */

void listar_resumo_utilizador(const gchar *utilizador_id, FILE *output_file);

/**
 * @brief Lista o resumo de um artista, incluindo informações essenciais.
 * 
 * Exibe informações como nome, tipo (e.g., individual ou grupo), país, número de álbuns e receita total.
 * Caso o artista não seja encontrado, uma linha vazia será escrita no arquivo de saída.
 * 
 * @param artista_id Ponteiro para o ID do artista cujas informações serão resumidas.
 * @param output_file Ponteiro para o arquivo onde a saída será escrita.
 */

void listar_resumo_artista(const gchar *artista_id, FILE *output_file);


#endif 
