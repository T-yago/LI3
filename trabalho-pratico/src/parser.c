#include <stdio.h>

#include <stdbool.h>

#include <stdlib.h>

#include <string.h>

#include <glib.h>

#include "../includes/parser.h"

#include "../includes/users.h"

#include "../includes/drivers.h"

#include "../includes/query1.h"

#include "../includes/query2.h"

#include "../includes/rides.h"

#include "../includes/query3.h"

#include "../includes/query4.h"

#include "../includes/query5.h"

void parser_input(char * pathfiles, char * input) {
  Catalog_Users * catalog_users = users_catalog(pathfiles);
  initHash_users(catalog_users);
  Catalog_Drivers * catalog_drivers = drivers_catalog(pathfiles);
  initHash_drivers(catalog_drivers);
  Catalog_Cities * catalog_cities = init_hash_cities();
  Catalog_Rides * catalog_rides = rides_catalog(catalog_users, catalog_drivers, catalog_cities, pathfiles);

  FILE * file;
  char * info_1;
  char * info_2;
  int numb_query, n = 1;
  size_t len;
  char * line = NULL;
  file = fopen(input, "r");
  do {
    while (getline( & line, & len, file) != -1) {
      numb_query = atoi(strtok( line, " "));
      info_1 = strtok(NULL, " \n");
      info_2 = strtok (NULL, "\n");

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
  free (line);
  fclose(file);
  free_hash_users (catalog_users);
  free_hash_drivers (catalog_drivers);
  free_hash_rides (catalog_rides);
  free_hash_cities (catalog_cities);
  free (catalog_users);
  free (catalog_drivers);
  free (catalog_cities);
  free (catalog_rides);
}