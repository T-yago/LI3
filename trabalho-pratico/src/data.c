#include "../includes/data.h"

void fill_data (Catalog_Users* catalog_users, Catalog_Drivers* catalog_drivers, Catalog_Rides* catalog_rides, Catalog_Cities* catalog_cities) {
    unsigned int array_rides_length = get_array_rides_length (catalog_rides);

    unsigned int id;
    char* user;
    char* driver;
    unsigned short int ride_distance = 0;
    double ride_tip = 0;
    char* ride_city;
    char * car_class;
    double total_gasto = 0;
    double total_gasto_sem_tips = 0;
    double total_auferido = 0;
    unsigned short int ride_score_driver;
    unsigned short int ride_score_user;
    unsigned short int ride_date;


    for (unsigned int i = 0; i < array_rides_length; i++) {
        
        id = get_ride_id (catalog_rides,i);
        user = get_ride_user (catalog_rides,i);
        driver = get_ride_driver (catalog_rides,i);
        ride_distance = get_ride_distance (catalog_rides,i);
        ride_tip = get_ride_tip (catalog_rides,i);
        ride_city = get_ride_city (catalog_rides,i);
        car_class = getCarClassDriver(catalog_drivers, driver);
        total_gasto = calcula_total_gasto (car_class,ride_distance,ride_tip);
        total_gasto_sem_tips = total_gasto - ride_tip;
        total_auferido = calcula_total_gasto(car_class, ride_distance, ride_tip);
        ride_score_driver = get_score_driver_ride (catalog_rides,i);     
        ride_score_user = get_score_user_ride (catalog_rides, i);
        ride_date = get_ride_date (catalog_rides,i);


        totalGastoUser(catalog_users,user,total_gasto);

        avaliacaoTotalUser(catalog_users, user, ride_score_user);

        incUserNumeroViagens(catalog_users,user);

        totalDistanceUser(catalog_users, user, ride_distance);

        dateUser(catalog_users, user, ride_date);
               
        totalAuferidoDriver(catalog_drivers, driver, total_auferido);

        avaliacaoTotalDriver(catalog_drivers, driver, ride_score_driver);

        numeroViagensDriver(catalog_drivers, driver);

        dateDriver(catalog_drivers, driver, ride_date);

        fill_cities_catalog (catalog_cities, ride_city, total_gasto_sem_tips, id);
        
        free (user);
        free (driver);
        free (car_class);
        free (ride_city);

    }
}