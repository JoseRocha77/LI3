#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashParser/hash.h" 
#include "Queries/Q1.h"    
#include "Queries/Q2.h"
#include "Queries/Q3.h"
#include "Entidades/users.h" 
#include "Entidades/musics.h"
#include "Entidades/artists.h"
#include "HashParser/hash.h" 
#include "Entidades/albuns.h"
#include "Entidades/history.h"
#include "Validacoes/validation.h"
#include "Utilitarias/utilitarias.h"




void carregar_artistas(const char *arquivo_csv) {
    FILE *arq = fopen(arquivo_csv, "r");
    if (!arq) {
        printf("Erro ao abrir o arquivo: %s\n", arquivo_csv);
        return;
    }

    FILE *erro_file = fopen("resultados/artists_errors.csv", "w");
    if (!erro_file) {
        printf("Erro ao criar o arquivo de erros\n");
        fclose(arq);
        return;
    }

    printf("Iniciando o carregamento de artistas...\n");
    char linha[2048];
    char cabeçalho[256]; // Armazena o cabeçalho
    int encontrou_erro = 0; // Flag para saber se houve erro

    // Lê a primeira linha (cabeçalho) e armazena
    if (fgets(cabeçalho, sizeof(cabeçalho), arq)) {
        cabeçalho[strcspn(cabeçalho, "\n")] = '\0'; // Remove o '\n'
    }

    while (fgets(linha, sizeof(linha), arq)) {
        linha[strcspn(linha, "\n")] = '\0';
        
        // Faz copia da linha original
        char linha_original[2048];
        strncpy(linha_original, linha, sizeof(linha_original));
        linha_original[sizeof(linha_original) - 1] = '\0';

        char *id = strtok(linha, ";");
        char *name = strtok(NULL, ";");
        strtok(NULL, ";");
        char *recipe_str = strtok(NULL, ";");
        char *id_constituents = strtok(NULL, ";");
        char *country = strtok(NULL, ";");
        char *type = strtok(NULL, ";");


        // Tirar aspas
        id = remove_aspas(id);
        name = remove_aspas(name);
        recipe_str = remove_aspas(recipe_str);
        country = remove_aspas(country);
        type = remove_aspas(type);
        id_constituents = remove_aspas(id_constituents);
        
        // Converte a string recipe_str para float
        float recipe_per_stream = recipe_str ? atof(recipe_str) : 0.0;

        GList *id_constituent_list = NULL;
        id_constituents = tratar_lista_id(id_constituents);
        if (id_constituents && strlen(id_constituents) > 0) {
            char *constituent_id = strtok(id_constituents, ",");
            while (constituent_id) {
                id_constituent_list = g_list_append(id_constituent_list, g_strdup(constituent_id));
                constituent_id = strtok(NULL, ",");
            }
       }
       free(id_constituents);
        
        //printf(" %d, %d\n",validar_artist_list(type, id_constituent_list),validar_type(type) );
        
        if (!validar_artist_list(type, id_constituent_list) || !validar_type(type)) {
            if (!encontrou_erro) {
                // Escreve o cabeçalho no arquivo de erros apenas uma vez
                fprintf(erro_file, "%s\n", cabeçalho);
                encontrou_erro = 1; // Marca que houve erro
            }
            // Escreve a linha inválida no arquivo de erros
            fprintf(erro_file, "%s\n", linha_original);
            g_list_free_full(id_constituent_list, g_free);
            continue;
        }

        // Cria e insere o artista
        Artist *novo_artista = create_artist(
            id,
            name,
            recipe_per_stream,
            id_constituent_list,
            country,
            type
        );
    
          if (!novo_artista) {
            printf("Erro ao criar artista: %s\n", id);
            g_list_free_full(id_constituent_list, g_free); // Liberar caso falhe
            continue;
        }
        
        inserir_artista(novo_artista);

        // printf("Artista carregado com sucesso:\n");
        // printf("ID: %s\n", id);
        // printf("Name: %s\n", name);
        // printf("Description: %s\n", description);
        // printf("Recipe_str: %s\n", recipe_str);
        // printf("Country: %s\n", country);
        // printf("Type: %s\n", type);
        // printf("Discografia: %d\n", calcular_duracao_total(novo_artista, tabela_musicas));
        // for (GList *l = id_constituent_list; l != NULL; l = l->next) {
        //     printf("%s ", (char *)l->data);
        // }
        // printf("\n");

        g_list_free_full(id_constituent_list, g_free);
    }

    fclose(arq);
    fclose(erro_file);
    printf("Carregamento de artistas concluído.\n");
}


