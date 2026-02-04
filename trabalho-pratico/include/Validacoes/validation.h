#ifndef VALIDADOR_H
#define VALIDADOR_H

#include <glib.h>
#include <stdbool.h>
#include "HashParser/hash.h"

/**
 * @file validador.h
 * @brief Declarações de funções para validação de dados no programa.
 */

/**
 * @brief Valida uma data de nascimento.
 * 
 * @param data_nascimento String representando a data no formato "YYYY-MM-DD".
 * @return 1 se a data for válida, 0 caso contrário.
 */
int validar_data_nascimento(const char *data_nascimento);

/**
 * @brief Valida a duração de uma música.
 * 
 * @param duracao String representando a duração no formato "HH:MM:SS".
 * @return 1 se a duração for válida, 0 caso contrário.
 */
int validar_duracao_musica(const char *duracao);

/**
 * @brief Valida um endereço de email.
 * 
 * @param email String representando o email.
 * @return 1 se o email for válido, 0 caso contrário.
 */
int validar_email(const char *email);

/**
 * @brief Valida o tipo de subscrição de um usuário.
 * 
 * @param subscription_type String representando o tipo de subscrição (e.g., "premium", "free").
 * @return 1 se o tipo for válido, 0 caso contrário.
 */
int validar_subscription_type(const char *subscription_type);

/**
 * @brief Valida uma lista de identificadores de músicas preferidas.
 * 
 * @param idsdasmusicaspreferidas Lista de identificadores de músicas.
 * @return 1 se todos os identificadores forem válidos, 0 caso contrário.
 */
int validar_liked_musics_id(GList *idsdasmusicaspreferidas);

/**
 * @brief Valida uma lista de identificadores de artistas.
 * 
 * @param idsdosartistas Lista de identificadores de artistas.
 * @return 1 se todos os identificadores forem válidos, 0 caso contrário.
 */
int validar_artists_id(GList *idsdosartistas);

/**
 * @brief Valida a consistência de uma lista de artistas com base em seu tipo.
 * 
 * @param type Tipo do artista (e.g., "solo", "banda").
 * @param idsdosartistas Lista de identificadores de artistas.
 * @return 1 se a lista for consistente com o tipo, 0 caso contrário.
 */
int validar_artist_list(const char *type, GList *idsdosartistas);

/**
 * @brief Valida um identificador de álbum.
 * 
 * @param album_id String representando o identificador do álbum.
 * @return 1 se o identificador for válido, 0 caso contrário.
 */
int validar_album_id(const char *album_id);

/**
 * @brief Valida o nome de uma plataforma.
 * 
 * @param platform String representando o nome da plataforma (e.g., "Spotify", "Apple Music").
 * @return 1 se o nome for válido, 0 caso contrário.
 */
int validar_platform(const char *platform);

/**
 * @brief Valida o tipo de uma entidade.
 * 
 * @param type String representando o tipo (e.g., "solo", "banda").
 * @return 1 se o tipo for válido, 0 caso contrário.
 */
int validar_type(const char *type);

/**
 * @brief Verifica se o nome de um país começa com letra maiúscula.
 *
 * @param pais Nome do país como string.
 * @return 1 se o país começa com letra maiúscula, caso contrário 0.
 */
int verificar_pais(const char *pais);

#endif // VALIDADOR_H
