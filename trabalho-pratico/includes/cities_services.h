#ifndef CITIES_SERVICES_H
#define CITIES_SERVICES_H

#include "../includes/cities.h"

typedef struct catalog_cities Catalog_Cities;
typedef struct avaliacao_media_driver Avaliacao_media_driver;
typedef struct city City;


int compare2(const void * a, const void * b);
void sort_array_avaliacoes_city (Catalog_Cities * catalog_cities, char * city_to_check);
uint get_id_driver_from_ordered_array (Catalog_Cities * catalog_cities, char * city_to_check, int index);
double get_aval_med_from_ordered_array (Catalog_Cities * catalog_cities, char * city_to_check, int index);


#endif