void carregar_musicas(const char *arquivo_csv) {
    FILE *arq = fopen(arquivo_csv, "r");
    if (!arq) {
        printf("Erro ao abrir o arquivo: %s\n", arquivo_csv);
        return;
    }

    FILE *erro_file = fopen("resultados/musics_errors.csv", "w");
    if (!erro_file) {
        printf("Erro ao criar o arquivo de erros\n");
        fclose(arq);
        return;
    }

    printf("Iniciando o carregamento de músicas...\n");
    char linha[2048];
    char cabeçalho[256]; // Armazena o cabeçalho
    int encontrou_erro = 0; // Flag para identificar erros

    // Lê a primeira linha (cabeçalho) e armazena
    if (fgets(cabeçalho, sizeof(cabeçalho), arq)) {
        cabeçalho[strcspn(cabeçalho, "\n")] = '\0'; // Remove o '\n'
    }

    while (fgets(linha, sizeof(linha), arq)) {
        linha[strcspn(linha, "\n")] = '\0';

        // Faz cópia da linha original
        char linha_original[2048];
        strncpy(linha_original, linha, sizeof(linha_original));
        linha_original[sizeof(linha_original) - 1] = '\0';

        char *id = strtok(linha, ";");
        char *title = strtok(NULL, ";");
        char *artist_ids = strtok(NULL, ";");
        char *idalbum = strtok(NULL, ";");
        char *duration = strtok(NULL, ";");
        char *genre = strtok(NULL, ";");
        char *year = strtok(NULL, ";");


        // Tirar aspas
        id = remove_aspas(id);
        title = remove_aspas(title);
        artist_ids = remove_aspas(artist_ids);
        idalbum = remove_aspas(idalbum);
        duration = remove_aspas(duration);
        genre = remove_aspas(genre);
        year = remove_aspas(year);
        

        // Converter year para inteiro
        int ano = atoi(year);

        
        // Processar lista de IDs de artistas
        GList *idartists = NULL;
        artist_ids = tratar_lista_id(artist_ids);
        if(artist_ids){
            char *artist_id = strtok(artist_ids, ",");
            while (artist_id) {
                idartists = g_list_append(idartists, g_strdup(artist_id));
                artist_id = strtok(NULL, ",");
            }
            free(artist_ids);
        }

        //printf("%d, %d, %d\n",validar_duracao_musica(duration),validar_artists_id(idartists),validar_album_id(idalbum) );

        // Valida os campos
        if (!validar_duracao_musica(duration) || !validar_artists_id(idartists) || !validar_album_id(idalbum)) {
            if (!encontrou_erro) {
                fprintf(erro_file, "%s\n", cabeçalho);
                encontrou_erro = 1;
            }
            fprintf(erro_file, "%s\n", linha_original);
            g_list_free_full(idartists, g_free);
            continue;
        }
       
        // Criar nova música
        Music *nova_musica = create_music(
            id,
            title,
            idartists,
            idalbum,
            duration,
            genre,
            ano
        );
        inserir_musica(nova_musica);

        // Converter duração para segundos
        gint duracao_em_segundos = converter_duracao_para_segundos(duration);


        // Atualizar a discografia de cada artista
        for (GList *node = idartists; node != NULL; node = node->next) {
            const gchar *artist_id = (const gchar *)node->data;


            Artist *artista = buscar_artista(artist_id);
            if (artista) {
                set_discografia(artista,get_discografia(artista) + duracao_em_segundos);
                //printf("Discografia atualizada para o artista %s: %d segundos\n", artist_id, artista->discografia);
            }
        }
        

        // printf("Música carregada com sucesso:\n");
        // printf("  ID: %s\n", id);
        // printf("  Título: %s\n", title);
        // printf("  IDAlbum: %s\n", idalbum);
        // printf("  Duração: %s\n", duration);
        // printf("  Gênero: %s\n", genre);
        // printf("  Ano: %d\n", ano);
        // printf("  IDs de Artistas: ");
        // for (GList *l = idartists; l != NULL; l = l->next) {
        //     printf("%s ", (char *)l->data);
        // }
        // printf("\n");
        g_list_free_full(idartists, free);
    }

    fclose(arq);
    fclose(erro_file);
    printf("Carregamento de músicas concluído.\n");
}

