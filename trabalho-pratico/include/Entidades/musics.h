#ifndef MUSICS_H
#define MUSICS_H

#include <glib.h>

/**
 * @brief Estrutura representando uma música.
 * 
 * Contém os seguintes campos:
 * - `idmusica`: Identificador único da música.
 * - `titulo`: Título da música.
 * - `idartists`: Lista de identificadores dos artistas associados.
 * - `idalbum`: Identificador do álbum ao qual a música pertence.
 * - `duracao`: Duração da música no formato string.
 * - `generomusica`: Gênero da música.
 * - `ano`: Ano de lançamento da música.
 * - `reproduçoes`: Número de vezes que a música foi reproduzida.
 */
typedef struct Mus Music;

// Funções setter
/**
 * @brief Define o ID da música.
 * 
 * @param music Ponteiro para a estrutura Music.
 * @param idmusica ID da música a ser definido.
 */
void set_idmusica(Music *music, const gchar *idmusica);

/**
 * @brief Define o título da música.
 * 
 * @param music Ponteiro para a estrutura Music.
 * @param titulo Título da música a ser definido.
 */
void set_tituloM(Music *music, const gchar *titulo);

/**
 * @brief Define a lista de IDs de artistas associados à música.
 * 
 * @param music Ponteiro para a estrutura Music.
 * @param idartists Lista de IDs de artistas.
 */
void set_idartistsM(Music *music, GList *idartists);

/**
 * @brief Define o ID do álbum associado à música.
 * 
 * @param music Ponteiro para a estrutura Music.
 * @param idalbum ID do álbum a ser definido.
 */
void set_idalbum(Music *music, const gchar *idalbum);

/**
 * @brief Define a duração da música.
 * 
 * @param music Ponteiro para a estrutura Music.
 * @param duracao Duração da música no formato de string.
 */
void set_duracao(Music *music, const gchar *duracao);

/**
 * @brief Define o gênero da música.
 * 
 * @param music Ponteiro para a estrutura Music.
 * @param generomusica Gênero da música a ser definido.
 */
void set_generomusica(Music *music, const gchar *generomusica);

/**
 * @brief Define o ano de lançamento da música.
 * 
 * @param music Ponteiro para a estrutura Music.
 * @param ano Ano de lançamento.
 */
void set_anoM(Music *music, gint ano);

/**
 * @brief Define o número de reproduções da música.
 * 
 * @param music Ponteiro para a estrutura Music.
 * @param reproducoes Número de reproduções.
 */
void set_reproducoes(Music *music, gint reproducoes);

// Funções para criar e liberar músicas

/**
 * @brief Cria uma nova música.
 * 
 * @param idmusica Identificador único da música.
 * @param titulo Título da música.
 * @param idartists Lista de identificadores dos artistas associados.
 * @param idalbum Identificador do álbum ao qual a música pertence.
 * @param duracao Duração da música.
 * @param generomusica Gênero da música.
 * @param ano Ano de lançamento da música.
 * @return Ponteiro para a estrutura Music recém-criada.
 */
Music* create_music(const gchar *idmusica, const gchar *titulo, GList *idartists, const gchar *idalbum, const gchar *duracao, const gchar *generomusica, gint ano);

/**
 * @brief Libera a memória associada a uma música.
 * 
 * @param music Ponteiro para a música a ser liberada.
 */
void liberar_musica(Music *music);

// Funções relacionadas à tabela de hash de músicas

/**
 * @brief Insere uma música em uma tabela de hash.
 * 
 * @param musica Ponteiro para a música a ser inserida.
 */
void inserir_musica(Music *musica);

/**
 * @brief Busca uma música pelo identificador único.
 * 
 * @param idmusica Identificador único da música.
 * @return Ponteiro para a música encontrada, ou NULL se não for encontrada.
 */
Music* buscar_musica(const gchar *idmusica);

/**
 * @brief Remove uma música da tabela de hash.
 * 
 * @param idmusica Identificador único da música.
 * @return TRUE se a música foi removida com sucesso, FALSE caso contrário.
 */
gboolean remover_musica(const gchar *idmusica);

// Funções getters

/**
 * @brief Obtém o gênero de uma música.
 * 
 * @param music Ponteiro para a música.
 * @return Gênero da música.
 */
gchar* get_genero_musica(const Music *music);

/**
 * @brief Obtém o id do album a que a música pertence.
 * 
 * @param music Ponteiro para a música.
 * @return Id do album a que a música pertence.
 */
gchar* get_idalbum(const Music *music);

/**
 * @brief Obtém a duração de uma música.
 * 
 * @param music Ponteiro para a música.
 * @return Duração da música.
 */
gchar* get_duracao(const Music *music);

// GList* get_artista_musica(const Music* music);

/**
 * @brief Obtém o id da música.
 * 
 * @param music Ponteiro para a música.
 * @return Id da música.
 */
gchar* get_idmusica(const Music *music);

/**
 * @brief Obtém a lista dos artistas de uma música.
 * 
 * @param music Ponteiro para a música.
 * @return Lista dos artistas da música.
 */
GList* get_idartistsm(const Music *music);


// Funções de manipulção de dados das musicas

/**
 * @brief Imcrementa o numero de reproducoes da musica.
 * 
 * @param artista Ponteiro para a musica.
 */
void imcreproducoes(Music *music);

#endif // MUSICS_H
