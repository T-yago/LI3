#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>

#include "../includes/drivers.h"
#include "../includes/cities.h"
#include "../includes/query7.h"


/**
 * @brief Top N condutores numa determinada cidade
 * 
 * @param N Número de condutores a apresentar
 * @param city Cidade em questão
 * @param catalog_cities Catálogo das cidades
 * @param catalog_drivers Catálogo dos drivers
 * @param n Número do ficheiro de output a gerar
 */
void query7 (char * N, char * city, Catalog_Cities * catalog_cities, Catalog_Drivers * catalog_drivers, int n){
  int numb = atoi(N);
  
  char buffer[256];
  snprintf(buffer, 256, "Resultados/command%d_output.txt", n);
  FILE * output = fopen(buffer, "w");
  if (!is_in_hash_cities (catalog_cities,city)) fclose (output);
  else {
    char* city_query = strdup (city);

    for (int i = 0; i < numb; i++) {
      uint id_driver = get_id_driver_from_ordered_array (catalog_cities, city_query, i);
      
      if (get_driver_acc_Status (catalog_drivers, id_driver -1) == true) 
      {
        char * name = get_driver_name(catalog_drivers, id_driver - 1);
        double avaliacao_media = get_aval_med_from_ordered_array(catalog_cities, city_query, i);
        fprintf(output, "%012d;""%s;""%.3f\n", id_driver, name, avaliacao_media);
        free (name);
      }
      else numb++;
    }

    fclose(output);
    free (city_query);

  } 
}