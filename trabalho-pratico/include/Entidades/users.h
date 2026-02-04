#ifndef USERS_H
#define USERS_H

#include <glib.h>

/**
 * @brief Estrutura representando um usuário.
 */
typedef struct user User;

// Funçoẽs setter

/**
 * @brief Define o nome de usuário.
 * 
 * @param user Ponteiro para a estrutura do usuário.
 * @param username Nome de usuário a ser configurado.
 */
void set_username(User *user, const gchar *username);

/**
 * @brief Define o endereço de e-mail.
 * 
 * @param user Ponteiro para a estrutura do usuário.
 * @param email Endereço de e-mail a ser configurado.
 */
void set_email(User *user, const gchar *email);

/**
 * @brief Define o primeiro nome.
 * 
 * @param user Ponteiro para a estrutura do usuário.
 * @param Pnome Primeiro nome a ser configurado.
 */
void set_Pnome(User *user, const gchar *Pnome);

/**
 * @brief Define o apelido ou sobrenome.
 * 
 * @param user Ponteiro para a estrutura do usuário.
 * @param Apelido Apelido ou sobrenome a ser configurado.
 */
void set_Apelido(User *user, const gchar *Apelido);

/**
 * @brief Define a data de nascimento.
 * 
 * @param user Ponteiro para a estrutura do usuário.
 * @param datadenascimento Data de nascimento a ser configurada.
 */
void set_datadenascimento(User *user, const gchar *datadenascimento);

/**
 * @brief Define o país.
 * 
 * @param user Ponteiro para a estrutura do usuário.
 * @param country País a ser configurado.
 */
void set_country(User *user, const gchar *country);

/**
 * @brief Define o tipo de subscrição.
 * 
 * @param user Ponteiro para a estrutura do usuário.
 * @param tiposubscricao Tipo de subscrição a ser configurado.
 */
void set_tiposubscricao(User *user, const gchar *tiposubscricao);

/**
 * @brief Define a lista de IDs das músicas preferidas.
 * 
 * @param user Ponteiro para a estrutura do usuário.
 * @param idsdasmusicaspreferidas Lista de IDs das músicas preferidas.
 */
void set_idsdasmusicaspreferidas(User *user, GList *idsdasmusicaspreferidas);

// Funções para criar e liberar usuários

/**
 * @brief Cria um novo usuário.
 * 
 * @param username Nome de usuário.
 * @param email Email do usuário.
 * @param Pnome Primeiro nome do usuário.
 * @param Apelido Sobrenome do usuário.
 * @param datadenascimento Data de nascimento do usuário.
 * @param country País de origem do usuário.
 * @param tiposubscricao Tipo de subscrição (e.g., premium, gratuito).
 * @param idsdasmusicaspreferidas Lista de identificadores das músicas preferidas do usuário.
 * @return Ponteiro para a estrutura User recém-criada.
 */
User* create_user(const gchar *username, const gchar *email, const gchar *Pnome, const gchar *Apelido, const gchar *datadenascimento, const gchar *country, const gchar *tiposubscricao, GList *idsdasmusicaspreferidas);

/**
 * @brief Define o nome de usuário.
 * 
 * @param user Ponteiro para a estrutura do usuário.
 * @param username Nome de usuário a ser configurado.
 */
void set_username(User *user, const gchar *username);

/**
 * @brief Define o endereço de e-mail.
 * 
 * @param user Ponteiro para a estrutura do usuário.
 * @param email Endereço de e-mail a ser configurado.
 */
void set_email(User *user, const gchar *email);

/**
 * @brief Define o primeiro nome.
 * 
 * @param user Ponteiro para a estrutura do usuário.
 * @param Pnome Primeiro nome a ser configurado.
 */
void set_Pnome(User *user, const gchar *Pnome);

/**
 * @brief Define o apelido ou sobrenome.
 * 
 * @param user Ponteiro para a estrutura do usuário.
 * @param Apelido Apelido ou sobrenome a ser configurado.
 */
void set_Apelido(User *user, const gchar *Apelido);

/**
 * @brief Define a data de nascimento.
 * 
 * @param user Ponteiro para a estrutura do usuário.
 * @param datadenascimento Data de nascimento a ser configurada.
 */
void set_datadenascimento(User *user, const gchar *datadenascimento);

/**
 * @brief Define o país.
 * 
 * @param user Ponteiro para a estrutura do usuário.
 * @param country País a ser configurado.
 */
void set_country(User *user, const gchar *country);

/**
 * @brief Define o tipo de subscrição.
 * 
 * @param user Ponteiro para a estrutura do usuário.
 * @param tiposubscricao Tipo de subscrição a ser configurado.
 */
void set_tiposubscricao(User *user, const gchar *tiposubscricao);

/**
 * @brief Define a lista de IDs das músicas preferidas.
 * 
 * @param user Ponteiro para a estrutura do usuário.
 * @param idsdasmusicaspreferidas Lista de IDs das músicas preferidas.
 */
void set_idsdasmusicaspreferidas(User *user, GList *idsdasmusicaspreferidas);


/**
 * @brief Libera a memória associada a um usuário.
 * 
 * @param user Ponteiro para o usuário a ser liberado.
 */
void liberar_utilizador(User *user);

// Funções relacionadas à tabela de hash de usuários

/**
 * @brief Insere um usuário em uma tabela de hash.
 * 
 * @param user Ponteiro para o usuário a ser inserido.
 */
void inserir_user(User *user);

/**
 * @brief Busca um usuário pelo nome de usuário.
 * 
 * @param username Nome de usuário.
 * @return Ponteiro para o usuário encontrado, ou NULL se não for encontrado.
 */
User* buscar_user(const gchar *username);

/**
 * @brief Remove um usuário da tabela de hash.
 * 
 * @param username Nome de usuário do usuário.
 * @return TRUE se o usuário foi removido com sucesso, FALSE caso contrário.
 */
gboolean remover_user(const gchar *username);

// Funções getters

/**
 * @brief Obtém o nome de usuário.
 * 
 * @param user Ponteiro para o usuário.
 * @return Nome de usuário.
 */
gchar* get_username(const User *user);

/**
 * @brief Obtém o email do usuário.
 * 
 * @param user Ponteiro para o usuário.
 * @return Email do usuário.
 */
gchar* get_email(const User *user);

/**
 * @brief Obtém o primeiro nome do usuário.
 * 
 * @param user Ponteiro para o usuário.
 * @return Primeiro nome do usuário.
 */
gchar* get_Pnome(const User *user);

/**
 * @brief Obtém o sobrenome do usuário.
 * 
 * @param user Ponteiro para o usuário.
 * @return Sobrenome do usuário.
 */
gchar* get_Apelido(const User *user);

/**
 * @brief Obtém a data de nascimento do usuário.
 * 
 * @param user Ponteiro para o usuário.
 * @return Data de nascimento do usuário.
 */
gchar* get_datadenascimento(const User *user);

/**
 * @brief Obtém o país de origem do usuário.
 * 
 * @param user Ponteiro para o usuário.
 * @return País de origem do usuário.
 */
gchar* get_countryU(const User *user);

/**
 * @brief Obtém o tipo de subscrição do usuário.
 * 
 * @param user Ponteiro para o usuário.
 * @return Tipo de subscrição.
 */
gchar* get_tiposubscricao(const User *user);

/**
 * @brief Obtém a lista de identificadores das músicas preferidas do usuário.
 * 
 * @param user Ponteiro para o usuário.
 * @return Lista de identificadores das músicas preferidas.
 */
GList* get_idsdasmusicaspreferidas(const User *user);

#endif // USERS_H
