#ifndef ARTISTS_H
#define ARTISTS_H

#include <glib.h>

/**
 * @brief Estrutura representando um artista.
 * 
 * Contém os seguintes campos:
 * - `idartista`: Identificador único do artista.
 * - `name`: Nome do artista.
 * - `recipe_per_stream`: Receita gerada por stream.
 * - `id_constituent`: Lista de identificadores dos constituintes do artista.
 * - `country`: País de origem do artista.
 * - `type`: Tipo do artista ("individual" ou "grupo").
 * - `discografia`: Duração total da discografia do artista.
 * - `numalbuns`: Número de álbuns do artista.
 * - `recipe`: Receita total do artista.
 */
typedef struct Art Artist;


/**
 * @brief Define o ID do artista.
 * 
 * @param art Ponteiro para a estrutura Art.
 * @param idartista Novo ID do artista.
 */
void set_idartista(Artist *artista, const gchar *idartista);

/**
 * @brief Define o nome do artista.
 * 
 * @param art Ponteiro para a estrutura Art.
 * @param name Novo nome do artista.
 */
void set_name(Artist *artista, const gchar *name);


/**
 * @brief Define a receita por stream do artista.
 * 
 * @param art Ponteiro para a estrutura Art.
 * @param recipe_per_stream Nova receita por stream.
 */
void set_recipe_per_stream(Artist *artist, gfloat recipe_per_stream);

/**
 * @brief Define a lista de constituintes do artista.
 * 
 * @param art Ponteiro para a estrutura Art.
 * @param id_constituent Nova lista de IDs de constituintes.
 */
void set_id_constituent(Artist *artista, GList *id_constituent);

/**
 * @brief Define o país de origem do artista.
 * 
 * @param art Ponteiro para a estrutura Art.
 * @param country Novo país de origem do artista.
 */
void set_countryA(Artist *artista, const gchar *country);

/**
 * @brief Define o tipo do artista.
 * 
 * @param art Ponteiro para a estrutura Art.
 * @param type Novo tipo do artista ("individual" ou "grupo").
 */
void set_type(Artist *artista, const gchar *type);

/**
 * @brief Define a discografia do artista.
 * 
 * @param art Ponteiro para a estrutura Art.
 * @param discografia Nova discografia do artista.
 */
void set_discografia(Artist *artista, gint discografia);

/**
 * @brief Define o número de álbuns do artista.
 * 
 * @param art Ponteiro para a estrutura Art.
 * @param numalbuns Novo número de álbuns.
 */
void set_numalbuns(Artist *artista, gint numalbuns);

/**
 * @brief Define a receita total do artista.
 * 
 * @param art Ponteiro para a estrutura Art.
 * @param recipe Nova receita total do artista.
 */
void set_recipe(Artist *artista, gfloat recipe);

// Funções para criar e liberar um artista

/**
 * @brief Cria um novo artista.
 * 
 * @param idartista Identificador único do artista.
 * @param name Nome do artista.
 * @param recipe_per_stream Receita gerada por stream.
 * @param id_constituent Lista de identificadores dos artistas constituintes.
 * @param country País de origem do artista.
 * @param type Tipo do artista (e.g., individual, grupo).
 * @return Ponteiro para a estrutura Artist recém-criada.
 */
Artist* create_artist(const gchar *idartista, const gchar *name, gfloat recipe_per_stream, GList *id_constituent, const gchar *country, const gchar *type);

/**
 * @brief Libera a memória associada a um artista.
 * 
 * @param artist Ponteiro para o artista a ser liberado.
 */
void liberar_artista(Artist *artist);

// Funções getters para obter os atributos de um artista

/**
 * @brief Obtém o identificador único de um artista.
 * 
 * @param artist Ponteiro para o artista.
 * @return Identificador único do artista.
 */
gchar* get_idartista(const Artist* artist);

/**
 * @brief Obtém o nome de um artista.
 * 
 * @param artist Ponteiro para o artista.
 * @return Nome do artista.
 */
gchar* get_name(const Artist* artist);


/**
 * @brief Obtém a receita por stream de um artista.
 * 
 * @param artist Ponteiro para o artista.
 * @return Receita gerada por stream.
 */
gfloat get_recipe_per_stream(const Artist* artist);

/**
 * @brief Obtém a lista de identificadores dos artistas constituintes.
 * 
 * @param artist Ponteiro para o artista.
 * @return Lista de identificadores dos artistas constituintes.
 */
GList* get_id_constituent(const Artist* artist);

/**
 * @brief Obtém o país de origem de um artista.
 * 
 * @param artist Ponteiro para o artista.
 * @return País de origem do artista.
 */
gchar* get_country(const Artist* artist);

/**
 * @brief Obtém o tipo de um artista (e.g., solo, banda).
 * 
 * @param artist Ponteiro para o artista.
 * @return Tipo do artista.
 */
gchar* get_type(const Artist* artist);

/**
 * @brief Obtém o numero de constiuintes de um grupo 
 * 
 * @param artist Ponteiro para o artista.
 * @return numero de elementos de um grupo.
 */
gint get_num_constituents(const Artist *artista);

/**
 * @brief Obtém a duração da discografia de um artista.
 * 
 * @param artist Ponteiro para o artista.
 * @return Duração da discografia.
 */
gint get_discografia(const Artist* artist);

/**
 * @brief Obtém o numero de albuns de um artista.
 * 
 * @param artist Ponteiro para o artista.
 * @return número de albuns.
 */
gint get_numalbuns(const Artist* artista);

/**
 * @brief Obtém o numero de audiçoes de um artista.
 * 
 * @param artist Ponteiro para o artista.
 * @return número de audiçoes.
 */
gfloat get_recipe(const Artist* artist);

// Funções para a tabela de hash de artistas

/**
 * @brief Insere um artista em uma tabela de hash.
 * 
 * @param artista Ponteiro para o artista a ser inserido.
 */
void inserir_artista(Artist *artista);

/**
 * @brief Busca um artista pelo seu identificador único.
 * 
 * @param idartista Identificador único do artista.
 * @return Ponteiro para o artista encontrado, ou NULL se não for encontrado.
 */
Artist* buscar_artista(const gchar *idartista);

/**
 * @brief Remove um artista da tabela de hash.
 * 
 * @param idartista Identificador único do artista.
 * @return TRUE se o artista foi removido com sucesso, FALSE caso contrário.
 */
gboolean remover_artista(const gchar *idartista);


// Funções para manipular atributos de artistas

/**
 * @brief Imcrementa o numero de albuns do artista.
 * 
 * @param artista Ponteiro para o artista.
 */
void imcnumalbuns(Artist* artista);

/**
 * @brief Imcrementa a receita do artista.
 * 
 * @param artista Ponteiro para o artista.
 */
void imcrecipe(Artist* artista, gfloat recipe);

/**
 * @brief Define a duração total da discografia do artista.
 * 
 * @param artista Ponteiro para a estrutura Art.
 * @param duracao Nova duração total da discografia.
 */
void setdiscografia(Artist* artista, int duracao);


#endif // ARTISTS_H
