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

void parser_input(char * pathfiles, char * input) {
  Catalog_Users * hash_users = users_catalog(pathfiles);
  initHash_users(hash_users);
  Catalog_Drivers * hash_drivers = drivers_catalog(pathfiles);
  initHash_drivers(hash_drivers);
  Catalog_Cities * catalog_cities = init_hash_cities();
  rides_catalog(hash_users, hash_drivers, catalog_cities, pathfiles);

  FILE * file;
  char * aux;
  char * info;
  int numb_query, n = 1;
  size_t len;
  char * line = NULL;
  file = fopen(input, "r");
  do {
    while (getline( & line, & len, file) != -1) {
      char * line_aux1 = line;
      aux = strsep( & line_aux1, " ");
      numb_query = atoi(aux);
      char * line_aux2 = line_aux1;
      info = strsep( & line_aux2, " \n");
      switch (numb_query) {
      case 1:
        query1_main(info, hash_users, hash_drivers, n);
        break;
      case 2:
        query2(hash_drivers, info, n);
        break;
      case 3:
        query3(hash_users, info, n);
        break;
      case 4:
        query4(catalog_cities,info,n);
        break;
      case 5:
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
  free_hash_users (hash_users);
  free_hash_drivers (hash_drivers);
  free (hash_drivers);
  free (hash_users);
}