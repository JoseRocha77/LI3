#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashParser/parser.h" 
#include "Queries/Q1.h"    
#include "Queries/Q2.h"
#include "Queries/Q3.h"
#include "Queries/Q6.h"
#include "Entidades/users.h" 
#include "Entidades/musics.h"
#include "Entidades/artists.h"
#include "Entidades/albuns.h"
#include "Entidades/history.h"
#include "HashParser/hash.h" 
#include "Validacoes/validation.h"
#include "Utilitarias/utilitarias.h"
#include "Programas/interactive.h"
#define OUTPUT_BUFFER_SIZE 1024

void exibir_menu() {
    printf("\n=== Menu Interativo ===\n");
    printf("1. Resumo de Utilizador/Artista (Query 1)\n");
    printf("2. Top N Artistas com Maior Discografia (Query 2)\n");
    printf("3. Géneros Populares por Faixa Etária (Query 3)\n");
    printf("4. Artista com Mais Presenças no Top 10 (Query 4)\n");
    printf("5. Recomendação de Utilizadores (Query 5)\n");
    printf("6. Resumo Anual para um Utilizador (Query 6)\n");
    printf("0. Sair\n");
}

void aguardar_usuario() {
    printf("\nPressione Enter para voltar ao menu...");
    while (getchar() != '\n');
}

void listar_resumo_verifica(const char *id, void *tabela_utilizadores, void *tabela_artistas) {
    char buffer[OUTPUT_BUFFER_SIZE];
    FILE *temp_output = fmemopen(buffer, sizeof(buffer), "w");

    if (temp_output) {
        if (buscar_user(id)) {
            listar_resumo_utilizador(id, temp_output);
        } else if (buscar_artista(id)) {
            listar_resumo_artista(id, temp_output);
        } else {
            printf("Erro: ID %s não encontrado.\n", id);
            fclose(temp_output);
            return;
        }

        fclose(temp_output);

        if (strlen(buffer) > 0) {
            printf("%s", buffer);
        } else {
            printf("Sem resultado para essas informações.\n");
        }
    } else {
        printf("Erro ao criar buffer temporário.\n");
    }
}


void output_artists_verifica(int N, const char *pais, void *tabela_artistas, void *tabela_musicas) {
    char buffer[OUTPUT_BUFFER_SIZE];
    FILE *temp_output = fmemopen(buffer, sizeof(buffer), "w");

    if (temp_output) {
        output_artists(N, pais, tabela_artistas, tabela_musicas, temp_output);
        fclose(temp_output);

        if (strlen(buffer) > 0) {
            printf("%s", buffer);
        } else {
            printf("Sem resultado para essas informações.\n");
        }
    } else {
        printf("Erro ao criar buffer temporário.\n");
    }
}


void listar_generos_verifica(int idade_min, int idade_max) {
    if (idade_min < 0 || idade_max < 0) {
        printf("Erro: As idades devem ser números positivos.\n");
        return;
    }

    if (idade_min > idade_max) {
        printf("Erro: A idade mínima (%d) não pode ser maior que a idade máxima (%d).\n", idade_min, idade_max);
        return;
    }

    char buffer[OUTPUT_BUFFER_SIZE] = {0};
    FILE *temp_output = fmemopen(buffer, sizeof(buffer), "w");

    if (!temp_output) {
        printf("Erro ao criar buffer temporário.\n");
        return;
    }

    querie3(idade_min, idade_max, temp_output);
    fflush(temp_output);
    fclose(temp_output);

    printf("\nGêneros mais ouvidos e a respectiva quantidade de likes na faixa etária de %d a %d anos:\n", idade_min, idade_max);

    if (strlen(buffer) > 0) {
        printf("%s", buffer);
    } else {
        printf("Sem resultado para essas informações.\n");
    }
}



