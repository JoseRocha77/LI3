#ifndef TESTS_H
#define TESTS_H

#include <stdio.h>
#include <time.h>

/**
 * @file test_program.h
 * @brief Declarações de funções para o programa de testes.
 */

/**
 * @struct QueryStats
 * @brief Armazena estatísticas de execução de uma query.
 * 
 * Estrutura usada para guardar informações sobre o desempenho de uma query, 
 * como o número de acertos, falhas, comandos executados e o tempo total de execução.
 * 
 * @var acertos
 * Número de comandos bem-sucedidos.
 * 
 * @var falhas
 * Número de comandos que falharam.
 * 
 * @var comandos
 * Total de comandos executados.
 * 
 * @var tempo_total
 * Tempo total de execução em segundos.
 */
typedef struct {
    int acertos;
    int falhas;
    int comandos;
    double tempo_total;
} QueryStats;

/**
 * @brief Calcula o tempo decorrido entre dois momentos.
 * 
 * @param start Tempo inicial (obtido com clock()).
 * @param end Tempo final (obtido com clock()).
 * @return Tempo decorrido em segundos.
 */
double calcular_tempo(clock_t start, clock_t end);

/**
 * @brief Compara a saída do programa com a saída esperada.
 * 
 * Analisa linha por linha para determinar discrepâncias.
 * 
 * @param output_temp Arquivo com a saída gerada pelo programa.
 * @param output_esperado Arquivo com a saída esperada.
 * @param linha_incorreta Ponteiro para armazenar o número da primeira linha incorreta (se houver).
 * @return 0 se as saídas forem iguais, um valor diferente de 0 caso contrário.
 */
int comparar_output(FILE *output_temp, FILE *output_esperado, int *linha_incorreta);

/**
 * @brief Conta os comandos associados a cada query.
 * 
 * Lê o arquivo de comandos e atualiza a contagem de comandos por tipo de query.
 * 
 * @param comandos_path Caminho para o arquivo de comandos.
 */
void contar_comandos_por_query(const char *comandos_path);

/**
 * @brief Exibe o resumo dos resultados dos testes.
 * 
 * Apresenta um relatório contendo o número total de comandos, acertos, erros, tempo total de execução
 * e outros detalhes sobre o desempenho do programa.
 * 
 * @param total_comandos Número total de comandos executados.
 * @param total_acertos Número total de comandos executados corretamente.
 * @param total_erros Número total de comandos que apresentaram erro.
 * @param tempo_total_programa Tempo total de execução do programa em segundos.
 * @param resultado_comando Vetor com os resultados de cada comando (sucesso ou falha).
 * @param tempos_execucao Vetor com os tempos de execução de cada comando.
 * @param comandos_por_query Vetor com a contagem de comandos por tipo de query.
 */
void exibir_resumo(int total_comandos, int total_acertos, int total_erros, double tempo_total_programa, int *resultado_comando, double *tempos_execucao, int *comandos_por_query);

/**
 * @brief Executa o programa de testes.
 * 
 * Processa os comandos especificados, compara as saídas geradas pelo programa com as saídas esperadas e exibe um resumo.
 * 
 * @param comandos_path Caminho para o arquivo de comandos.
 * @param output_dir_path Caminho para o diretório de saída gerado pelo programa.
 * @param output_esperado_dir_path Caminho para o diretório contendo as saídas esperadas.
 */
void programa_testes(const char *comandos_path, const char *output_dir_path, const char *output_esperado_dir_path);

#endif // TESTS_H
