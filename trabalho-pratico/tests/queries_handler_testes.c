#include <stdio.h>

#include <stdbool.h>

#include <stdlib.h>

#include <string.h>

#include <glib.h>

#include <time.h>

#include "../includes/queries_handler_testes.h"

#include "../includes/catalogs.h"

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
 * @brief Função que lê os comandos de input e cexcuta as respectivas queries, para além disso calcula os tempos das queries e armazena no array times_query
 * 
 * @param input Ficheiro com input para as queries
 * @param catalogs Estrutura com todos os catálogos
 * @param times_query array que armazena o tempo de execução de cada query
 */
void queries_handler_testes(char * input, Catalogs * catalogs, double* times_query) {

  clock_t start, end;

  Catalog_Users* catalog_users =  get_users_catalog (catalogs);
  Catalog_Drivers* catalog_drivers =  get_drivers_catalog (catalogs);
  Catalog_Rides* catalog_rides = get_rides_catalog (catalogs);
  Catalog_Cities* catalog_cities =  get_cities_catalog (catalogs);


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
}