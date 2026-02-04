#ifndef Q4_H
#define Q4_H

#include <glib.h>

/**
 * @file Q4.h
 * @brief Funções e estruturas relacionadas ao cálculo do artista com maior presença no Top 10 semanal.
 */

/**
 * @brief Estrutura para armazenar o tempo de reprodução de um artista.
 */
typedef struct {
    char *artist_id; /**< ID do artista. */
    int playtime;    /**< Tempo de reprodução em segundos. */
} ArtistPlaytime;

/**
 * @brief Função de comparação para ordenar artistas por tempo de reprodução de forma decrescente.
 *
 * @param a Ponteiro para o primeiro artista a ser comparado.
 * @param b Ponteiro para o segundo artista a ser comparado.
 * @return -1 se o primeiro artista tiver maior playtime, 1 se menor, 0 se iguais.
 */
gint compare_playtime_desc(gconstpointer a, gconstpointer b);

/**
 * @brief Calcula o início da semana correspondente a um timestamp.
 *
 * @param timestamp Data e hora no formato "YYYY/MM/DD HH:MM:SS".
 * @param inicio_semana Data de início da semana no formato "YYYY/MM/DD".
 * @return String representando o início da semana no formato "YYYY/MM/DD" ou NULL em caso de erro.
 */
char *calcular_inicio_da_semana(const char *timestamp, const char *inicio_semana);

/**
 * @brief Obtém a chave da semana correspondente a um timestamp.
 *
 * @param timestamp Data e hora no formato "YYYY/MM/DD HH:MM:SS".
 * @param inicio_semana Data de início da semana no formato "YYYY/MM/DD".
 * @return Chave da semana no formato "YYYY/MM/DD".
 */
char *obter_chave_semana(const char *timestamp, const char *inicio_semana);

/**
 * @brief Verifica se uma data está dentro de um intervalo especificado.
 *
 * @param data Data no formato "YYYY/MM/DD".
 * @param begin_date Data inicial do intervalo no formato "YYYY/MM/DD".
 * @param end_date Data final do intervalo no formato "YYYY/MM/DD".
 * @return 1 se a data estiver no intervalo, 0 caso contrário.
 */
int data_esta_no_intervalo(const char *data, const char *begin_date, const char *end_date);

/**
 * @brief Atualiza o tempo de reprodução total para um artista.
 *
 * @param playtime_table Tabela de hash para armazenar tempos de reprodução por artista.
 * @param artist_id ID do artista.
 * @param duration Duração da reprodução em segundos.
 */
void atualizar_tempo_reproducao(GHashTable *playtime_table, const char *artist_id, int duration);

/**
 * @brief Agrupa o tempo de reprodução semanal dos artistas.
 *
 * @param begin_date Data inicial do intervalo no formato "YYYY/MM/DD".
 * @param end_date Data final do intervalo no formato "YYYY/MM/DD".
 * @return Tabela de hash com tempos de reprodução agrupados por semana.
 */
GHashTable *agrupar_tempo_por_semana(const char *begin_date, const char *end_date);

/**
 * @brief Calcula o Top 10 artistas mais reproduzidos semanalmente e atualiza a contagem.
 *
 * @param weekly_playtime Tabela de hash com tempos de reprodução semanais.
 * @param artist_top_count Tabela de hash para armazenar a contagem de presenças no Top 10.
 */
void calcular_top_10(GHashTable *weekly_playtime, GHashTable *artist_top_count);

/**
 * @brief Executa a Query 4, identificando o artista com mais presenças no Top 10.
 *
 * @param begin_date Data inicial do intervalo no formato "YYYY/MM/DD".
 * @param end_date Data final do intervalo no formato "YYYY/MM/DD".
 * @param output_file Arquivo onde o resultado será gravado.
 */
void query4(char *begin_date, char *end_date, FILE *output_file);

#endif // Q4_H
