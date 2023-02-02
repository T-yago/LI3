#include <stdio.h>

#include <stdbool.h>

#include <stdlib.h>

#include <string.h>

#include <glib.h>

#include <time.h>

#include "../includes/queries_handler_testes.h"

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

#include "../includes/query7.h"

#include "../includes/query8.h"

#include "../includes/query9.h"

#include "../includes/data.h"

/**
 * @brief Gere os catálogos e envia as suas referências para as queries e para além disso calcula os tempos das queries e armazena no array times_query
 * 
 * @param pathfiles String com o caminho dos ficheiros que são lidos
 * @param input Ficheiro com input para as queries
 * @param times_query array que armazena o tempo de execução de cada query
 */
void queries_handler_testes(char * pathfiles, char * input, double* times_query) {

  clock_t start, end;

  //criação dos catálogos
  start = clock();
  Catalog_Users * catalog_users = users_catalog(pathfiles);
  initHash_users(catalog_users);
  end = clock();
  printf("\nCatalog_users: %.6fs\n",  ((double)(end - start)) / CLOCKS_PER_SEC); 

  start = clock();
  Catalog_Drivers * catalog_drivers = drivers_catalog(pathfiles);
  init_array_drivers(catalog_drivers);
  end = clock();
  printf("\nArray_drivers: %.6fs\n",  ((double)(end - start)) / CLOCKS_PER_SEC); 

  start = clock();
  Catalog_Rides * catalog_rides = rides_catalog(pathfiles);
  end = clock();
  printf("\nCatalog_rides: %.6fs\n",  ((double)(end - start)) / CLOCKS_PER_SEC); 

  //init_array_genders (catalog_rides);
  start = clock();
  Catalog_Cities * catalog_cities = cities_catalog ();
  fill_data (catalog_users,catalog_drivers,catalog_rides,catalog_cities);
  end = clock();
  printf("\nCatalog_cities: %.6fs\n",  ((double)(end - start)) / CLOCKS_PER_SEC); 

  //criação das estruturas auxiliares para as queries
  start = clock();
  top_N_drivers (catalog_drivers);  // talvez mudar de sítio
  top_N_users (catalog_users);
  end = clock();
  printf("\nTopNdrivers e TopNusers: %.6fs\n",  ((double)(end - start)) / CLOCKS_PER_SEC); 

  //lê o ficheiro de input das queries
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
        start = clock();
        query1_main(info_1, catalog_users, catalog_drivers, n);
        end = clock();
        times_query[numb_query - 1] += ((double)(end - start)) / CLOCKS_PER_SEC; 
        break;
      case 2:
        start = clock();
        query2(catalog_drivers, info_1, n);
        end = clock();
        times_query[numb_query - 1] += ((double)(end - start)) / CLOCKS_PER_SEC;
        break;
      case 3:
        start = clock();
        query3(catalog_users, info_1, n);
        end = clock();
        times_query[numb_query - 1] += ((double)(end - start)) / CLOCKS_PER_SEC;        
        break;
      case 4:
        start = clock();
        query4(catalog_cities,info_1,n);
        end = clock();
        times_query[numb_query - 1] += ((double)(end - start)) / CLOCKS_PER_SEC;        
        break;
      case 5:
        start = clock();
        query5(info_1,info_2,catalog_drivers,catalog_rides,n);
        end = clock();
        times_query[numb_query - 1] += ((double)(end - start)) / CLOCKS_PER_SEC;
        break;
      case 6:
        start = clock();
        query6(info_1,info_2,info_3,catalog_cities, catalog_rides,n);
        end = clock();
        times_query[numb_query - 1] += ((double)(end - start)) / CLOCKS_PER_SEC;
        break;
      case 7:
        start = clock();
        query7(info_1, info_2, catalog_cities, catalog_drivers, n);
        end = clock();
        times_query[numb_query - 1] += ((double)(end - start)) / CLOCKS_PER_SEC;
        break;
      case 8:
        start = clock();
        query8 (info_1[0], atoi(info_2), catalog_rides, catalog_users, catalog_drivers, n);
        end = clock();
        times_query[numb_query - 1] += ((double)(end - start)) / CLOCKS_PER_SEC;
        break;
      case 9:
        start = clock();
        query9(catalog_rides, info_1, info_2, n);
        end = clock();
        times_query[numb_query - 1] += ((double)(end - start)) / CLOCKS_PER_SEC;
        break;
      }
      n++;
    }
  } while (!feof(file));
 
  //liberta a memória associada aos catálogos
  free (line);
  fclose (file);
  free_users_catalog (catalog_users);
  free_drivers_catalog (catalog_drivers);
  free_rides_catalog (catalog_rides);
  free_cities_catalog (catalog_cities);
}