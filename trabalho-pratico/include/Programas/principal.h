#ifndef PRINCIPAL_H
#define PRINCIPAL_H

/**
 * @file principal.h
 * @brief Declarações de funções para o programa principal.
 */

/**
 * @brief Executa comandos de um arquivo.
 * 
 * Processa e executa os comandos especificados no arquivo fornecido.
 * 
 * @param arquivo_comandos Caminho para o arquivo contendo os comandos.
 */
void executar_comandos(const char *arquivo_comandos);

/**
 * @brief Executa o programa principal.
 * 
 * Inicializa as tabelas de dados, carrega os dados dos arquivos CSV,
 * processa os comandos fornecidos no arquivo especificado e libera os recursos utilizados.
 * 
 * @param dir_dados Caminho para o diretório contendo os arquivos de dados.
 * @param arq_comandos Caminho para o arquivo contendo os comandos a serem executados.
 */
void run_principal(const char *dir_dados, const char *arq_comandos);

#endif // PRINCIPAL_H