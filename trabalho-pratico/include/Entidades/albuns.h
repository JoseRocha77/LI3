#ifndef ALBUNS_H
#define ALBUNS_H

#include <glib.h>

/**
 * @brief Estrutura representando um álbum.
 * 
 * Contém os seguintes campos:
 * - `idalbuns`: Identificador único do álbum.
 * - `titulo`: Título do álbum.
 * - `idartists`: Lista de IDs dos artistas associados.
 * - `ano`: Ano de lançamento do álbum.
 */
typedef struct Alb Albuns;

// Funções setter

/**
 * @brief Define o ID do álbum.
 * 
 * @param album Ponteiro para a estrutura Albuns.
 * @param idalbuns ID do álbum.
 */
void set_idalbuns(Albuns *album, const gchar *idalbuns);

/**
 * @brief Define o título do álbum.
 * 
 * @param album Ponteiro para a estrutura Albuns.
 * @param titulo Título do álbum.
 */
void set_titulo(Albuns *album, const gchar *titulo);

/**
 * @brief Define a lista de IDs de artistas associados ao álbum.
 * 
 * @param album Ponteiro para a estrutura Albuns.
 * @param idartists Lista de IDs dos artistas.
 */
void set_idartists(Albuns *album, GList *idartists);

/**
 * @brief Define o ano de lançamento do álbum.
 * 
 * @param album Ponteiro para a estrutura Albuns.
 * @param ano Ano de lançamento.
 */
void set_ano(Albuns *album, gint ano);

/**
 * @brief Cria um novo álbum.
 * 
 * @param idalbuns Identificador único do álbum.
 * @param titulo Título do álbum.
 * @param idartists Lista de identificadores dos artistas associados ao álbum.
 * @param ano Ano de lançamento do álbum.
 * @param producers Lista de produtores do álbum.
 * @return Ponteiro para a estrutura Albuns recém-criada.
 */
Albuns* create_album(const gchar *idalbuns, const gchar *titulo, GList *idartists, gint ano);

/**
 * @brief Libera a memória associada a um álbum.
 * 
 * @param album Ponteiro para o álbum a ser liberado.
 */
void liberar_album(Albuns *album);

// Funções de manipulação

/**
 * @brief Insere um álbum em uma coleção.
 * 
 * @param albuns Ponteiro para o álbum a ser inserido.
 */
void inserir_album(Albuns *albuns);

/**
 * @brief Busca um álbum pelo seu identificador.
 * 
 * @param idalbuns Identificador único do álbum.
 * @return Ponteiro para o álbum correspondente, ou NULL se não for encontrado.
 */
Albuns* buscar_album(const gchar *idalbuns);

/**
 * @brief Remove um álbum de uma coleção.
 * 
 * @param idalbuns Identificador único do álbum a ser removido.
 * @return TRUE se o álbum foi removido com sucesso, FALSE caso contrário.
 */
gboolean remover_album(const gchar *idalbuns);

// Funções getters

/**
 * @brief Obtém o identificador de um álbum.
 * 
 * @param album Ponteiro para o álbum.
 * @return Identificador do álbum.
 */
const gchar* get_idalbuns(Albuns *album);

/**
 * @brief Obtém o título de um álbum.
 * 
 * @param album Ponteiro para o álbum.
 * @return Título do álbum.
 */
const gchar* get_titulo(Albuns *album);

/**
 * @brief Obtém a lista de identificadores de artistas associados a um álbum.
 * 
 * @param album Ponteiro para o álbum.
 * @return Lista de identificadores dos artistas.
 */
GList* get_idartists(Albuns *album);

/**
 * @brief Obtém o ano de lançamento de um álbum.
 * 
 * @param album Ponteiro para o álbum.
 * @return Ano de lançamento.
 */
gint get_ano(Albuns *album);


#endif // ALBUNS_H

