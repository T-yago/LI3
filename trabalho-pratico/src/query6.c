#include <stdio.h>

#include <glib.h>

#include <string.h>

#include "../includes/query6.h"


/**
 * @brief Distância média percorrida, numa determinada cidade
 * 
 * @param city Cidade a considerar
 * @param dateA Data inferior a considerar
 * @param dateB Data superior a considerar
 * @param catalog_cities Catálogo das cities
 * @param catalog_rides Catálogo das rides
 * @param n Número do ficheiro de output a gerar
 */
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