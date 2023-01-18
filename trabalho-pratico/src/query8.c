#include <stdio.h>
#include "../includes/rides.h"
#include "../includes/dates.h"

void query8 (char gender, int age, Catalog_Rides* catalog_rides, Catalog_Users* catalog_users, Catalog_Drivers* catalog_drivers, int n) {
    
    char buffer[256];
    snprintf(buffer, 256, "Resultados/command%d_output.txt", n);
    FILE * output = fopen(buffer, "w");
    
    char* id_driver;
    char* id_user;
    char* name_driver;
    char* name_user;
    unsigned int id_ride = 0;
    unsigned short int age_in_days = convert_to_day ("09/10/2022") - (age * 365) - 3; // Calcular o dia a partir do qual a idade é maior à pedida
    unsigned int * array_ids =  check_gender_in_rides (catalog_rides, gender, age_in_days); //recebe o array de ids que correspondem às viagens válidas

    for (int i = 0; array_ids[i]!=0; i++) {

        id_ride = array_ids [i];
        id_driver = get_ride_driver (catalog_rides, id_ride);
        id_user = get_ride_user (catalog_rides, id_ride);
        name_driver = getNameDriver (catalog_drivers, id_driver);
        name_user = getNameUser (catalog_users, id_user);
        if (getAccountStatus (catalog_drivers,id_driver) && getAccountStatusUser(catalog_users,id_user))
        fprintf(output, "%s;" "%s;" "%s;" "%s\n", id_driver, name_driver, id_user, name_user);
        free (id_driver);
        free (id_user);
        free (name_driver);
        free(name_user);
    }
    free (array_ids);
}