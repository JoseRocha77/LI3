#ifndef INTERACTIVE_H
#define INTERACTIVE_H

/**
 * @file interactive.h
 * @brief Declarações de funções para o modo interativo do programa.
 */

/**
 * @brief Exibe o menu interativo para o usuário.
 * 
 * Mostra as opções de queries disponíveis e orienta o usuário para interagir com o programa.
 */
void exibir_menu();

/**
 * @brief Aguarda o usuário pressionar Enter antes de prosseguir.
 */
void aguardar_usuario();

/**
 * @brief Lista o resumo de um utilizador ou artista, verificando a validade do ID.
 *
 * @param id ID do utilizador ou artista.
 * @param tabela_utilizadores Ponteiro para a tabela de utilizadores.
 * @param tabela_artistas Ponteiro para a tabela de artistas.
 */
void listar_resumo_verifica(const char *id, void *tabela_utilizadores, void *tabela_artistas);

/**
 * @brief Exibe os artistas com maior discografia, verificando entradas.
 *
 * @param N Número de artistas a listar.
 * @param pais País a ser filtrado (ou NULL para todos os países).
 * @param tabela_artistas Ponteiro para a tabela de artistas.
 * @param tabela_musicas Ponteiro para a tabela de músicas.
 */
void output_artists_verifica(int N, const char *pais, void *tabela_artistas, void *tabela_musicas);

/**
 * @brief Lista gêneros populares em uma faixa etária específica.
 *
 * @param idade_min Idade mínima.
 * @param idade_max Idade máxima.
 */
void listar_generos_verifica(int idade_min, int idade_max);

/**
 * @brief Exibe o resumo anual para um utilizador específico, verificando entradas.
 *
 * @param id_usuario ID do utilizador.
 * @param ano Ano do resumo.
 * @param N Número de artistas adicionais a incluir (opcional).
 */
void query6_verifica(const char *id_usuario, int ano, int N);


/**
 * @brief Executa o modo interativo do programa.
 * 
 * Permite que o usuário interaja com o programa por meio de um menu e insira comandos para executar queries.
 * Inicializa as tabelas de dados, carrega os arquivos CSV e gerencia a execução das queries.
 * 
 * @param dir_dados Caminho para o diretório contendo os arquivos de dados CSV.
 */
void modo_interativo(const char *dir_dados);

/**
 * @brief Versão alternativa para executar o modo interativo.
 * 
 * @param dir_dados Caminho para o diretório contendo os arquivos de dados CSV.
 */
void run_interactive(const char *dir_dados);

#endif // INTERACTIVE_H
