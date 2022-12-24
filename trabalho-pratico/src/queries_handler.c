#include <stdio.h>

#include <stdbool.h>

#include <stdlib.h>

#include <string.h>

#include <glib.h>

#include "../includes/queries_handler.h"

#include "../includes/users.h"

#include "../includes/drivers.h"

#include "../includes/rides.h"

#include "../includes/cities.h"

#include "../includes/query1.h"

#include "../includes/query2.h"


#include "../includes/query3.h"

#include "../includes/query4.h"

#include "../includes/query5.h"

#include "../includes/query6.h"

#include "../includes/data.h"

void queries_handler (char * pathfiles, char * input) {
  
  // criação dos catálogos
  Catalog_Users * catalog_users = users_catalog(pathfiles);
  initHash_users(catalog_users);
  Catalog_Drivers * catalog_drivers = drivers_catalog(pathfiles);
  initHash_drivers(catalog_drivers);
  Catalog_Rides * catalog_rides = rides_catalog(pathfiles);
  Catalog_Cities * catalog_cities = cities_catalog ();
  fill_data (catalog_users,catalog_drivers,catalog_rides,catalog_cities);
  
  // criação das estruturas auxiliares para as queries
  top_N_drivers (catalog_drivers);
  top_N_users (catalog_users);

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
        break;
      case 8:
        break;
      case 9:
        break;
      }
      n++;
    }
  } while (!feof(file));
 
  // liberta a memória associada aos catálogos
  free (line);
  fclose(file);
  free_users_catalog (catalog_users);
  free_drivers_catalog (catalog_drivers);
  free_rides_catalog (catalog_rides);
  free_cities_catalog (catalog_cities);
}