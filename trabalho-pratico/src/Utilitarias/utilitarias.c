#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
#include <glib.h>
#include "Entidades/artists.h"
#include "Entidades/musics.h"
#include "Entidades/users.h"
#include "Entidades/albuns.h"
#include "Entidades/history.h"
#include "HashParser/hash.h" 
#include "Utilitarias/utilitarias.h"

int calcular_idade(const char *data_nascimento) {
    int dia_nasc, mes_nasc, ano_nasc;
    sscanf(data_nascimento, "%d/%d/%d", &ano_nasc, &mes_nasc, &dia_nasc);

    // Define a data de referência como 09/09/2024
    int ano_ref = 2024, mes_ref = 9, dia_ref = 9;

    int idade = ano_ref - ano_nasc;
    //printf("Idade calculada pelo ano: %d\n", idade);

    if (mes_ref < mes_nasc  || (mes_nasc == mes_ref && dia_nasc > dia_ref)) {
        idade--;
        //printf("Aniversário ainda n ocorreu no ano de referencia: %d\n", idade);
    }

    return idade;
}

char *tratar_lista_id(const char *id) {
    if (!id) return NULL; // Verifica se o input é nulo.

    // Aloca memória para o resultado.
    char *resultado = malloc(strlen(id) + 1);
    if (!resultado) {
        printf("Erro ao alocar memória\n");
        return NULL;
    }

    size_t j = 0; // Índice para o resultado.
    for (size_t i = 0; id[i] != '\0'; i++) {
        // Adiciona o caractere se não for ' [ ou ] nem espaços extras.
        if (id[i] != '\'' && id[i] != '[' && id[i] != ']' && id[i] != ' ') {
            resultado[j++] = id[i];
        }
    }
    resultado[j] = '\0'; // Finaliza a string com o terminador nulo.

    return resultado; // Retorna a string tratada.
}



// Função auxiliar para remover aspas de um campo
char* remove_aspas(char *str) {
    if (!str || str[0] != '"' || str[strlen(str) - 1] != '"') {
        return str; // Retorna a string original se não tiver aspas
    }
    str[strlen(str) - 1] = '\0'; // Remove aspas finais
    return str + 1; // Ignora aspas iniciais
}


// Converte a duração no formato "hh:mm:ss" para segundos
gint converter_duracao_para_segundos(const gchar *duracao) {
    gint horas, minutos, segundos;

    if (sscanf(duracao, "%d:%d:%d", &horas, &minutos, &segundos) != 3 ) {
        printf("Formato de duração inválido: %s\n", duracao);
        return 0;
    }
    return (horas * 3600) + (minutos * 60) + segundos;
}

// Converte a duração em segundos para o formato "hh:mm:ss"
gchar* converter_segundos_para_duracao(gint duracao_em_segundos) {
    gint horas = duracao_em_segundos / 3600;
    gint minutos = (duracao_em_segundos % 3600) / 60;
    gint segundos = duracao_em_segundos % 60;
    gchar* duracao_formatada = malloc(9 * sizeof(gchar));
    if (duracao_formatada) {
        snprintf(duracao_formatada, 9, "%02d:%02d:%02d", horas, minutos, segundos);
    }
    //printf("Duração formatada: %s\n", duracao_formatada);
    return duracao_formatada;
}

// Função de comparação para procurar um ID de artista específico na lista de IDs de uma música
gint comparar_id_artista(gconstpointer a, gconstpointer b) {
    return g_strcmp0((const gchar *)a, (const gchar *)b);
}

void substituir_separador(char *linha) {
    for (int i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == ';') {
            linha[i] = '=';
        }
    }
}

gpointer duplicate_string(const gchar *string) {
    return g_strdup(string); // Duplicar a string com g_strdup
}