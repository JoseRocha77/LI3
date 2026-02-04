#ifndef PARSER_H
#define PARSER_H

#include <glib.h>


/**
 * @brief Carrega dados de utilizadores de um arquivo CSV.
 * 
 * Esta função lê os dados de um arquivo CSV e insere os utilizadores na tabela de hash.
 * 
 * @param arquivo_csv Caminho para o arquivo CSV contendo os dados dos utilizadores.
 */
void carregar_usuarios(const char *arquivo_csv);

/**
 * @brief Carrega dados de músicas de um arquivo CSV.
 * 
 * Esta função lê os dados de um arquivo CSV e insere as músicas na tabela de hash.
 * Além disso essa função também incrementa a discografia de um artista que será util para a execução das queries
 * 
 * @param arquivo_csv Caminho para o arquivo CSV contendo os dados das músicas.
 */
void carregar_musicas(const char *arquivo_csv);

/**
 * @brief Carrega dados de artistas de um arquivo CSV.
 * 
 * Esta função lê os dados de um arquivo CSV e insere os artistas na tabela de hash.
 * 
 * @param arquivo_csv Caminho para o arquivo CSV contendo os dados dos artistas.
 */
void carregar_artistas(const char *arquivo_csv);

/**
 * @brief Carrega dados de álbuns de um arquivo CSV.
 * 
 * Esta função lê os dados de um arquivo CSV e insere os álbuns na tabela de hash.
 * Além disso essa função também incrementa o numero de albuns de um artista que será util para a execução das queries
 * @param arquivo_csv Caminho para o arquivo CSV contendo os dados dos álbuns.
 */
void carregar_albuns(const char *arquivo_csv);

/**
 * @brief Carrega dados de histórico de interações de um arquivo CSV.
 * 
 * Esta função lê os dados de um arquivo CSV e insere os registros de histórico na tabela de hash.
 * Além disso esta função incrementa o nº de reproduçoẽs das músicas e as receitas dos artistas
 * essenciais para a realização das Queries
 * @param arquivo_csv Caminho para o arquivo CSV contendo os dados do histórico.
 */
void carregar_history(const char *arquivo_csv);

#endif // PARSER_H
