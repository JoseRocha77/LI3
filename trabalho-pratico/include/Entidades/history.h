#ifndef HISTORY_H
#define HISTORY_H

#include <glib.h>

/**
 * @brief Estrutura representando o histórico de interações de um usuário.
 * 
 * Contém os seguintes campos:
 * - `idhistory`: Identificador único do histórico.
 * - `iduser`: Identificador do usuário associado.
 * - `idmusic`: Identificador da música associada.
 * - `timestamp`: Data e hora da interação.
 * - `duration`: Duração da interação.
 * - `platform`: Plataforma usada (e.g., desktop, mobile).
 */
typedef struct His History;

// Funções Setter
/**
 * @brief Define o identificador do histórico.
 * 
 * @param history Ponteiro para a estrutura History.
 * @param idhistory Identificador do histórico (string).
 */
void set_idhistory(History *history, const gchar *idhistory);

/**
 * @brief Define o identificador do usuário associado ao histórico.
 * 
 * @param history Ponteiro para a estrutura History.
 * @param iduser Identificador do usuário (string).
 */
void set_iduser(History *history, const gchar *iduser);

/**
 * @brief Define o identificador da música associada ao histórico.
 * 
 * @param history Ponteiro para a estrutura History.
 * @param idmusic Identificador da música (string).
 */
void set_idmusic(History *history, const gchar *idmusic);

/**
 * @brief Define o timestamp do histórico.
 * 
 * @param history Ponteiro para a estrutura History.
 * @param timestamp Timestamp do histórico (string).
 */
void set_timestamp(History *history, const gchar *timestamp);

/**
 * @brief Define a duração do histórico.
 * 
 * @param history Ponteiro para a estrutura History.
 * @param duration Duração do histórico (string).
 */
void set_duration(History *history, const gchar *duration);

/**
 * @brief Define a plataforma associada ao histórico.
 * 
 * @param history Ponteiro para a estrutura History.
 * @param platform Plataforma associada ao histórico (string).
 */
void set_platform(History *history, const gchar *platform);

// Funções de criação e liberação

/**
 * @brief Cria um novo registro de histórico.
 * 
 * @param idhistory Identificador único do histórico.
 * @param idartista Identificador do artista associado.
 * @param idmusic Identificador da música associada.
 * @param timestamp Data e hora da interação.
 * @param duration Duração da interação.
 * @param platform Plataforma usada (e.g., desktop, mobile).
 * @return Ponteiro para a estrutura History recém-criada.
 */
History* create_history(const gchar *idhistory, const gchar *idartista, const gchar *idmusic, const gchar *timestamp, const gchar *duration, const gchar *platform);

/**
 * @brief Libera a memória associada a um registro de histórico.
 * 
 * @param history Ponteiro para o histórico a ser liberado.
 */
void liberar_history(History *history);

// Funções de manipulação

/**
 * @brief Insere um registro de histórico em uma coleção.
 * 
 * @param history Ponteiro para o registro de histórico a ser inserido.
 */
void inserir_history(History *history);

/**
 * @brief Busca um registro de histórico pelo identificador.
 * 
 * @param idhistory Identificador único do histórico.
 * @return Ponteiro para o histórico encontrado, ou NULL se não for encontrado.
 */
History* buscar_history(const gchar *idhistory);

/**
 * @brief Remove um registro de histórico de uma coleção.
 * 
 * @param idhistory Identificador único do histórico.
 * @return TRUE se o histórico foi removido com sucesso, FALSE caso contrário.
 */
gboolean remover_history(const gchar *idhistory);

// Funções getters

/**
 * @brief Obtém o identificador único de um registro de histórico.
 * 
 * @param history Ponteiro para o histórico.
 * @return Identificador único do histórico.
 */
const gchar* get_idhistory(History *history);

/**
 * @brief Obtém o identificador do usuário associado a um registro de histórico.
 * 
 * @param history Ponteiro para o histórico.
 * @return Identificador do usuário.
 */
const gchar* get_iduser(History *history);

/**
 * @brief Obtém o identificador da música associada a um registro de histórico.
 * 
 * @param history Ponteiro para o histórico.
 * @return Identificador da música.
 */
const gchar* get_idmusic(History *history);

/**
 * @brief Obtém a data e hora associadas a um registro de histórico.
 * 
 * @param history Ponteiro para o histórico.
 * @return Data e hora da interação.
 */
const gchar* get_timestamp(History *history);

/**
 * @brief Obtém a duração associada a um registro de histórico.
 * 
 * @param history Ponteiro para o histórico.
 * @return Duração da interação.
 */
const gchar* get_duration(History *history);

/**
 * @brief Obtém a plataforma usada em um registro de histórico.
 * 
 * @param history Ponteiro para o histórico.
 * @return Plataforma usada.
 */
const gchar* get_platform(History *history);

/**
 * @brief Obtém o dia de audição de um registro de histórico.
 * 
 * @param history Ponteiro para o histórico.
 * @return Dia da audição.
 */
gchar* get_dia_audicao(const gchar* timestamp) ;

/**
 * @brief Obtém a duração de audição de um registro de histórico.
 * 
 * @param history Ponteiro para o histórico.
 * @return Duração da audição.
 */
gchar* get_hora_audicao(const gchar* timestamp);


#endif // HISTORY_H
