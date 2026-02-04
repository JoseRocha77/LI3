#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Entidades/artists.h"
#include "Utilitarias/utilitarias.h"




struct Art {
    gchar *idartista;                // Identificador do arista
    gchar *name;                     // Nome do artista
    gfloat recipe_per_stream;        // Receita o stream do artista
    GList *id_constituent;           // Lista de IDs de constituintes
    gchar *country;                  // País de origem do artista
    gchar *type;                     // Tipo de artista: "individual" ou "grupo"
    gint discografia;                // Discografia do atista
    gint numalbuns;                  // Número de albuns do artista 
    gfloat recipe;                   // Receita do artista
} ;

// Uso da tabela de artistas declarada em hash.c
extern GHashTable *tabela_artistas;


// Funções Setters

// Setter para idartista
void set_idartista(Artist *artista, const gchar *idartista) {
    if (artista) {
        artista->idartista = g_strdup(idartista);
    }
}

// Setter para name
void set_name(Artist *artista, const gchar *name) {
    if (artista) {
        artista->name = g_strdup(name);
    }
}

// Setter para recipe_per_stream
void set_recipe_per_stream(Artist *artista, gfloat recipe_per_stream) {
    if (artista) {
        artista->recipe_per_stream = recipe_per_stream;
    }
}

// Setter para id_constituent
void set_id_constituent(Artist *artista, GList *id_constituent) {
    if (artista) {
        artista->id_constituent = g_list_copy_deep(id_constituent, (GCopyFunc)duplicate_string, NULL);
    }
}

// Setter para country
void set_countryA(Artist *artista, const gchar *country) {
    if (artista) {
        artista->country = g_strdup(country);
    }
}

// Setter para type
void set_type(Artist *artista, const gchar *type) {
    if (artista) {
        artista->type = g_strdup(type);
    }
}

// Setter para discografia
void set_discografia(Artist *artista, gint discografia) {
    if (artista) {
        artista->discografia = discografia;
    }
}

// Setter para numalbuns
void set_numalbuns(Artist *artista, gint numalbuns) {
    if (artista) {
        artista->numalbuns = numalbuns;
    }
}

// Setter para recipe
void set_recipe(Artist *artista, gfloat recipe) {
    if (artista) {
        artista->recipe = recipe;
    }
}

Artist* create_artist(const gchar *idartista, const gchar *name, gfloat recipe_per_stream, 
                      GList *id_constituent, const gchar *country, const gchar *type) {
    // Aloca memória para a estrutura Artist
    Artist *new_artist = (Artist *)g_malloc(sizeof(Artist));
    if (!new_artist) return NULL;

    // Configura os campos usando os setters
    set_idartista(new_artist, idartista);
    set_name(new_artist, name);
    set_recipe_per_stream(new_artist, recipe_per_stream);
    set_id_constituent(new_artist, id_constituent);
    set_countryA(new_artist, country);
    set_type(new_artist, type);

    // Inicializa os campos restantes com valores padrão
    set_discografia(new_artist, 0);
    set_numalbuns(new_artist, 0);
    set_recipe(new_artist, 0.0);

    // Verifica se os campos obrigatórios foram alocados corretamente
    if (!new_artist->idartista || !new_artist->name || 
        !new_artist->country || !new_artist->type) {
        liberar_artista(new_artist); // Libera recursos alocados até o momento
        return NULL;
    }

    return new_artist;
}


// Funçao para liberar a memória alocada para guardar a struct artista.
void liberar_artista(Artist *artist) {
    if (artist) {
        //printf("Liberando memória para artista em %p\n", (void *)artist);

        if (artist->idartista) {
         g_free(artist->idartista);
         artist->idartista = NULL;
        }

        if (artist->name) {
            //printf("Liberando name: %s em %p\n", artist->name, (void *)artist->name);
            g_free(artist->name);
            artist->name = NULL;
        }

       if (artist->id_constituent) {
            //printf("Liberando lista id_constituent em %p\n", (void *)artist->id_constituent);
            g_list_free_full(artist->id_constituent, g_free);
            artist->id_constituent = NULL;
        }

        if (artist->country) {
            //printf("Liberando country: %s em %p\n", artist->country, (void *)artist->country);
            g_free(artist->country);
            artist->country = NULL;
        }

        if (artist->type) {
          //printf("Liberando type: %s em %p\n", artist->type, (void *)artist->type);
            g_free(artist->type);
            artist->type = NULL;
        }

        //printf("Liberando estrutura artist em %p\n", (void *)artist);
        g_free(artist);
        
    }
}



// Função para inserir um artista na tabela de hash
void inserir_artista(Artist *artista) {
    g_hash_table_insert(tabela_artistas, g_strdup(artista->idartista), artista);
}

// Função para buscar um artista na tabela de hash
Artist* buscar_artista(const gchar *idartista) {
    return (Artist *)g_hash_table_lookup(tabela_artistas, idartista);
}

// Função para remover um artista da tabela de hash
gboolean remover_artista(const gchar *idartista) {
    return g_hash_table_remove(tabela_artistas, idartista);
}

// Função para definir a discografia
void setdiscografia(Artist* artista, int duracao) {
    if (artista) {
    artista->discografia = duracao;
    }
}

// Funçoẽs GETTERS de artistas

// Getter para idartista.
gchar* get_idartista(const Artist* artist) {
    return artist ? artist->idartista : NULL;
}

// Getter para obter o nome do arista.
gchar* get_name(const Artist* artist) {
    return artist ? artist->name : NULL;
}

// Getter para obter a recipe_per_stream do atista.
gfloat get_recipe_per_stream(const Artist* artist) {
    return artist ? artist->recipe_per_stream : 0.0f;
}

// Getter para obtr o id_constituents do arista.
GList* get_id_constituent(const Artist* artist) {
    return artist ? artist->id_constituent : NULL;
}

// Getter para obter o country do artista.
gchar* get_country(const Artist* artist) {
    return artist ? artist->country : NULL;
}

// Getter para obter o type do artista.
gchar* get_type(const Artist* artist) {
    return artist ? artist->type : NULL;
}

// Getter para obter a discografia do artista.
gint get_discografia(const Artist* artist) {
    return artist ? artist->discografia : 0;
}

// Getter para obter o numero de albuns do artista.
gint get_numalbuns(const Artist* artist) {
    return artist ? artist->numalbuns : 0;
}

// Getter para obter a receita do artista.
gfloat get_recipe(const Artist* artist) {
    return artist ? artist->recipe : 0.0;
}

// Getter para obter o numero de constituintes do artista.
gint get_num_constituents(const Artist *artist) {
    return artist ? g_list_length(artist->id_constituent) : 0;
}


// Funções de manipulação de dados dos artistas.

// Função para incrementar nº albuns
void imcnumalbuns(Artist* artista) {
    (artista->numalbuns)++;
}

// Função para imcrementar a receita.
void imcrecipe(Artist* artista, gfloat recipe) {
    artista->recipe += recipe;
}