void carregar_usuarios(const char *arquivo_csv) {
    FILE *arq = fopen(arquivo_csv, "r");
    if (!arq) {
        printf("Erro ao abrir o arquivo: %s\n", arquivo_csv);
        return;
    }

    FILE *erro_file = fopen("resultados/users_errors.csv", "w");
    if (!erro_file) {
        printf("Erro ao criar o arquivo de erros\n");
        fclose(arq);
        return;
    }

    printf("Iniciando o carregamento de utilizadores...\n");
    char linha[2048];
    char cabeçalho[512]; // Armazena o cabeçalho
    int encontrou_erro = 0; // Flag para identificar erros

    // Lê a primeira linha (cabeçalho) e armazena
    if (fgets(cabeçalho, sizeof(cabeçalho), arq)) {
        cabeçalho[strcspn(cabeçalho, "\n")] = '\0'; // Remove o '\n'
    }

    while (fgets(linha, sizeof(linha), arq)) {

        linha[strcspn(linha, "\n")] = '\0';
        
        // Faz copia da linha original
        char linha_original[2048];
        strncpy(linha_original, linha, sizeof(linha_original));
        linha_original[sizeof(linha_original) - 1] = '\0';

        char *username = strtok(linha, ";");
        char *email = strtok(NULL, ";");
        char *Pnome = strtok(NULL, ";");
        char *Apelido = strtok(NULL, ";");
        char *birth_date = strtok(NULL, ";");
        char *country = strtok(NULL, ";");
        char *subscription_type = strtok(NULL, ";");
        char *liked_songs_ids = strtok(NULL, ";");


        // Remover aspas de todos os campos
        username = remove_aspas(username);
        email = remove_aspas(email);
        Pnome = remove_aspas(Pnome);
        Apelido = remove_aspas(Apelido);
        birth_date = remove_aspas(birth_date);
        country = remove_aspas(country);
        subscription_type = remove_aspas(subscription_type);
        liked_songs_ids = remove_aspas(liked_songs_ids);

        // Processar os liked_songs_ids
        GList *idsdasmusicaspreferidas = NULL;
        liked_songs_ids = tratar_lista_id(liked_songs_ids); // Limpa os IDs das músicas
        if (liked_songs_ids) {
            char *id = strtok(liked_songs_ids, ",");
            while (id) {
                idsdasmusicaspreferidas = g_list_append(idsdasmusicaspreferidas, g_strdup(id));
                id = strtok(NULL, ",");
            }
            free(liked_songs_ids); // Liberar memória alocada por tratar_music_id
        }

        //printf(" %d, %d, %d, %d\n", validar_data_nascimento(birth_date), validar_email(email), validar_subscription_type(subscription_type), validar_liked_musics_id(idsdasmusicaspreferidas) );

        // Valida os campos
        if (!validar_data_nascimento(birth_date) || !validar_email(email) || !validar_subscription_type(subscription_type) || !validar_liked_musics_id(idsdasmusicaspreferidas)) {
            if (!encontrou_erro) {
                fprintf(erro_file, "%s\n", cabeçalho);
                encontrou_erro = 1;
            }
            fprintf(erro_file, "%s\n", linha_original);
            g_list_free_full(idsdasmusicaspreferidas, g_free);
            continue;
        }

        // Criar novo usuário
        User *novo_usuario = create_user(
            username, 
            email, 
            Pnome, 
            Apelido, 
            birth_date, 
            country, 
            subscription_type, 
            idsdasmusicaspreferidas
        );
        inserir_user(novo_usuario);

        // printf("Usuário carregado:\n");
        // printf("  Nome de usuário: %s\n", username);
        // printf("  Email: %s\n", email);
        // printf("  Primeiro nome: %s\n", Pnome);
        // printf("  Apelido: %s\n", Apelido);
        // printf("  Data de nascimento: %s\n", birth_date);
        // printf("  País: %s\n", country);
        // printf("  Tipo de assinatura: %s\n", subscription_type);
        // printf("  Músicas preferidas: ");
        // for (GList *l = idsdasmusicaspreferidas; l != NULL; l = l->next) {
        //     printf("%s ", (char *)l->data);
        // }
        // printf("\n");
        g_list_free_full(idsdasmusicaspreferidas, free);
    }

    fclose(arq);
    fclose(erro_file);
    printf("Carregamento de usuários concluído.\n");
}

