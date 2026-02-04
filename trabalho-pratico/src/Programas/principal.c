#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashParser/hash.h" 
#include "Queries/Q1.h"    
#include "Queries/Q2.h"
#include "Queries/Q3.h"
#include "Queries/Q4.h"
#include "Queries/Q5.h"
#include "Queries/Q6.h"
#include "Entidades/users.h" 
#include "Entidades/musics.h"
#include "Entidades/artists.h"
#include "Entidades/albuns.h"
#include "Entidades/history.h"
#include "HashParser/parser.h" 
#include "Validacoes/validation.h"
#include "Utilitarias/utilitarias.h"
#include "Programas/principal.h"



void executar_comandos(const char *arquivo_comandos) {
    FILE *arq = fopen(arquivo_comandos, "r");
    if (!arq) {
        printf("Erro ao abrir o arquivo: %s\n", arquivo_comandos);
        return;
    }

    char linha[256];
    int comando_num = 1;

    while (fgets(linha, sizeof(linha), arq)) {
        int query_id, idade_min, idade_max, N, ano;
        char pais[100] = "", id[100] = "";
        char data_inicio[20] = "", data_fim[20] = "";
        char id_usuario[20] = "";
        int separador_igual = 0;

        // Remover nova linha no final, se existir
        linha[strcspn(linha, "\n")] = 0;

        
        // Verificar e remover o 'S' apenas se estiver imediatamente após um número
        for (int i = 0; linha[i] != '\0'; i++) {
            if (linha[i] >= '0' && linha[i] <= '9' && linha[i + 1] == 'S') {
            // Remove o 'S' movendo o resto da string para a esquerda
             memmove(&linha[i + 1], &linha[i + 2], strlen(&linha[i + 2]) + 1);
        
            // Define separador_igual como 1 após a remoção do 'S'
            separador_igual = 1;
            break;
            }
        }

        


        // Verificar o ID do comando
        if (sscanf(linha, "%d", &query_id) != 1) {
            printf("Comando inválido na linha %d\n", comando_num);
            comando_num++;
            continue;
        }

        // Definir nome do arquivo de saída
        char output_nome[256];
        snprintf(output_nome, sizeof(output_nome), "resultados/command%d_output.txt", comando_num);

        FILE *output_file = fopen(output_nome, "w");
        if (!output_file) {
            printf("Erro ao abrir o arquivo de saída: %s\n", output_nome);
            comando_num++;
            continue;
        }

        switch (query_id) {
            case 1:
                if (sscanf(linha, "%*d %s", id) == 1) {
                    if (buscar_user(id)) {
                    listar_resumo_utilizador(id, output_file);
                } else if (buscar_artista(id)) {
                    listar_resumo_artista(id, output_file);
                } else {
                    fprintf(output_file, "\n");
                }
                }
                break;

            case 2:
                if (sscanf(linha, "%*d %d %99[^\n]", &N, pais) >= 1) {
                    output_artists(N, strlen(pais) ? remove_aspas(pais) : NULL, tabela_artistas, tabela_musicas, output_file);
                } else {
                    fprintf(output_file, "\n");
                }
                break;

            case 3:
                if (sscanf(linha, "%*d %d %d", &idade_min, &idade_max) == 2) {
                    querie3(idade_min, idade_max, output_file);
                } else {
                    fprintf(output_file, "\n");
                }
                break;

            // case 4:
            //     if (sscanf(linha, "%*d %19s %19s", data_inicio, data_fim) == 2) {
            //         query4(data_inicio, data_fim, output_file);
            //     } else {
            //         query4(NULL, NULL, output_file);
            //     }
            //     break;

            // case 5:
            //     if (sscanf(linha, "%*d %s %d", id_usuario, &N) == 2) {
            //         recomendar_utilizadores(id_usuario, N, output_file);
            //     } else {
            //         fprintf(output_file, "\n");
            //     }
            //     break;
            
            case 6:  // Implementação da Query 6
                N = 0;  // Inicializa N com 0 para garantir que não retenha valores de comandos anteriores
                if (sscanf(linha, "%*d %s %d %d", id_usuario, &ano, &N) >= 2) {
                    query6(id_usuario, ano, N, output_file);
                } else if (sscanf(linha, "%*d %s %d", id_usuario, &ano) == 2) {
                    query6(id_usuario, ano, 0, output_file);  // Passa 0 como N quando não está especificado
                } else {
                    fprintf(output_file, "\n");  // Linha vazia no arquivo de saída
                }
                break;

            default:
                fprintf(output_file, "\n");
                break;
        }

        fclose(output_file);

        // Substituir separador, se necessário
        if (separador_igual) {
            FILE *file_in = fopen(output_nome, "r");
            FILE *file_out = fopen("temp_output.txt", "w");

            if (file_in && file_out) {
                while (fgets(linha, sizeof(linha), file_in)) {
                    substituir_separador(linha);
                    fputs(linha, file_out);
                }
                fclose(file_in);
                fclose(file_out);
                rename("temp_output.txt", output_nome);
            }
        }
        comando_num++;
    }

    fclose(arq);
    printf("Processamento dos comandos concluído.\n");
}

void run_principal(const char *dir_dados, const char *arq_comandos) {
    // Inicializa as tabelas hash
    printf("Inicializando tabelas de dados...\n");
    inicializar_tabelas();

    // Monta os caminhos dos arquivos CSV para carregamento de dados
    char arq_users[256], arq_musics[256], arq_artists[256], arq_albuns[256], arq_history[256];;
    snprintf(arq_users, sizeof(arq_users), "%s/users.csv", dir_dados);
    snprintf(arq_musics, sizeof(arq_musics), "%s/musics.csv", dir_dados);
    snprintf(arq_artists, sizeof(arq_artists), "%s/artists.csv", dir_dados);
    snprintf(arq_albuns, sizeof(arq_albuns), "%s/albums.csv", dir_dados);
    snprintf(arq_history, sizeof(arq_history), "%s/history.csv", dir_dados);

    // Carrega dados dos arquivos CSV
    printf("Carregando dados de usuários, músicas, artistas e álbuns...\n");
    carregar_artistas(arq_artists);
    carregar_albuns(arq_albuns);
    carregar_musicas(arq_musics);
    carregar_usuarios(arq_users);
    carregar_history(arq_history);

    printf("Dados carregados com sucesso!\n");

    // Processa os comandos do arquivo especificado
    printf("Executando comandos do arquivo: %s\n", arq_comandos);
    executar_comandos(arq_comandos);

    // Libera a memória das tabelas e finaliza o programa
    printf("Liberando memória das tabelas...\n");
    liberar_tabelas();

    printf("Execução finalizada. Todos os dados foram processados e liberados.\n");
}