#include <stdio.h>

#include <glib.h>

#include <string.h>

#include "../includes/query6.h"

#include "../includes/query4.h"

#include "../includes/rides.h"

#include "../includes/users.h"

#include "../includes/dates.h"


void query6 (char * city, char * dateA, char * dateB, Catalog_Rides * catalog_rides, int n) {
    unsigned short int date = 0; 
    double distancia_media = 0;
    uint num_rides = 0;
    unsigned short int dateinf = convert_to_day (dateA);
    unsigned short int datesup = convert_to_day (dateB);

    int hash_rides_size = get_hash_rides_size (catalog_rides);
    gpointer * keys = get_hash_keys_as_array_rides (catalog_rides,hash_rides_size);

    for (int i=0; i < hash_rides_size; i++) {
        char * driver = (get_ride_driver (catalog_rides,keys[i]));
        char * ride_city = (get_ride_city (catalog_rides,keys[i]));
        if (strcmp(driver,"driver")) {
            date = get_ride_date (catalog_rides,keys[i]);
            int distance = get_ride_distance(catalog_rides,keys[i]);
            if ((date > dateinf) && (date <= datesup) && (!strcmp(strdup(city),ride_city))){
                distancia_media += distance;
                num_rides++;
            }
        }
    }
    if (num_rides != 0)    distancia_media = distancia_media / num_rides;
    else    distancia_media = 0;
    free (keys);
    char buffer[256];
    snprintf(buffer, 256, "Resultados/command%d_output.txt", n);

    FILE * output = fopen(buffer, "w");
    fprintf(output, "%.3f\n", distancia_media);
    fclose(output);
}