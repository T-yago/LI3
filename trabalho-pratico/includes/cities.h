#include "../includes/rides.h"
#include "../includes/drivers.h"
#include "../includes/rides_services.h"
#include "../includes/query1.h"


typedef struct catalog_cities Catalog_Cities;
typedef struct avaliacao_media_driver Avaliacao_media_driver;
typedef struct city City;

Catalog_Cities * cities_catalog ();
void fill_cities_catalog (Catalog_Cities * catalog_cities, Catalog_Rides* catalog_rides, Catalog_Drivers* catalog_drivers);
void free_cities_catalog (Catalog_Cities * catalog_cities);
double get_total_gasto_city (Catalog_Cities* catalog_cities, char * city);
bool is_in_hash_cities (Catalog_Cities * catalog_cities, char* city);
int get_array_ids_city_length (Catalog_Cities* catalog_cities, char* city);
void fill_array_rides (Catalog_Cities * catalog_cities, unsigned short int total_dist, char * city);
double get_average_distance (Catalog_Cities* catalog_cities, Catalog_Rides* catalog_rides,char * city, unsigned short int dateInf, unsigned short int dateSup);

int compare2(const void * a, const void * b);
void sort_array_avaliacoes_city (Catalog_Cities * catalog_cities, char * city_to_check);
uint get_id_driver_from_ordered_array (Catalog_Cities * catalog_cities, char * city_to_check, int index);
double get_aval_med_from_ordered_array (Catalog_Cities * catalog_cities, char * city_to_check, int index);

void sort_arrays_avaliacoes_cities (Catalog_Cities * catalog_cities);

