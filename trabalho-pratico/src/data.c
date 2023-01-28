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
    
    unsigned int array_rides_length = get_array_rides_length (catalog_rides);
    uint array_drives_length = get_array_drivers_size (catalog_drivers);

    int ride_id;
    int driver;
    unsigned short int ride_distance = 0;
    double ride_tip = 0;
    char* ride_city;
    char car_class;
    double total_gasto = 0;
    double total_gasto_sem_tips = 0;
    float ride_score_driver;

    for (unsigned int i = 0; i < array_rides_length; i++) {
        ride_id = get_ride_id (catalog_rides,i);
        if (ride_id != -1) {
        driver = get_ride_driver (catalog_rides,i);
        ride_distance = get_ride_distance (catalog_rides,i);
        ride_tip = get_ride_tip (catalog_rides,i);
        ride_city = get_ride_city (catalog_rides,i);
        car_class = get_driver_carclass(catalog_drivers, driver-1);
        total_gasto = calcula_total_gasto (car_class,ride_distance,ride_tip);
        total_gasto_sem_tips = total_gasto - ride_tip;
        ride_score_driver = get_score_driver_ride (catalog_rides,i);     
        

        fill_cities_catalog (catalog_cities, ride_city, total_gasto_sem_tips, array_drives_length, driver, ride_score_driver, i);

        
        free (ride_city);
        }
    }

    update_aval_medias_users (catalog_users);
    fill_drivers_array (catalog_drivers, catalog_rides);
    
    fill_users_hash (catalog_users, catalog_rides, catalog_drivers);
    update_aval_medias_users (catalog_users);
    
    insert_arrays_genders (catalog_users,catalog_drivers,catalog_rides);
    insert_array_dist(catalog_rides);
   
    sort_array_genders (catalog_rides);
    sort_arrays_avaliacoes_cities (catalog_cities);
}