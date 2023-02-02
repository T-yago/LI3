#include <stdio.h>

#include <glib.h>

#include "../includes/query3.h"

#include "../includes/rides.h"

#include "../includes/users.h"

#include "../includes/drivers.h"


/**
 * @brief Lista os N users com maior distância viajada
 * 
 * @param catalog_users Catálogo dos users
 * @param info String com o número de users pedidos
 * @param n Número do ficheiro de output a gerar
 */
void query3(Catalog_Users * catalog_users, char * info, int n) {
  int numb = atoi(info);
  char* id = NULL;
  char* name = NULL;
  unsigned short int distance = 0;
  
  char buffer[256];
  snprintf(buffer, 256, "Resultados/command%d_output.txt", n);

  FILE * output = fopen(buffer, "w");
  for (int i = 0; i < numb; i++) {
    id = get_top_N_users_id (catalog_users,i);
    name = getNameUser (catalog_users,id);
    distance = get_top_N_users_distance (catalog_users,i);
        
      fprintf(output, "%s;"
      "%s;"
      "%d\n", id, name, distance);
      free (name);
      free (id);
  }
  fclose(output);
}