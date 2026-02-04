#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Entidades/musics.h"
#include "Utilitarias/utilitarias.h"

struct Mus {
    gchar *idmusica;               // Identificador da música
    gchar *titulo;                 // Título da música
    GList *idartists;              // Lista de IDs dos autores
    gchar *idalbum;                // identificador do album
    gchar *duracao;                // Duração da música em minutos
    gchar *generomusica;           // Gênero da música
    gint ano;                      // Ano de lançamento               
    gint reproduçoes;              // Numero de reproduçoes
} ;

// Uso da tabela musicas declarada em hash.c
extern GHashTable *tabela_musicas;

// Funções Setters

// Setter para idmusica
void set_idmusica(Music *music, const gchar *idmusica) {
    if (music) {
        music->idmusica = g_strdup(idmusica);
    }
}

// Setter para titulo
void set_tituloM(Music *music, const gchar *titulo) {
    if (music) {
        music->titulo = g_strdup(titulo);
    }
}

// Setter para idartists
void set_idartistsM(Music *music, GList *idartists) {
    if (music) {
        music->idartists = g_list_copy_deep(idartists, (GCopyFunc)g_strdup, NULL);
    }
}

// Setter para idalbum
void set_idalbum(Music *music, const gchar *idalbum) {
    if (music) {
        music->idalbum = g_strdup(idalbum);
    }
}

// Setter para duracao
void set_duracao(Music *music, const gchar *duracao) {
    if (music) {
        music->duracao = g_strdup(duracao);
    }
}

// Setter para generomusica
void set_generomusica(Music *music, const gchar *generomusica) {
    if (music) {
        music->generomusica = g_strdup(generomusica);
    }
}

// Setter para ano
void set_anoM(Music *music, gint ano) {
    if (music) {
        music->ano = ano;
    }
}

// Setter para reproducoes
void set_reproducoes(Music *music, gint reproducoes) {
    if (music) {
        music->reproduçoes = reproducoes;
    }
}

Music* create_music(const gchar *idmusica, const gchar *titulo, GList *idartists, 
                    const gchar *idalbum, const gchar *duracao, const gchar *generomusica, gint ano) {
    // Aloca memória para a estrutura Music
    Music *new_music = (Music *)g_malloc(sizeof(Music));
    if (!new_music) return NULL;

    // Inicializa os campos usando setters para garantir consistência
    set_idmusica(new_music, idmusica);
    set_tituloM(new_music, titulo);
    set_idartistsM(new_music, idartists);
    set_idalbum(new_music, idalbum);
    set_duracao(new_music, duracao);
    set_generomusica(new_music, generomusica);
    set_anoM(new_music, ano);
    set_reproducoes(new_music, 0); // Inicializa o número de reproduções como 0

    // Verifica se os campos obrigatórios foram alocados corretamente
    if (!new_music->idmusica || !new_music->titulo || !new_music->idalbum || 
        !new_music->duracao || !new_music->generomusica) {
        liberar_musica(new_music);
        return NULL; // Retorna NULL em caso de erro
    }

    return new_music;
}


// Implementação detalhada da função de liberação de uma música
void liberar_musica(Music *music) {
    if (music) {
        //printf("Liberando memória para música em %p\n", (void *)music);
        
        // Libera cada campo alocado dinamicamente
        if (music->idmusica) {
            //printf("Liberando idmusica: %s em %p\n", music->idmusica, (void *)music->idmusica);
            g_free(music->idmusica);
            music->idmusica = NULL;
        }

        if (music->titulo) {
            //printf("Liberando título: %s em %p\n", music->titulo, (void *)music->titulo);
            g_free(music->titulo);
            music->titulo = NULL;
        }

         if (music->idartists) {
            //printf("Liberando lista idartists em %p\n", (void *)music->idartists);
             g_list_free_full(music->idartists, g_free); // Libera a lista e as strings duplicadas.
             music->idartists = NULL;
         }

        if (music->idalbum) {
            //printf("Liberando idalbum: %s em %p\n", music->idalbum, (void *)music->idalbum);
            g_free(music->idalbum);
            music->idalbum = NULL;
        }

        if (music->duracao) {
            //printf("Liberando duração: %s em %p\n", music->duracao, (void *)music->duracao);
            g_free(music->duracao);
            music->duracao = NULL;
        }

        if (music->generomusica) {
            //printf("Liberando gênero música: %s em %p\n", music->generomusica, (void *)music->generomusica);
            g_free(music->generomusica);
            music->generomusica = NULL;
        }


        //printf("Liberando estrutura music em %p\n", (void *)music);
        free(music);
    }
}


// Função para inserir uma músia na tabela de hash
void inserir_musica(Music *musica) {
    g_hash_table_insert(tabela_musicas, g_strdup(musica->idmusica), musica);
}
// Função para buscar uma música na tabela de hash
Music* buscar_musica(const gchar *idmusica) {
    return (Music *)g_hash_table_lookup(tabela_musicas, idmusica);
}

// Função para remover uma música da tabela de hash
gboolean remover_musica(const gchar *idmusica) {
    return g_hash_table_remove(tabela_musicas, idmusica);
}


// Funções Getters

// Função getter para obter o gênero da música
gchar* get_genero_musica(const Music *music) {
    return music ? music->generomusica : NULL;
}

// Função getter para obter o id_música
gchar* get_idmusica(const Music *music) {
    return music ? music->idmusica : NULL;
}

// Função getter para obter o id_álbum da música
gchar* get_idalbum(const Music *music) {
    return music ? music->idalbum : NULL;
}

// Função getter para obter a duração da música
gchar* get_duracao(const Music *music) {
    return music ? music->duracao : NULL;
}


// Função para obter a lista de artistas de uma música
GList* get_idartistsm(const Music *music) {
    return music ? music->idartists : NULL; 
}


// Funções de manipulção de dados das musicas

// Função para imcrementar o número de reproducoes da musica.
void imcreproducoes(Music *music) {
    (music->reproduçoes)++;
}

