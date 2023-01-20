#ifndef CITIES_H
#define CITIES_H

#include <stdbool.h>
#include "../includes/rides.h"

typedef struct catalog_cities Catalog_Cities;
typedef struct avaliacao_media_driver Avaliacao_media_driver;
typedef struct aval_media_array_ordenado Aval_media_array_ordenado;
typedef struct city City;

Catalog_Cities * cities_catalog ();
void fill_cities_catalog (Catalog_Cities * catalog_cities, char * city_to_check, double total_gasto_por_ride,uint size_drivers, uint driver_id, unsigned short int score_driver, unsigned int ride_id);
void free_cities_catalog (Catalog_Cities * catalog_cities);
unsigned int get_num_rides_city (Catalog_Cities * catalog_cities, char * city);
double get_total_gasto_city (Catalog_Cities* catalog_cities, char * city);
bool is_in_hash_cities (Catalog_Cities * catalog_cities, char* city);
void fill_array_rides (Catalog_Cities * catalog_cities, unsigned short int total_dist, char * city);
double get_average_distance (Catalog_Cities* catalog_cities, Catalog_Rides* catalog_rides,char * city, unsigned short int dateInf, unsigned short int dateSup);

int compare2(const void * a, const void * b);
void sort_array_avaliacoes_city (Catalog_Cities * catalog_cities, char * city_to_check);
double get_aval_med_from_ordered_array (Catalog_Cities * catalog_cities, char * city_to_check, int index);
uint get_id_driver_from_ordered_array (Catalog_Cities * catalog_cities, char * city_to_check, int index);






#endif