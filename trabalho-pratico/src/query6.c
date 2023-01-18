#include <stdio.h>

#include <glib.h>

#include <string.h>

#include "../includes/query6.h"

// quer-se a distancia media por cidade logo recorrer ao array que tem as rides apenas daquela cidade
void query6 (char * city, char * dateA, char * dateB, Catalog_Cities* catalog_cities, Catalog_Rides * catalog_rides, int n) {
    char buffer[256];
    snprintf(buffer, 256, "Resultados/command%d_output.txt", n);
    FILE * output = fopen(buffer, "w");

    if (!is_in_hash_cities (catalog_cities,city)) fclose (output);
    
    else {
    char* city_query = strdup (city);
    double distancia_media = 0;
    unsigned short int dateinf = convert_to_day (dateA);
    unsigned short int datesup = convert_to_day (dateB);

    //
    distancia_media = get_average_distance (catalog_cities,catalog_rides, city_query,dateinf,datesup);
    
    if (distancia_media !=0) fprintf(output, "%.3f\n", distancia_media);
    fclose(output);
    free (city_query);
    }
}