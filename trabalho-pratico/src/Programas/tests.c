#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>
#include <ctype.h>
#include "HashParser/hash.h"
#include "Programas/principal.h"

// Estrutura para armazenar as estatísticas de cada query
typedef struct {
    int acertos;
    int falhas;
    int comandos;
    double tempo_total;
} QueryStats;

QueryStats stats[6];  // Uma para cada query de 1 a 6
int comandos_falhados[500];  // Para armazenar os números de comandos que falharam
int falhas_contadas = 0;

// Função para calcular o tempo decorrido em segundos
double calcular_tempo(clock_t start, clock_t end) {
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Função para comparar dois arquivos caractere por caractere
int comparar_output(FILE *output_temp, FILE *output_esperado, int *posicao_incorreta) {
    int char_esperado, char_obtido;
    *posicao_incorreta = 1;

    rewind(output_temp);
    rewind(output_esperado);

    while ((char_esperado = fgetc(output_esperado)) != EOF &&
           (char_obtido = fgetc(output_temp)) != EOF) {
        // Ignorar espaços em branco no início ou final de ambos
        while (isspace(char_esperado)) char_esperado = fgetc(output_esperado);
        while (isspace(char_obtido)) char_obtido = fgetc(output_temp);

        if (char_esperado != char_obtido) {
            return 0;  // Encontrou diferença
        }
        (*posicao_incorreta)++;
    }

    // Verifica se ambos os arquivos terminaram
    if (fgetc(output_esperado) != EOF || fgetc(output_temp) != EOF) {
        return 0;
    }

    return 1;  
}

// Função para contar os comandos associados a cada query
void contar_comandos_por_query(const char *comandos_path) {
    FILE *comandos_file = fopen(comandos_path, "r");
    if (!comandos_file) {
        fprintf(stderr, "Erro ao abrir o arquivo de comandos: %s\n", comandos_path);
        exit(EXIT_FAILURE);
    }

    char linha[128];
    while (fgets(linha, sizeof(linha), comandos_file)) {
        int query_num;

        // Extraímos o número da query (assumindo que ela está no início da linha)
        if (sscanf(linha, "%d", &query_num) == 1 && query_num >= 1 && query_num <= 6) {
            stats[query_num - 1].comandos++;
        }
    }

    fclose(comandos_file);
}

void exibir_resumo(int total_comandos, int total_acertos, int total_erros, double tempo_total_programa, int* resultado_comando, double* tempos_execucao, int* comandos_por_query) {
    printf("\nResumo dos testes:\n");
    printf("Total de testes executados: %d\n", total_comandos);
    printf("Testes corretos: %d\n", total_acertos);
    printf("Testes com erro: %d\n", total_erros);

    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    double memoria_usada_gb = r_usage.ru_maxrss / 1024.0 / 1024.0;  
    printf("Tempo total de execução: %.3f segundos.\n", tempo_total_programa );  
    printf("Memória máxima usada: %.3f GB\n", memoria_usada_gb); 

    int ordem_queries[] = {1, 2, 3, 4, 6, 5};
    int posicao_atual = 0;

    for (int i = 0; i < 6; i++) {
        int query_id = ordem_queries[i];
        int total_query = comandos_por_query[i];
        int acertos = 0, falhas = 0;
        double tempo_total_query = 0;

        for (int j = posicao_atual; j < posicao_atual + total_query; j++) {
            if (resultado_comando[j] == 1) {
                acertos++;
            } else {
                falhas++;
            }
            tempo_total_query += tempos_execucao[j];
        }

        double tempo_medio = total_query > 0 ? tempo_total_query / total_query : 0;

        printf("\nQuery %d:\n", query_id);
        printf("  Total de comandos: %d\n", total_query);
        printf("  Acertos: %d\n", acertos);
        printf("  Falhas: %d\n", falhas);
        printf("  Tempo médio: %.3f ms\n", tempo_medio * 1000);  
        printf("  Tempo total: %.3f ms\n", tempo_total_query * 1000);  

        posicao_atual += total_query;
    }

    // Identificar comandos que falharam e organizá-los por query
    printf("\nComandos que falharam:\n");
    int falhas_contadas = 0;

    for (int i = 0; i < 6; i++) {
        int query_id = ordem_queries[i];
        int total_query = comandos_por_query[i];
        int encontrou_falhas = 0;

        printf("\n  Query %d: ", query_id);  
        int contador_linha = 0; 

        for (int j = 0; j < total_query; j++) {
            int comando_index = falhas_contadas + j;
            if (comando_index < total_comandos && resultado_comando[comando_index] != 1) {
                if (contador_linha > 0 && contador_linha % 10 == 0) {
                    printf("\n           "); 
                }
                printf("Comando %d", comando_index + 1);
                encontrou_falhas = 1;
                contador_linha++;

                if (j < total_query - 1) {
                    printf(", ");
                }
            }
        }

        if (!encontrou_falhas) {
            printf("Nenhum");
        }

        printf("\n");
        falhas_contadas += total_query;
    }
}


void programa_testes(const char *dir_dados, const char *comandos_path, const char *output_esperado_dir_path) {
    clock_t inicio_programa = clock();

    printf("Inicializando tabelas e processando comandos...\n");
    run_principal(dir_dados, comandos_path);

    // Contar comandos por query
    contar_comandos_por_query(comandos_path);
    int comandos_por_query[6];
    for (int i = 0; i < 6; i++) {
        comandos_por_query[i] = stats[i].comandos;
    }

    printf("\n\nExecutando comparação de resultados...\n");
    int total_acertos = 0;
    int total_erros = 0;
    int comando_num = 1;

    int resultado_comando[500]; // Array para resultados dos comandos (máximo de 500 comandos)
    double tempos_execucao[500]; // Array para tempos de execução dos comandos

    while (1) {
        char output_nome[128], output_esperado_nome[128];
        snprintf(output_nome, sizeof(output_nome), "resultados/command%d_output.txt", comando_num);
        snprintf(output_esperado_nome, sizeof(output_esperado_nome), "%s/command%d_output.txt", output_esperado_dir_path, comando_num);

        FILE *output_file = fopen(output_nome, "r");
        FILE *output_esperado_file = fopen(output_esperado_nome, "r");

        if (!output_file || !output_esperado_file) {
            if (output_file) fclose(output_file);
            if (output_esperado_file) fclose(output_esperado_file);
            break;
        }

        clock_t inicio_query = clock();
        int posicao_incorreta;
        int resultado = comparar_output(output_file, output_esperado_file, &posicao_incorreta);
        clock_t fim_query = clock();

        double tempo_query = calcular_tempo(inicio_query, fim_query);

        // Determina a query associada ao comando com base na ordem (1, 2, 3, 4, 6, 5)
        int ordem_queries[] = {1, 2, 3, 4, 6, 5};
        int query_index = ordem_queries[(comando_num - 1) % 6] - 1;

        stats[query_index].tempo_total += tempo_query;

        // Atualiza resultados e estatísticas
        resultado_comando[comando_num - 1] = resultado;
        tempos_execucao[comando_num - 1] = tempo_query;

        if (resultado) {
            stats[query_index].acertos++;
            total_acertos++;
        } else {
            stats[query_index].falhas++;
            comandos_falhados[falhas_contadas++] = comando_num;
            total_erros++;
        }

        fclose(output_file);
        fclose(output_esperado_file);
        comando_num++;
    }

    clock_t fim_programa = clock();
    double tempo_total_programa = calcular_tempo(inicio_programa, fim_programa);

    // Passar os novos arrays para exibir_resumo
    exibir_resumo(comando_num - 1, total_acertos, total_erros, tempo_total_programa, resultado_comando, tempos_execucao, comandos_por_query);
}
