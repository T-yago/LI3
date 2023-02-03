#include <stdio.h>

#include <stdbool.h>

#include <stdlib.h>

#include <string.h>

#include <glib.h>

#include "../includes/queries_handler.h"

#include "../includes/catalogs.h"

#include "../includes/query1.h"

#include "../includes/query2.h"

#include "../includes/query3.h"

#include "../includes/query4.h"

#include "../includes/query5.h"

#include "../includes/query6.h"

#include "../includes/query7.h"

#include "../includes/query8.h"

#include "../includes/query9.h"

#include "../includes/data.h"

/**
 * @brief Gere os catálogos e envia as suas referências para as queries
 *   
 * @param input Ficheiro com input para as queries
 * @param catalogs Estrutura com todos os catálogos
 */
void queries_handler (char * input, Catalogs* catalogs) {


  Catalog_Users* catalog_users =  get_users_catalog (catalogs);
  Catalog_Drivers* catalog_drivers =  get_drivers_catalog (catalogs);
  Catalog_Rides* catalog_rides = get_rides_catalog (catalogs);
  Catalog_Cities* catalog_cities =  get_cities_catalog (catalogs);

  // lê o ficheiro de input das queries
  FILE * file;
  char * info_1;
  char * info_2;
  char * info_3;
  int numb_query, n = 1;
  size_t len;
  char * line = NULL;
  file = fopen(input, "r");
  do {
    while (getline( & line, & len, file) != -1) {
      numb_query = atoi(strtok( line, " "));
      info_1 = strtok(NULL, "  \n");
      info_2 = strtok (NULL, " \n");
      info_3 = strtok(NULL, "\n");

      switch (numb_query) {
      case 1:
        query1_main(info_1, catalog_users, catalog_drivers, n);
        break;
      case 2:
        query2(catalog_drivers, info_1, n);
        break;
      case 3:
        query3(catalog_users, info_1, n);
        break;
      case 4:
        query4(catalog_cities,info_1,n);
        break;
      case 5:
        query5(info_1,info_2,catalog_drivers,catalog_rides,n);
        break;
      case 6:
        query6(info_1,info_2,info_3,catalog_cities, catalog_rides,n);
        break;
      case 7:
        query7(info_1, info_2, catalog_cities, catalog_drivers, n);
        break;
      case 8:
       query8 (info_1[0], atoi(info_2), catalog_rides, catalog_users, catalog_drivers, n);
        break;
      case 9:
        query9(catalog_rides, info_1, info_2, n);
        break;
      }
      n++;
    }
  } while (!feof(file));
 
  free (line);
  fclose(file);  
}