#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <ctype.h> 
#include "Entidades/artists.h"
#include "Entidades/musics.h"
#include "Entidades/users.h"
#include "Entidades/albuns.h"
#include "Entidades/history.h"
#include "HashParser/hash.h" 
#include "Validacoes/validation.h"


int validar_data_nascimento(const char *data_nascimento) {
    if (strlen(data_nascimento) != 10) {
        return 0;
    }

    for (int i = 0; i < 10; i++) {
        if ((i == 4 || i == 7) && data_nascimento[i] != '/') {
            return 0;
        } else if (i != 4 && i != 7 && !isdigit(data_nascimento[i])) {
            return 0;
        }
    }

    char data_copia[11];
    strncpy(data_copia, data_nascimento, 11);

    char *ano_str = strtok(data_copia, "/");
    char *mes_str = strtok(NULL, "/");
    char *dia_str = strtok(NULL, "/");

    if (!ano_str || !mes_str || !dia_str) {
        return 0;
    }

    int ano = atoi(ano_str);
    int mes = atoi(mes_str);
    int dia = atoi(dia_str);

    if (mes < 1 || mes > 12 || dia < 1 || dia > 31) {
        return 0;
    }

    int ano_atual = 2024;
    int mes_atual = 9;
    int dia_atual = 9;

    if (ano > ano_atual || (ano == ano_atual && mes > mes_atual) ||
       (ano == ano_atual && mes == mes_atual && dia > dia_atual)) {
        return 0;
    }

    return 1;
}


int validar_duracao_musica(const char *duracao) {
    char duracao_copia[9];
    strncpy(duracao_copia, duracao, 9);

    char *horas_str = strtok(duracao_copia, ":");
    char *minutos_str = strtok(NULL, ":");
    char *segundos_str = strtok(NULL, ":");

    if (!horas_str || !minutos_str || !segundos_str ||
        strlen(horas_str) != 2 || strlen(minutos_str) != 2 || strlen(segundos_str) != 2) {
        return 0;
    }

    int horas = atoi(horas_str);
    int minutos = atoi(minutos_str);
    int segundos = atoi(segundos_str);

    if (horas < 0 || horas > 99 || minutos < 0 || minutos > 59 || segundos < 0 || segundos > 59) {
        return 0;
    }

    return 1;
}



int validar_email(const char *email) {
    const char *at = strchr(email, '@');
    if (!at || at == email) { // Verifica se '@' existe e não é o primeiro caractere
        return 0;
    }

    // Valida o username antes do '@'
    for (const char *ptr = email; ptr < at; ptr++) {
        if (!isalnum(*ptr) || isupper(*ptr)) {
            return 0;
        }
    }

    const char *domain = at + 1;
    const char *dot = strchr(domain, '.');
    if (!dot || dot == domain || *(dot + 1) == '\0') { // Verifica se '.' existe e está em posição válida
        return 0;
    }

    // Valida a parte do domínio antes do '.'
    for (const char *ptr = domain; ptr < dot; ptr++) {
        if (!islower(*ptr)) {
            return 0;
        }
    }

    // Valida a extensão após o '.'
    const char *extension = dot + 1;
    if (strcmp(extension, "net") != 0 && strcmp(extension, "org") != 0 && strcmp(extension, "com") != 0) {
        return 0;
    }

    return 1; 
}


int validar_subscription_type(const char *subscription_type) {
    return strcmp(subscription_type, "normal") == 0 || strcmp(subscription_type, "premium") == 0;
}



// Função para verificar se todos os IDs de músicas em uma lista são válidos
int validar_liked_musics_id(GList *idsdasmusicaspreferidas) {
    if (!idsdasmusicaspreferidas) {
        fprintf(stderr, "Erro: Lista de IDs das músicas é nula.\n");
        return 0; 
    }

    // Itera sobre os IDs das músicas na lista
    GList *node;
    for (node = idsdasmusicaspreferidas; node != NULL; node = node->next) {
        gchar *id_musica = (gchar *)node->data;
        //printf("musica: %s\n", id_musica);
        // Verifica se a música existe na tabela de hash
        if (!buscar_musica(id_musica)) {
            return 0; 
        }
    }

    return 1; 
}

// Função para verificar se todos os IDs de artistas em uma lista são válidos
int validar_artists_id(GList *idsdosartistas) {
    if (!idsdosartistas) {
        fprintf(stderr, "Erro: Lista de IDs dos artistas é nula.\n");
        return 0; 
    }

    // Itera sobre os IDs dos artistas na lista
    GList *node;
    for (node = idsdosartistas; node != NULL; node = node->next) {
        gchar *id_artista = (gchar *)node->data;
        //printf("artista: %s\n", id_artista);
        // Verifica se o artista existe na tabela de hash
        if (!buscar_artista(id_artista)) {
            return 0; 
        }
    }

    return 1; 
}


int validar_artist_list(const char *type, GList *idsdosartistas) {
    // Verifica se o tipo é "individual"
    if (strcmp(type, "individual") == 0) {
        // Um artista individual não deve ter IDs associados
        if (idsdosartistas != NULL && g_list_length(idsdosartistas) > 0) {
            //fprintf(stderr, "Erro: Um artista do tipo 'individual' não deve ter IDs associados na lista.\n");
            return 0; 
        }
    }

    return 1;
}


// Função para verificar se um album_id é válido
int validar_album_id(const char *album_id) {
    if (!album_id || strlen(album_id) == 0) {
        return 0; 
    }

    // Verifica se o álbum existe na tabela de álbuns
    if (!buscar_album(album_id)) {
        return 0; 
    }

    return 1; 
}

// Função para validar o campo "platform"
int validar_platform(const char *platform) {
    if (!platform) {
        return 0; 
    }

    // Transforma a string para letras minúsculas
    char platform_lower[20];
    strncpy(platform_lower, platform, sizeof(platform_lower) - 1);
    platform_lower[sizeof(platform_lower) - 1] = '\0';

    for (int i = 0; platform_lower[i]; i++) {
        platform_lower[i] = tolower(platform_lower[i]);
    }

    return strcmp(platform_lower, "mobile") == 0 || strcmp(platform_lower, "desktop") == 0;
}

// Função para validar o campo "type" de um artista
int validar_type(const char *type) {
    if (!type) {
        return 0; 
    }

    // Transforma a string para letras minúsculas
    char type_lower[20];
    strncpy(type_lower, type, sizeof(type_lower) - 1);
    type_lower[sizeof(type_lower) - 1] = '\0';

    for (int i = 0; type_lower[i]; i++) {
        type_lower[i] = tolower(type_lower[i]);
    }

    return strcmp(type_lower, "individual") == 0 || strcmp(type_lower, "group") == 0;
}

// Função para verificar se o país começa com letra maiúscula
int verificar_pais(const char *pais) {
    if (strlen(pais) > 0 && isupper(pais[0])) {
        return 1; 
    }
    return 0; 
}