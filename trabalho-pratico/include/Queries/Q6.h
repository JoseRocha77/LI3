#ifndef Q6_H
#define Q6_H

#include <glib.h>
#include <stdio.h>

/**
 * @file q6.h
 * @brief Cabeçalho para a implementação da Query 6, que gera um resumo anual de estatísticas para um utilizador.
 * 
 * Este arquivo contém as declarações de funções e tipos necessários para calcular e listar estatísticas
 * de audição de um utilizador, incluindo o artista mais ouvido, o género favorito, o álbum favorito,
 * e outras métricas relevantes.
 */

/**
 * @brief Estrutura para armazenar informações sobre um artista.
 */
typedef struct _ArtistaInfo ArtistaInfo;

/**
 * @brief Compara dois artistas com base em um critério definido.
 * 
 * @param a Ponteiro para o primeiro artista.
 * @param b Ponteiro para o segundo artista.
 * @return Um valor negativo, zero, ou positivo se o primeiro artista for menor, igual, ou maior que o segundo, respectivamente.
 */
gint comparar_artistas(gconstpointer a, gconstpointer b);

/**
 * @brief Obtém o histórico de audição de um utilizador.
 * 
 * @param user Ponteiro para a estrutura do utilizador.
 * @return Uma lista (`GList`) contendo o histórico de audição.
 */
GList* get_historico(User *user);

/**
 * @brief Filtra o histórico de audição por ano.
 * 
 * @param historico Lista de audição.
 * @param ano Ano a ser filtrado.
 * @return Uma nova lista contendo apenas as entradas do ano especificado.
 */
GList* filtrar_historico_por_ano(GList *historico, gint ano);

/**
 * @brief Calcula o artista mais ouvido com base em uma tabela hash de artistas.
 * 
 * @param artistas Tabela hash contendo artistas e contagens de audições.
 * @return Uma string (`gchar*`) com o nome do artista mais ouvido.
 */
gchar* calcular_artista_mais_ouvido(GHashTable *artistas);

/**
 * @brief Calcula o género musical mais ouvido.
 * 
 * @param generos Tabela hash contendo géneros e contagens de audições.
 * @return Uma string (`gchar*`) com o nome do género mais ouvido.
 */
gchar* calcular_genero_mais_ouvido(GHashTable *generos);

/**
 * @brief Calcula o álbum favorito.
 * 
 * @param albuns Tabela hash contendo álbuns e contagens de audições.
 * @return Uma string (`gchar*`) com o nome do álbum favorito.
 */
gchar* calcular_album_favorito(GHashTable *albuns);

/**
 * @brief Obtém a data mais recente entre duas datas.
 * 
 * @param data1 Primeira data.
 * @param data2 Segunda data.
 * @return A data mais recente entre as duas fornecidas.
 */
const gchar* obter_data_mais_recente(const gchar *data1, const gchar *data2);

/**
 * @brief Calcula o dia mais ativo em termos de audições.
 * 
 * @param dias Tabela hash contendo dias e contagens de audições.
 * @return Uma string (`gchar*`) com o dia mais ativo.
 */
gchar* calcular_dia_mais_ativo(GHashTable *dias);

/**
 * @brief Calcula a hora mais comum de audição.
 * 
 * @param horas Tabela hash contendo horas e contagens de audições.
 * @return Uma string (`gchar*`) com a hora mais comum.
 */
gchar* calcular_hora_mais_comum(GHashTable *horas);

/**
 * @brief Lista os N artistas mais ouvidos por um utilizador.
 * 
 * @param artistas Tabela hash contendo artistas e contagens de audições.
 * @param N Número de artistas a listar.
 * @param output_file Ponteiro para o arquivo onde a lista será escrita.
 */
void listar_top_artistas_utilizador(GHashTable *artistas, gint N, FILE *output_file);

/**
 * @brief Gera um resumo anual de estatísticas para um utilizador.
 * 
 * A função calcula e imprime um resumo anual contendo o tempo total de audição, 
 * número de músicas distintas ouvidas, artista mais ouvido, dia mais ativo, 
 * género musical favorito, álbum favorito e a hora mais comum de audição. 
 * Opcionalmente, também lista os N artistas mais ouvidos pelo utilizador nesse ano.
 * 
 * @param user_id Identificador único do utilizador.
 * @param year Ano para o qual o resumo será gerado.
 * @param N Número de artistas mais ouvidos a serem listados. Caso seja 0 ou omitido, 
 *          nenhum artista adicional será listado.
 * @param output_file Ponteiro para o arquivo onde o resumo será escrito.
 */
void query6(const gchar *user_id, gint year, gint N, FILE *output_file);


#endif // Q6_H
