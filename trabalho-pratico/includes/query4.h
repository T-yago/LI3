#ifndef QUERY4_H
#define QUERY4_H

#include <glib.h>
#include <stdbool.h>

typedef struct catalog_cities Catalog_Cities;
typedef struct cities Cities;


int check_city (Catalog_Cities * cities_catalog, char * city);
Catalog_Cities *  init_hash_cities ();
void hash_cities_get_n_viagens (Catalog_Cities * catalog_cities, char * city);
void insert_cities_hash (Catalog_Cities * cities_catalog , char * city, double total_gasto_por_ride);
void query4 (Catalog_Cities * catalog_cities, char * city , int n);
void free_hash_cities (Catalog_Cities * catalog_cities);


#endif
