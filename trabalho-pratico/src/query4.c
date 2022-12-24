    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #include <ctype.h>
    #include <glib.h>

    #include "../includes/query4.h"
    


void query4 (Catalog_Cities * catalog_cities, char * info , int n) {
    char buffer[256];
    snprintf(buffer, 256, "Resultados/command%d_output.txt", n);
    FILE * output = fopen(buffer, "w");

    char* city = strdup(info);
    double avaliacao_media = 0;
    double total_gasto = 0;
    unsigned int num_rides = 0;
    if (!is_in_hash_cities(catalog_cities,city)) fclose (output);
    else {
        total_gasto = get_total_gasto_city (catalog_cities,city);
        num_rides = get_num_rides_city (catalog_cities,city);
        avaliacao_media = total_gasto / num_rides;
        if (avaliacao_media != 0) fprintf(output, "%.3f\n",avaliacao_media);
        free (city);
        fclose (output);
    }
}