void carregar_albuns(const char *arquivo_csv) {
    FILE *arq = fopen(arquivo_csv, "r");
    if (!arq) {
        printf("Erro ao abrir o arquivo: %s\n", arquivo_csv);
        return;
    }

    FILE *erro_file = fopen("resultados/albuns_errors.csv", "w");
    if (!erro_file) {
        printf("Erro ao criar o arquivo de erros\n");
        fclose(arq);
        return;
    }

    printf("Iniciando o carregamento de álbuns...\n");
    char linha[256];
    char cabeçalho[256]; // Armazena o cabeçalho
    int encontrou_erro = 0; // Flag para saber se houve erro

    // Lê a primeira linha (cabeçalho) e armazena
    if (fgets(cabeçalho, sizeof(cabeçalho), arq)) {
        cabeçalho[strcspn(cabeçalho, "\n")] = '\0'; // Remove o '\n'
    }

    while (fgets(linha, sizeof(linha), arq)) {
        linha[strcspn(linha, "\n")] = '\0';

        // Faz cópia da linha original
        char linha_original[256];
        strncpy(linha_original, linha, sizeof(linha_original));
        linha_original[sizeof(linha_original) - 1] = '\0';

        char *idalbuns = remove_aspas(strtok(linha, ";"));
        char *titulo = remove_aspas(strtok(NULL, ";"));
        char *idartists_str = remove_aspas(strtok(NULL, ";"));
        char *ano_str = remove_aspas(strtok(NULL, ";"));

        // Processa e limpa a lista de IDs de artistas
        char *idartists_limpo = tratar_lista_id(idartists_str);
        GList *idartists = NULL;
        if (idartists_limpo && strlen(idartists_limpo) > 0) {
            char *idartist = strtok(idartists_limpo, ",");
            while (idartist) {
                idartists = g_list_append(idartists, g_strdup(idartist));
                idartist = strtok(NULL, ",");
            }
        }
        free(idartists_limpo);


        // Converte o ano para inteiro
        gint ano = atoi(ano_str);

        // Validação do álbum (exemplo de validação: ID ou título vazio é inválido)
        if (!idalbuns || !titulo || strlen(idalbuns) == 0 || strlen(titulo) == 0) {
            if (!encontrou_erro) {
                // Escreve o cabeçalho no arquivo de erros apenas uma vez
                fprintf(erro_file, "%s\n", cabeçalho);
                encontrou_erro = 1; // Marca que houve erro
            }
            // Escreve a linha inválida no arquivo de erros
            fprintf(erro_file, "%s\n", linha_original);
            g_list_free_full(idartists, g_free);
            continue;
        }

        // Cria e insere o álbum
        Albuns *novo_album = create_album(
            idalbuns,
            titulo,
            idartists,
            ano
        );

        inserir_album(novo_album);


        // Incremetação de numero de albuns para cada artista
        for (GList *node = idartists; node != NULL; node = node->next) {
            const gchar *artist_id = (const gchar *)node->data;

            // Buscar o artista pelo ID
            Artist *artista = buscar_artista(artist_id);
            if (artista) {
                imcnumalbuns(artista);
                //printf("Número de albuns atualizado para o artista %s: %d albuns\n", artist_id, artista->numalbuns);
            }
        }

        // // Prints de verificação
        // printf("Álbum carregado com sucesso:\n");
        // printf("ID: %s\n", idalbuns);
        // printf("Título: %s\n", titulo);
        // printf("Ano: %d\n", ano);
        // printf("Artistas: ");
        // for (GList *l = idartists; l != NULL; l = l->next) {
        //     printf("%s ", (char *)l->data);
        // }
        // printf("\n");

        // Libera as listas locais (o create_album já copia elas)
        g_list_free_full(idartists, g_free);
    }

    fclose(arq);
    fclose(erro_file);
    printf("Carregamento de álbuns concluído.\n");
}


