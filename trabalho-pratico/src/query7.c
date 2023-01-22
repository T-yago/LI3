#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>

#include "../includes/drivers.h"
#include "../includes/cities.h"
#include "../includes/cities_services.h"
#include "../includes/query7.h"

char* int_to_string(int x) {
  char* str = malloc(13);
  snprintf(str, 13, "%012d", x);
  return str;
}

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
      char * name = get_driver_name(catalog_drivers, id_driver - 1);
      double avaliacao_media = get_aval_med_from_ordered_array(catalog_cities, city_query, i);
      fprintf(output, "%012d;""%s;""%.3f\n", id_driver, name, avaliacao_media);
      free (name);
    }

    fclose(output);
    free (city_query);

  } 
}