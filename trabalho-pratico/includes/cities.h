#ifndef CITIES_H
#define CITIES_H

#include <stdbool.h>
#include "../includes/rides.h"

typedef struct catalog_cities Catalog_Cities;
typedef struct city City;

Catalog_Cities * cities_catalog ();
void fill_cities_catalog (Catalog_Cities * cities_catalog , char * city_to_check, double total_gasto_por_ride, unsigned int ride_id);
void free_cities_catalog (Catalog_Cities * catalog_cities);
unsigned int get_num_rides_city (Catalog_Cities * catalog_cities, char * city);
double get_total_gasto_city (Catalog_Cities* catalog_cities, char * city);
bool is_in_hash_cities (Catalog_Cities * catalog_cities, char* city);
void fill_array_rides (Catalog_Cities * catalog_cities, unsigned short int total_dist, char * city);
double get_average_distance (Catalog_Cities* catalog_cities, Catalog_Rides* catalog_rides,char * city, unsigned short int dateInf, unsigned short int dateSup);

#endif