void carregar_history(const char *arquivo_csv) {
    FILE *arq = fopen(arquivo_csv, "r");
    if (!arq) {
        printf("Erro ao abrir o arquivo: %s\n", arquivo_csv);
        return;
    }

    FILE *erro_file = fopen("resultados/history_errors.csv", "w");
    if (!erro_file) {
        printf("Erro ao criar o arquivo de erros\n");
        fclose(arq);
        return;
    }

    printf("Iniciando o carregamento do histórico...\n");
    char linha[256];
    char cabeçalho[256]; // Armazena o cabeçalho
    int encontrou_erro = 0; // Flag para saber se houve erro

    // Lê a primeira linha (cabeçalho) e armazena
    if (fgets(cabeçalho, sizeof(cabeçalho), arq)) {
        cabeçalho[strcspn(cabeçalho, "\n")] = '\0'; // Remove o '\n'
    }

    while (fgets(linha, sizeof(linha), arq)) {
        linha[strcspn(linha, "\n")] = '\0';

        // Faz cópia da linha original
        char linha_original[256];
        strncpy(linha_original, linha, sizeof(linha_original));
        linha_original[sizeof(linha_original) - 1] = '\0';

        char *idhistory = strtok(linha, ";");
        char *iduser = strtok(NULL, ";");
        char *idmusic = strtok(NULL, ";");
        char *timestamp = strtok(NULL, ";");
        char *duration = strtok(NULL, ";");
        char *platform = strtok(NULL, ";");

        // Remove aspas das strings
        idhistory = remove_aspas(idhistory);
        iduser = remove_aspas(iduser);
        idmusic = remove_aspas(idmusic);
        timestamp = remove_aspas(timestamp);
        duration = remove_aspas(duration);
        platform = remove_aspas(platform);

        // Validação do histórico (exemplo de validação: campos essenciais não podem ser nulos ou vazios)
        if (!validar_platform(platform)) {
            if (!encontrou_erro) {
                // Escreve o cabeçalho no arquivo de erros apenas uma vez
                fprintf(erro_file, "%s\n", cabeçalho);
                encontrou_erro = 1; // Marca que houve erro
            }
            // Escreve a linha inválida no arquivo de erros
            fprintf(erro_file, "%s\n", linha_original);
            continue;
        }


        // Cria e insere o histórico
        History *novo_history = create_history(
            idhistory,
            iduser,
            idmusic,
            timestamp,
            duration,
            platform
        );

        inserir_history(novo_history);
       
        // Incrementação do nº de reproduçoẽs de uma música
        Music *musica = buscar_musica(idmusic);
        if (musica){
            imcreproducoes(musica);

          // Cálculo da receita de cada artista   
          for (GList *node = get_idartistsm(musica); node != NULL; node = node->next) {
            const gchar *artist_id = (const gchar *)node->data;

            
            Artist *artista = buscar_artista(artist_id);
            if (artista) {                                                                                     // verfica se é um artista válido
                if ((g_strcmp0(get_type(artista), "group") == 0)){                                             // verifica se o id_artista se trata de um grupo 
                    gint num_constituents = get_num_constituents(artista);                                     // calcula o número de aristas que constituem o grupo 
                    imcrecipe(artista, get_recipe_per_stream(artista));                                        // Incrementa a receita do grupo tendo em conta  o recipe_per_stream
                    for (GList *consti = get_id_constituent(artista); consti != NULL; consti = consti->next){  // Ciclo for para percorrer a lista dos constituintes do grupo  
                        const gchar *artistg_id = (const gchar *)consti->data;

                        Artist *artistag = buscar_artista(artistg_id);
                        if (artistag) {                                                                        // Verifica se o artista elemento do grupo é válido
                            /*printf("receita artista %s do grupo %s: %.2f\n",
                            get_idartista(artistag), get_idartista(artista), get_recipe(artistag));
                            */
                            imcrecipe(artistag, (get_recipe_per_stream(artista) / num_constituents));          // Incrementa a receita do elemento divdindo a receita do grupo pelo numero de eeents
                            /*printf("receita por stream grupo: %.2f; receita membro grupo: %.2f; nº de membros grupo: %d\n",
                             get_recipe_per_stream(artista), get_recipe(artistag), num_constituents);
                            */
                        }
                    }
                }
                else {
                    imcrecipe(artista, get_recipe_per_stream(artista));                                        // Caso seja um artista individual incrementa a receita tendo em conta o seu recipe_per_stream
                }
            }
        }
    }

        // // Prints de verificação
        // printf("Histórico carregado com sucesso:\n");
        // printf("ID Histórico: %s\n", idhistory);
        // printf("ID Usuário: %s\n", iduser);
        // printf("ID Música: %s\n", idmusic);
        // printf("Timestamp: %s\n", timestamp);
        // printf("Duração: %s\n", duration);
        // printf("Plataforma: %s\n", platform);

    }

    fclose(arq);
    fclose(erro_file);
    printf("Carregamento do histórico concluído.\n");
}
