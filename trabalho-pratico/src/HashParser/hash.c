#include <glib.h>
#include <stdio.h>
#include "Entidades/artists.h"
#include "Entidades/musics.h"
#include "Entidades/users.h"
#include "Entidades/history.h"
#include "Entidades/albuns.h"
#include "HashParser/hash.h" 




// Declaração das tabelas de hash
GHashTable *tabela_artistas;
GHashTable *tabela_musicas;
GHashTable *tabela_utilizadores;
GHashTable *tabela_history;
GHashTable *tabela_albuns;


// Função que inicializa as tabelas de hash
void inicializar_tabelas() {
    tabela_artistas = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)liberar_artista);
    tabela_musicas = g_hash_table_new_full(g_str_hash, g_str_equal, g_free,  (GDestroyNotify)liberar_musica);
    tabela_utilizadores = g_hash_table_new_full(g_str_hash, g_str_equal, g_free,  (GDestroyNotify)liberar_utilizador);
    tabela_history = g_hash_table_new_full(g_str_hash, g_str_equal, g_free,  (GDestroyNotify)liberar_history);
    tabela_albuns = g_hash_table_new_full(g_str_hash, g_str_equal, g_free,  (GDestroyNotify)liberar_album);
}


// Função principal para liberar e destruir as tabelas
void liberar_tabelas() {
    if (tabela_artistas) {
        printf("Liberando tabela de artistas.\n");
        g_hash_table_destroy(tabela_artistas);
        printf("Tabela de artistas liberada.\n");
    } else {
        printf("Tabela de artistas já é NULL.\n");
    }

    if (tabela_musicas) {
        printf("Liberando tabela de músicas.\n");
        g_hash_table_destroy(tabela_musicas);
        printf("Tabela de musicas liberada.\n");
    } else {
        printf("Tabela de músicas já é NULL.\n");
    }

    if (tabela_utilizadores) {
        printf("Liberando tabela de utilizadores.\n");
        g_hash_table_destroy(tabela_utilizadores);
        printf("Tabela de users liberada.\n");
    } else {
        printf("Tabela de utilizadores já é NULL.\n");
    }

    if (tabela_history) {
        printf("Liberando tabela de history.\n");
        g_hash_table_destroy(tabela_history);
        printf("Tabela de history liberada.\n");
    } else {
        printf("Tabela de history já é NULL.\n");
    }

    if (tabela_albuns) {
        printf("Liberando tabela de albuns.\n");
        g_hash_table_destroy(tabela_albuns);
        printf("Tabela de albuns liberada.\n");
    } else {
        printf("Tabela de albuns já é NULL.\n");
    }
}