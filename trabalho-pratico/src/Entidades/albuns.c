#include <glib.h>
#include <stdlib.h>
#include "Entidades/albuns.h"

struct Alb{
    gchar *idalbuns;               // Identificador da música
    gchar *titulo;                 // Título da música
    GList *idartists;              // Lista de IDs dos autores
    gint ano;                      // Ano de lançamento
};

// Uso da tabela albuns declarada em hash.c
extern GHashTable *tabela_albuns;


// Funções Setters

void set_idalbuns(Albuns *album, const gchar *idalbuns) {
    if (!album || !idalbuns) return;
    album->idalbuns = g_strdup(idalbuns);
}

void set_titulo(Albuns *album, const gchar *titulo) {
    if (!album || !titulo) return;
    album->titulo = g_strdup(titulo);
}

void set_idartists(Albuns *album, GList *idartists) {
    if (!album) return;
    album->idartists = g_list_copy_deep(idartists, (GCopyFunc)g_strdup, NULL);
}

void set_ano(Albuns *album, gint ano) {
    if (!album) return;
    album->ano = ano;
}

Albuns* create_album(const gchar *idalbuns, const gchar *titulo, GList *idartists, gint ano) {
    // Aloca memória para a estrutura Albuns
    Albuns *new_album = (Albuns *)g_malloc(sizeof(Albuns));
    if (!new_album) return NULL;

    // Usa os setters para inicializar os campos
    set_idalbuns(new_album, idalbuns);
    set_titulo(new_album, titulo);
    set_idartists(new_album, idartists);
    set_ano(new_album, ano);

    return new_album;
}


// Funçao para liberar a memória alocada para guarda a struct album.
void liberar_album(Albuns *album) {
    if (album) {
        if (album->idalbuns) {
            g_free(album->idalbuns);
            album->idalbuns = NULL;
        }

        if (album->titulo) {
            g_free(album->titulo);
            album->titulo = NULL;
        }

        if (album->idartists) {
            g_list_free_full(album->idartists, g_free);
            album->idartists = NULL;
        }

        free(album);
    }
}


// Função para inserir um album na tabela de hash
void inserir_album(Albuns *albuns) {
    g_hash_table_insert(tabela_albuns, g_strdup(albuns->idalbuns), albuns);
}

// Função para buscar um album pela ID
Albuns* buscar_album(const gchar *idalbuns) { 
    return (Albuns *)g_hash_table_lookup(tabela_albuns, idalbuns);
}

// Função para remover um album pela ID
gboolean remover_album(const gchar *idalbuns) {
    return g_hash_table_remove(tabela_albuns, idalbuns);
}

// Funções Getters

// Getter para id_album
const gchar* get_idalbuns(Albuns *album) {
    return album ? album->idalbuns : NULL;
}

// Getter para obter o titulo do album
const gchar* get_titulo(Albuns *album) {
    return album ? album->titulo : NULL;
}

// Getter para obter o id_artists do album
GList* get_idartists(Albuns *album) {
    return album ? album->idartists : NULL;
}

// Getter para obter o ano do album
gint get_ano(Albuns *album) {
    return album ? album->ano : 0; 
}
