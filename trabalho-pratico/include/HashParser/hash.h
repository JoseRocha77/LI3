#ifndef HASH_H
#define HASH_H

#include <glib.h>
#include "Entidades/users.h" 
#include "Entidades/musics.h"
#include "Entidades/artists.h"
#include "Entidades/albuns.h"
#include "Entidades/history.h"

/**
 * @brief Tabela de hash para armazenar artistas.
 */
extern GHashTable *tabela_artistas;

/**
 * @brief Tabela de hash para armazenar músicas.
 */
extern GHashTable *tabela_musicas;

/**
 * @brief Tabela de hash para armazenar utilizadores.
 */
extern GHashTable *tabela_utilizadores;

/**
 * @brief Tabela de hash para armazenar histórico.
 */
extern GHashTable *tabela_history;

/**
 * @brief Tabela de hash para armazenar albuns.
 */
extern GHashTable *tabela_albuns;


/**
 * @brief Inicializa as tabelas de hash para entidades do sistema.
 * 
 * Esta função cria e inicializa as tabelas de hash que serão usadas para armazenar
 * artistas, músicas, utilizadores, albuns e histórico. Deve ser chamada antes de usar qualquer uma das tabelas.
 */
void inicializar_tabelas();

/**
 * @brief Libera a memória associada às tabelas de hash.
 * 
 * Esta função libera todos os recursos alocados pelas tabelas de hash.
 * Deve ser chamada ao finalizar o uso das tabelas.
 */
void liberar_tabelas();

#endif // HASH_H
