#ifndef UTILITARIAS_H
#define UTILITARIAS_H

#include <glib.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>

/**
 * @file utilitarias.h
 * @brief Declarações de funções utilitárias para operações diversas no programa.
 */

/**
 * @brief Calcula a idade com base na data de nascimento fornecida.
 * 
 * @param data_nascimento String representando a data de nascimento no formato "YYYY-MM-DD".
 * @return Idade calculada em anos.
 */
int calcular_idade(const char *data_nascimento);

/**
 * @brief Trata uma lista de identificadores separados por vírgulas.
 * 
 * @param id String contendo a lista de identificadores.
 * @return String formatada contendo os identificadores tratados.
 */
char *tratar_lista_id(const char *id);

/**
 * @brief Remove as aspas de uma string.
 * 
 * @param str String da qual as aspas serão removidas.
 * @return Ponteiro para a string sem aspas.
 */
char* remove_aspas(char *str);

/**
 * @brief Converte uma duração no formato "HH:MM:SS" para segundos.
 * 
 * @param duracao String representando a duração no formato "HH:MM:SS".
 * @return Duração em segundos.
 */
gint converter_duracao_para_segundos(const gchar *duracao);

/**
 * @brief Converte uma duração em segundos para o formato "HH:MM:SS".
 * 
 * @param duracao_em_segundos Duração em segundos.
 * @return String representando a duração no formato "HH:MM:SS".
 */
gchar* converter_segundos_para_duracao(gint duracao_em_segundos);

/**
 * @brief Compara dois identificadores de artistas.
 * 
 * Função usada para ordenação ou busca em listas de identificadores.
 * 
 * @param a Primeiro identificador.
 * @param b Segundo identificador.
 * @return 0 se forem iguais, um valor negativo se a < b, ou positivo se a > b.
 */
gint comparar_id_artista(gconstpointer a, gconstpointer b);

/**
 * @brief Substitui o separador de campos em uma linha.
 * 
 * Altera um separador (e.g., vírgula) para outro caractere em uma string.
 * 
 * @param linha String onde o separador será substituído.
 */
void substituir_separador(char *linha);

/**
 * @brief Duplica uma string.
 * 
 * 
 * @param string A string a ser duplicada. Deve ser uma string válida e não nula.
 * @return Um ponteiro para a nova string duplicada. Retorna `NULL` se a string de entrada for `NULL` 
 *         ou se a alocação de memória falhar.
 */
gpointer duplicate_string(const gchar *string);

#endif // UTILITARIAS_H
