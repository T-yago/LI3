#ifndef CITIES_SERVICES_H
#define CITIES_SERVICES_H

#include "../includes/cities.h"


int compare2(const void * a, const void * b);
void sort_array_avaliacoes_city (Catalog_Cities * catalog_cities, char * city_to_check);
uint get_id_driver_from_ordered_array (Catalog_Cities * catalog_cities, char * city_to_check, int index);
double get_aval_med_from_ordered_array (Catalog_Cities * catalog_cities, char * city_to_check, int index);


#endif