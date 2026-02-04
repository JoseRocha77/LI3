#include <stdio.h>
#include <time.h>
#include <glib.h>
#include "Validacoes/validation.h"
#include "HashParser/hash.h" 
#include "Entidades/users.h"
#include "Utilitarias/utilitarias.h"
#include "Entidades/artists.h"

// Função para listar o resumo de um utilizador
void listar_resumo_utilizador(const gchar *utilizador_id, FILE *output_file) {
    
    User *user = buscar_user(utilizador_id);

   

    if (user) {
    // Escreve o resumo do utilizador no arquivo de saída
    fprintf(output_file, "%s;%s;%s;%d;%s\n",
            get_email(user), get_Pnome(user), get_Apelido(user),
            calcular_idade(get_datadenascimento(user)), get_countryU(user));
    //printf("Resumo do utilizador escrito no arquivo: %s;%s;%s;%d;%s\n", 
    //        get_email(user), get_Pnome(user), get_Apelido(user), 
    //        calcular_idade(get_datadenascimento(user)), get_country(user));
} else {
    //printf("Utilizador não encontrado.\n");
    fprintf(output_file, "\n");
}

}


// Função para listar o resumo de um artista
void listar_resumo_artista(const gchar *artista_id, FILE *output_file) {
    
    Artist *artist = buscar_artista(artista_id);

    

    if (artist) {
    // Escreve o resumo do utilizador no arquivo de saída
    fprintf(output_file, "%s;%s;%s;%d;%.2f\n",
            get_name(artist), get_type(artist), get_country(artist), get_numalbuns(artist), get_recipe(artist));
            
    //printf("Resumo do artista escrito no arquivo: %s;%s;%d\n", 
    //        get_name(artist), get_country(country), get_numalbuns(artist));
    
} else {
    //printf("Utilizador não encontrado.\n");
    fprintf(output_file, "\n");
}
}