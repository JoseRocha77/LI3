#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include "Entidades/history.h"

struct His{
    gchar *idhistory;             // identificador historico
    gchar *iduser;                // identificador do user
    gchar *idmusic;               // Identificador da música
    gchar *timestamp;             // data e hora da audição
    gchar *duration;              // duração da audição
    gchar *platform;              // plataforma utilizada       
};

// Uso da tabela hisórico declarada em hash.c
extern GHashTable *tabela_history;

// Funções Setters

// Setter para idhistory
void set_idhistory(History *history, const gchar *idhistory) {
    if (history) {
        history->idhistory = g_strdup(idhistory);
    }
}

// Setter para iduser
void set_iduser(History *history, const gchar *iduser) {
    if (history) {
        history->iduser = g_strdup(iduser);
    }
}

// Setter para idmusic
void set_idmusic(History *history, const gchar *idmusic) {
    if (history) {
        history->idmusic = g_strdup(idmusic);
    }
}

// Setter para timestamp
void set_timestamp(History *history, const gchar *timestamp) {
    if (history) {
        history->timestamp = g_strdup(timestamp);
    }
}

// Setter para duration
void set_duration(History *history, const gchar *duration) {
    if (history) {
        history->duration = g_strdup(duration);
    }
}

// Setter para platform
void set_platform(History *history, const gchar *platform) {
    if (history) {
        history->platform = g_strdup(platform);
    }
}


// Atualizando a função de criação para utilizar os setters

History* create_history(const gchar *idhistory, const gchar *iduser, const gchar *idmusic, 
                        const gchar *timestamp, const gchar *duration, const gchar *platform) {
    // Aloca memória para a estrutura History
    History *new_history = (History *)malloc(sizeof(History));
    if (!new_history) return NULL;

    // Inicializa os campos usando os setters
    set_idhistory(new_history, idhistory);
    set_iduser(new_history, iduser);
    set_idmusic(new_history, idmusic);
    set_timestamp(new_history, timestamp);
    set_duration(new_history, duration);
    set_platform(new_history, platform);

    return new_history;
}


// Implementação detalhada da função de liberação de um histórico
void liberar_history(History *history) {
    if (history) {
        // Libera cada campo alocado dinamicamente
        if (history->idhistory) {
            g_free(history->idhistory);
            history->idhistory = NULL;
        }

        if (history->iduser) {
            g_free(history->iduser);
            history->iduser = NULL;
        }

        if (history->idmusic) {
            g_free(history->idmusic);
            history->idmusic = NULL;
        }

        if (history->timestamp) {
            g_free(history->timestamp);
            history->timestamp = NULL;
        }

        if (history->duration) {
            g_free(history->duration);
            history->duration = NULL;
        }

        if (history->platform) {
            g_free(history->platform);
            history->platform = NULL;
        }

        // Libera a estrutura principal
        g_free(history);
    }
}

// Função para inserir um hisórico na tabela de hash
void inserir_history(History *history) {
    g_hash_table_insert(tabela_history, g_strdup(history->idhistory), history);
}

// Função para buscar um histórico na tabela de hash
History* buscar_history(const gchar *history) { 
    return (History *)g_hash_table_lookup(tabela_history, history);
}

// Função para remover um hstórico da tabela de hash
gboolean remover_history(const gchar *history) {
    return g_hash_table_remove(tabela_history, history);
}

// Funções Getters

// Função getter para obter o id_history            
const gchar* get_idhistory(History *history) {
    return history ? history->idhistory : NULL;
}

// Função getter para obter o id_album do histórico
const gchar* get_iduser(History *history) {
    return history ? history->iduser : NULL;
}

// Função getter para obter o id_music do histórico
const gchar* get_idmusic(History *history) {
    return history ? history->idmusic : NULL;
}

// Função getter para obter o timestamp do histórico
const gchar* get_timestamp(History *history) {
    return history ? history->timestamp : NULL;
}

// Função getter para obter a duração do histórico
const gchar* get_duration(History *history) {
    return history ? history->duration : NULL;
}

// Função getter para obter a plataforma do histórico
const gchar* get_platform(History *history) {
    return history ? history->platform : NULL;
}

// Função getter para obter o dia da audição do histórico
gchar* get_dia_audicao(const gchar* timestamp) {
    if (!timestamp) return NULL; // Retorna NULL em caso de entrada inválida

    // Aloca espaço suficiente para a string de data (YYYY/MM/DD) + null-terminator
    gchar* data = g_new(gchar, 11);

    // Copia os primeiros 10 caracteres do timestamp (YYYY/MM/DD)
    strncpy(data, timestamp, 10);
    data[10] = '\0'; // Garante que a string está terminada

    return data; // Retorna a string alocada
}

// Função getter para obter a hora da audição do histórico
gchar* get_hora_audicao(const gchar* timestamp) {
    if (!timestamp) return NULL;

    // Procurar o espaço que separa a data da hora
    const gchar* hora_ptr = g_strrstr(timestamp, " ");
    if (!hora_ptr || *(hora_ptr + 1) == '\0') return NULL;

    // Avançar para a parte da hora
    hora_ptr++;

    // Alocar memória para a string da hora (HH) e copiar o valor
    gchar* hora_str = g_malloc(3); // HH + '\0'
    if (!hora_str) return NULL;

    hora_str[0] = hora_ptr[0];
    hora_str[1] = hora_ptr[1];
    hora_str[2] = '\0';

    return hora_str;
}