void query6_verifica(const char *id_usuario, int ano, int N) {
    char buffer[OUTPUT_BUFFER_SIZE];
    FILE *temp_output = fmemopen(buffer, sizeof(buffer), "w");

    if (temp_output) {
        // Chama a função que executa a Query 6
        query6(id_usuario, ano, N, temp_output);
        fclose(temp_output);

        // Exibe o resultado ou mensagem padrão
        if (strlen(buffer) > 0) {
            printf("%s", buffer);
        } else {
            printf("Sem resultado para essas informações.\n");
        }
    } else {
        printf("Erro ao criar buffer temporário.\n");
    }
}



void modo_interativo(const char *dir_dados) {
    // Carregar dados
    printf("Carregando dados do diretório: %s\n", dir_dados);
    inicializar_tabelas();

    // Monta os caminhos dos arquivos CSV para carregamento de dados
    char arq_users[256], arq_musics[256], arq_artists[256], arq_albuns[256], arq_history[256];
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

    printf("Dados carregados com sucesso!\n\n");

        // Loop interativo
        int opcao = -1;
        int exibir_menu_automaticamente = 1; 

        while (opcao != 0) {
            if (exibir_menu_automaticamente) {
                exibir_menu();
            }

            printf("Escolha uma opção: ");
            if (scanf("%d", &opcao) != 1) { 
                opcao = -1; 
                while (getchar() != '\n'); 
            }

            if (opcao < 0 || opcao > 6) {
                printf("Opção inválida. Escolha novamente.\n");
                exibir_menu_automaticamente = 0; 
                continue; 
            }

            exibir_menu_automaticamente = 1; 

        switch (opcao) {
            case 1: {
                char id[100];
                int id_valido = 0;

                while (!id_valido) {
                    printf("Insira o ID do Utilizador/Artista ou escreva 'menu' para voltar ao menu: ");
                    scanf("%99s", id);
                    getchar(); 

                    if (strcmp(id, "menu") == 0) {
                        printf("Voltando ao menu...\n");
                        break; 
                    }

                    // Verifica se é um utilizador ou artista válido
                    if (buscar_user(id)) {
                        printf("\nResumo do Utilizador:\n");
                        listar_resumo_utilizador(id, stdout);
                        id_valido = 1; 
                    } else if (buscar_artista(id)) {
                        printf("\nResumo do Artista:\n");
                        listar_resumo_artista(id, stdout);
                        id_valido = 1; 
                    } else {
                        printf("Erro: ID %s não encontrado.\n", id);
                    }
                }

                if (id_valido) {
                    aguardar_usuario(); 
                }
                break;
            }


            case 2: {
                int N;
                char pais[100] = "";

                // Validação de entrada para N
                while (1) {
                    printf("Insira o número de artistas (N): ");
                    if (scanf("%d", &N) == 1 && N > 0) {
                        break; 
                    } else {
                        printf("Erro: O valor de N deve ser um inteiro maior que 0. Tente novamente.\n");
                        while (getchar() != '\n'); 
                    }
                }

                getchar(); 

                while (1) {
                    printf("Insira o país ou pressione Enter para ignorar: ");
                    fgets(pais, sizeof(pais), stdin);
                    pais[strcspn(pais, "\n")] = '\0';

                    // Validação de entrada para o país
                    if (strlen(pais) > 0 && !verificar_pais(pais)) {
                        printf("Erro: O nome do país deve começar com uma letra maiúscula.\n");
                    } else {
                        break; 
                    }
                }

                if (strlen(pais)) {
                    printf("\nOs %d artistas com maior discografia de %s:\n", N, pais);
                } else {
                    printf("\nOs %d artistas com maior discografia:\n", N);
                }
                output_artists_verifica(N, strlen(pais) ? pais : NULL, tabela_artistas, tabela_musicas);

                aguardar_usuario();
                break;
            }
            case 3: {
                int idade_min, idade_max;

                while (1) {
                    // Solicitar a idade mínima
                    while (1) {
                        printf("Insira a idade mínima: ");
                        if (scanf("%d", &idade_min) == 1 && idade_min >= 0) {
                            break; 
                        } else {
                            printf("Erro: A idade mínima deve ser um número inteiro não negativo. Tente novamente.\n");
                            while (getchar() != '\n'); 
                        }
                    }

                    // Solicitar a idade máxima
                    while (1) {
                        printf("Insira a idade máxima: ");
                        if (scanf("%d", &idade_max) == 1 && idade_max >= 0) {
                            break; 
                        } else {
                            printf("Erro: A idade máxima deve ser um número inteiro não negativo. Tente novamente.\n");
                            while (getchar() != '\n'); 
                        }
                    }

                    // Verificar se a mínima é menor que a máxima
                    if (idade_min <= idade_max) {
                        break; 
                    } else {
                        printf("Erro: A idade mínima (%d) não pode ser maior que a idade máxima (%d). Insira as idades novamente.\n", idade_min, idade_max);
                    }
                }

                while (getchar() != '\n');

                // Chamar a função de listagem de gêneros
                listar_generos_verifica(idade_min, idade_max);

                aguardar_usuario();
                break;
            }

            case 4: {
                printf("Esta funcionalidade está em desenvolvimento.\n");
                while (getchar() != '\n');
                aguardar_usuario();
                break;
            }
            case 5: {
                printf("Esta funcionalidade está em desenvolvimento.\n");
                while (getchar() != '\n');
                aguardar_usuario();
                break;
            }
            case 6: {
                char id_usuario[100];
                int ano, N = 0;
                int id_valido = 0;

                // Validação do ID do Usuário
                while (!id_valido) {
                    printf("Insira o ID do Utilizador ou escreva 'menu' para voltar ao menu: ");
                    scanf("%99s", id_usuario);
                    getchar();

                    if (strcmp(id_usuario, "menu") == 0) {
                        printf("Voltando ao menu...\n");
                        break;
                    }

                    if (buscar_user(id_usuario)) {
                        id_valido = 1; 
                    } else {
                        printf("Erro: ID %s não encontrado. Por favor, insira um ID válido.\n", id_usuario);
                    }
                }

                // Se o usuário decidiu voltar ao menu, sair do caso
                if (!id_valido) {
                    break;
                }

                // Solicitação do Ano com Validação de 4 dígitos
                char ano_str[10];  
                while (1) {
                    printf("Insira o ano desejado: ");
                    fgets(ano_str, sizeof(ano_str), stdin);

                    // Remove o '\n' se existir
                    ano_str[strcspn(ano_str, "\n")] = '\0';

                    // Verifica se o ano tem exatamente 4 dígitos
                    if (strlen(ano_str) == 4 && sscanf(ano_str, "%d", &ano) == 1 && ano >= 1000 && ano <= 9999) {
                        break;  
                    } else {
                        printf("Erro: Ano inválido. Por favor, insira um ano com 4 dígitos entre 2010 e 2025.\n");
                    }
                }

                // Solicitação de N (opcional)
                printf("Insira o número de artistas (N) para incluir ou pressione Enter para ignorar: ");
                char n_input[10];
                fgets(n_input, sizeof(n_input), stdin);

                // Converte N, se especificado
                if (sscanf(n_input, "%d", &N) != 1) {
                    N = 0;  
                }

                // Chamada da Query 6
                printf("\nResumo anual para o usuário %s no ano %d:\nFormato: tempo de audição;#musicas;artista mais ouvido ;dia que mais ouviu ;genero mais ouvido ;album favorito ;hora mais comum de audição\n[artista preferido n1;#musicas;tempo de audição]\n...\n\n", id_usuario, ano);
                query6_verifica(id_usuario, ano, N);

                aguardar_usuario();
                break;
            }
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    liberar_tabelas();
    printf("Memória liberada. Programa encerrado.\n");
}

void run_interactive(const char *dir_dados) {
    modo_interativo(dir_dados);
}
