#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Programas/principal.h"
#include "Programas/interactive.h"
#include "Programas/tests.h"

int main(int argc, char *argv[]) {
    if (argc == 3) {
        // Modo Principal
        const char *dir_dados = argv[1];
        const char *arq_comandos = argv[2];

        // Executa o programa principal
        run_principal(dir_dados, arq_comandos);

    } else if (argc == 4) {
        // Modo Teste
        const char *dir_dados = argv[1];
        const char *arq_comandos = argv[2];
        const char *dir_output_esperado = argv[3];

        // Executa o programa de testes
        programa_testes(dir_dados, arq_comandos, dir_output_esperado);

    } else if (argc == 1) {
        // Modo Interativo
        char dir_dados[256];

        printf("=== Programa Interativo ===\n");
        printf("Insira o caminho dos dados: ");
        fgets(dir_dados, sizeof(dir_dados), stdin);
        dir_dados[strcspn(dir_dados, "\n")] = '\0';

        if (strlen(dir_dados) == 0) {
            strncpy(dir_dados, "./dados", sizeof(dir_dados));
        }

        // Executa o programa interativo
        run_interactive(dir_dados);
        
    } else {
        printf("Uso incorreto.\n");
        printf("Modo correto:\n");
        printf("  - Para modo principal: %s <diretorio_dados> <arquivo_comandos>\n", argv[0]);
        printf("  - Para modo interativo: %s\n", argv[0]);
        printf("  - Para modo de testes: %s <diretorio_dados> <arquivo_comandos> <diretorio_output_esperado>\n", argv[0]);
        return 1;
    }

    return 0;
}
