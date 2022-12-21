#include <stdio.h>

#include <glib.h>

#include <string.h>

#include "../includes/query6.h"

#include "../includes/query4.h"

#include "../includes/rides.h"

#include "../includes/users.h"

#include "../includes/dates.h"


void query6 (char * city, char * dateA, char * dateB, Catalog_Rides * catalog_rides, int n) {
    char* city_query = strdup (city);
    unsigned short int date = 0; 
    double distancia_media = 0;
    uint num_rides = 0;
    unsigned short int dateinf = convert_to_day (dateA);
    unsigned short int datesup = convert_to_day (dateB);

    uint array_length = get_array_rides_length (catalog_rides);
    for (uint i=0; i < array_length; i++) {
        char * ride_city = get_ride_city (catalog_rides,i);
        date = get_ride_date (catalog_rides,i);
        int distance = get_ride_distance(catalog_rides,i);
        if ((!strcmp(city_query,ride_city) && (date >= dateinf) && (date <= datesup))){
            distancia_media += distance;
            num_rides++;
        }

        free (ride_city);
    }
    if (num_rides != 0)    distancia_media = distancia_media / num_rides;
    else    distancia_media = 0;
    char buffer[256];
    snprintf(buffer, 256, "Resultados/command%d_output.txt", n);

    FILE * output = fopen(buffer, "w");
    fprintf(output, "%.3f\n", distancia_media);
    fclose(output);
    free (city_query);
    
}