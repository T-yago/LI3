#include "../includes/data.h"
#include <stdio.h>
#include <math.h>

void fill_data (Catalog_Users* catalog_users, Catalog_Drivers* catalog_drivers, Catalog_Rides* catalog_rides, Catalog_Cities* catalog_cities) {
    
    unsigned int array_rides_length = get_array_rides_length (catalog_rides);
    uint array_drives_length = get_array_drivers_size (catalog_drivers);

    int ride_id;
    char* user;
    int driver;
    unsigned short int ride_distance = 0;
    double ride_tip = 0;
    char* ride_city;
    char * car_class;
    double total_gasto = 0;
    double total_gasto_sem_tips = 0;
    double total_auferido = 0;
    float ride_score_driver;
    unsigned short int ride_score_user;
    unsigned short int ride_date;

    for (unsigned int i = 0; i < array_rides_length; i++) {
        ride_id = get_ride_id (catalog_rides,i);
        if (ride_id != -1) {
        user = get_ride_user (catalog_rides,i);
        driver = get_ride_driver (catalog_rides,i);
        ride_distance = get_ride_distance (catalog_rides,i);
        ride_tip = get_ride_tip (catalog_rides,i);
        ride_city = get_ride_city (catalog_rides,i);
        car_class = get_driver_carclass(catalog_drivers, driver-1);
        total_gasto = calcula_total_gasto (car_class,ride_distance,ride_tip);
        total_gasto_sem_tips = total_gasto - ride_tip;
        total_auferido = calcula_total_gasto(car_class, ride_distance, ride_tip);
        if (total_auferido == 16.48) {
           if (driver == 3079){
            printf ("Index: %d\n",i);
            printf ("%d\n",driver);
            printf ("tip: %f\n",ride_tip);
            printf ("car_class: %s\n",car_class);
            printf ("distance: %d\n\n",ride_distance);
           } 

        }
        ride_score_driver = get_score_driver_ride (catalog_rides,i);     
        ride_score_user = get_score_user_ride (catalog_rides, i);
        ride_date = get_ride_date (catalog_rides,i);
        
        totalGastoUser(catalog_users,user,total_gasto);

        avaliacaoTotalUser(catalog_users, user, ride_score_user);

        incUserNumeroViagens(catalog_users,user);

        totalDistanceUser(catalog_users, user, ride_distance);

        dateUser(catalog_users, user, ride_date);

        //if (driver -1 == 9242) printf ("Ride:%d\n",i);   
        totalAuferidoDriver(catalog_drivers, driver -1 , total_auferido);

        inc_avaliacao_media_driver (catalog_drivers, driver - 1, ride_score_driver);

        numeroViagensDriver(catalog_drivers, driver -1 );

        dateDriver(catalog_drivers, driver - 1, ride_date);

        fill_cities_catalog (catalog_cities, ride_city, total_gasto_sem_tips, array_drives_length, driver - 1, ride_score_driver, i);

        insert_arrays_genders (catalog_users,catalog_drivers,catalog_rides, user, driver - 1, i);
        
        free (user);
        free (car_class);
        free (ride_city);
        }
    }
   
    insert_array_dist(catalog_rides);
    update_avaliacao_media_driver(catalog_drivers);
    sort_array_genders (catalog_rides);
    sort_arrays_avaliacoes_cities (catalog_cities);
}