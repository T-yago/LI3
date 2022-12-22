#ifndef CITIES_H
#define cITIES_H

typedef struct catalog_cities Catalog_Cities;
typedef struct city City;

Catalog_Cities * cities_catalog ();
void insert_cities_hash (Catalog_Cities * cities_catalog , char * city, double total_gasto_por_ride);
void free_cities_catalog (Catalog_Cities * catalog_cities);
uint get_num_rides_city (Catalog_Cities * catalog_cities, char * city);
double get_total_gasto_city (Catalog_Cities* catalog_cities, char * city);
bool is_in_hash_cities (Catalog_Cities * catalog_cities, char* city);


#endif