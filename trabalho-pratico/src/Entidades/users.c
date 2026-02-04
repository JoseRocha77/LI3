#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <stdio.h>
#include "Entidades/users.h"
#include "Utilitarias/utilitarias.h"

struct user {
    gchar *username;                // Identificador único do utilizador
    gchar *email;                   // Email de registro
    gchar *Pnome;                   // Primeiro nome
    gchar *Apelido;                 // Apelido
    gchar *datadenascimento;        // Data de nascimento
    gchar *country;                 // País de registro
    gchar *tiposubscricao;          // Tipo de subscrição
    GList *idsdasmusicaspreferidas; // Lista de IDs das músicas gostadas
} ;

/// Uso da tabela de users declarada em hash.c
extern GHashTable *tabela_utilizadores;

// Funções Setters

void set_username(User *user, const gchar *username) {
    if (user) {
        user->username = g_strdup(username);
    }
}

// Setter para email
void set_email(User *user, const gchar *email) {
    if (user) {
        user->email = g_strdup(email);
    }
}

// Setter para Pnome
void set_Pnome(User *user, const gchar *Pnome) {
    if (user) {
        user->Pnome = g_strdup(Pnome);
    }
}

// Setter para Apelido
void set_Apelido(User *user, const gchar *Apelido) {
    if (user) {
        user->Apelido = g_strdup(Apelido);
    }
}

// Setter para datadenascimento
void set_datadenascimento(User *user, const gchar *datadenascimento) {
    if (user) {
        user->datadenascimento = g_strdup(datadenascimento);
    }
}

// Setter para country
void set_country(User *user, const gchar *country) {
    if (user) {
        user->country = g_strdup(country);
    }
}

// Setter para tiposubscricao
void set_tiposubscricao(User *user, const gchar *tiposubscricao) {
    if (user) {
        user->tiposubscricao = g_strdup(tiposubscricao);
    }
}

// Setter para idsdasmusicaspreferidas
void set_idsdasmusicaspreferidas(User *user, GList *idsdasmusicaspreferidas) {
    if (user) {
        user->idsdasmusicaspreferidas = g_list_copy_deep(idsdasmusicaspreferidas,(GCopyFunc)g_strdup, NULL);
    }
}

// Atualizando a função de criação para utilizar os setters
User* create_user(const gchar *username, const gchar *email, const gchar *Pnome,
                  const gchar *Apelido, const gchar *datadenascimento, const gchar *country,
                  const gchar *tiposubscricao, GList *idsdasmusicaspreferidas) {
    // Aloca memória para a estrutura User
    User *new_user = (User *)g_malloc(sizeof(User));
    if (!new_user) return NULL;

    // Configura os campos usando os setters
    set_username(new_user, username);
    set_email(new_user, email);
    set_Pnome(new_user, Pnome);
    set_Apelido(new_user, Apelido);
    set_datadenascimento(new_user, datadenascimento);
    set_country(new_user, country);
    set_tiposubscricao(new_user, tiposubscricao);
    set_idsdasmusicaspreferidas(new_user, idsdasmusicaspreferidas);

    return new_user;
}


// Funçao para liberar a memória alocada para guardar a struct User.
void liberar_utilizador(User *user) {
    if (user) {
        //printf("Liberando memória para usuário em %p\n", (void *)user);

        if (user->username) {
            //printf("Liberando username: %s em %p\n", user->username, (void *)user->username);
            g_free(user->username);
            user->username = NULL;
        }

        if (user->email) {
            //printf("Liberando email: %s em %p\n", user->email, (void *)user->email);
            g_free(user->email);
            user->email = NULL;
        }

        if (user->Pnome) {
            //printf("Liberando Pnome: %s em %p\n", user->Pnome, (void *)user->Pnome);
            g_free(user->Pnome);
            user->Pnome = NULL;
        }

        if (user->Apelido) {
            //printf("Liberando Apelido: %s em %p\n", user->Apelido, (void *)user->Apelido);
            g_free(user->Apelido);
            user->Apelido = NULL;
        }

        if (user->datadenascimento) {
            //printf("Liberando datadenascimento: %s em %p\n", user->datadenascimento, (void *)user->datadenascimento);
            g_free(user->datadenascimento);
            user->datadenascimento = NULL;
        }

        if (user->country) {
            //printf("Liberando country: %s em %p\n", user->country, (void *)user->country);
            g_free(user->country);
            user->country = NULL;
        }

        if (user->tiposubscricao) {
            //printf("Liberando tiposubscricao: %s em %p\n", user->tiposubscricao, (void *)user->tiposubscricao);
            g_free(user->tiposubscricao);
            user->tiposubscricao = NULL;
        }

        if (user->idsdasmusicaspreferidas) {
            //printf("Liberando lista idsdasmusicaspreferidas em %p\n", (void *)user->idsdasmusicaspreferidas);
            g_list_free_full(user->idsdasmusicaspreferidas, g_free);
            user->idsdasmusicaspreferidas = NULL;
        }

        //printf("Liberando estrutura user em %p\n", (void *)user);
        free(user);
    }
}


// Função para inserir um user na tabela de hash
void inserir_user(User *user) {
    g_hash_table_insert(tabela_utilizadores, g_strdup(user->username), user);
}

// Função para buscar um user na tabela de hash
User* buscar_user(const gchar *username) { 
    return (User *)g_hash_table_lookup(tabela_utilizadores, username);
}

// Função para remover um user da tabela de hash
gboolean remover_user(const gchar *username) {
    return g_hash_table_remove(tabela_utilizadores, username);
}

// Funções Getters

// Getter para username.
gchar* get_username(const User *user) {
    return user ? user->username : NULL;
}

// Getter para obter o emal do user
gchar* get_email(const User *user) {
    return user ? user->email : NULL;
}

// Getter para obter Pnome do user.
gchar* get_Pnome(const User *user) {
    return user ? user->Pnome : NULL;
}

// Getter para obter o apelido do user
gchar* get_Apelido(const User *user) {
    return user ? user->Apelido : NULL;
}

// Getter para obter a data de nascimento do user
gchar* get_datadenascimento(const User *user) {
    return user ? user->datadenascimento : NULL;
}

// Getter para obter o country do user
gchar* get_countryU(const User *user) {
    return user ? user->country : NULL;
}

// Getter para obter o tipo_de_subscrição do user
gchar* get_tiposubscricao(const User *user) {
    return user ? user->tiposubscricao : NULL;
}

// Getter para obter o idsdasmusicaspreferidas do user
GList* get_idsdasmusicaspreferidas(const User *user) {
    return user ? user->idsdasmusicaspreferidas : NULL;
}
