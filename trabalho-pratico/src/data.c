#include "../includes/data.h"
#include <stdio.h>
#include <math.h>

/**
 * @brief Itera sobre cada ride e faz fetch de informações que são depois enviadas para os outros módulos de forma a preenchê-los
 * 
 * @param catalog_users Catálogo dos users
 * @param catalog_drivers Catálogo dos drivers
 * @param catalog_rides Catálogo das rides
 * @param catalog_cities Catálogo das cidades
 */
void fill_data (Catalog_Users* catalog_users, Catalog_Drivers* catalog_drivers, Catalog_Rides* catalog_rides, Catalog_Cities* catalog_cities) {

    fill_cities_catalog (catalog_cities, catalog_rides, catalog_drivers);
    
    fill_drivers_array (catalog_drivers, catalog_rides);
    update_avaliacao_media_driver (catalog_drivers);
    
    fill_users_hash (catalog_users, catalog_rides, catalog_drivers);
    update_aval_medias_users (catalog_users);
    
    insert_arrays_genders (catalog_users,catalog_drivers,catalog_rides);
    insert_array_dist(catalog_rides);
   
    sort_array_genders (catalog_rides);
    sort_arrays_avaliacoes_cities (catalog_cities);
}