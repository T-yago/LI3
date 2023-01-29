    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #include <ctype.h>
    #include <glib.h>

    #include "../includes/query4.h"
    

/**
 * @brief Preço médio das viagens (sem considerar gorjetas) numa determinada cidade
 * 
 * @param catalog_cities Catálogo dos cities
 * @param info String com a cidade pedida
 * @param n Número do ficheiro de output a gerar
 */
void query4 (Catalog_Cities * catalog_cities, char * info , int n) {
    char buffer[256];
    snprintf(buffer, 256, "Resultados/command%d_output.txt", n);
    FILE * output = fopen(buffer, "w");

    char* city = strdup(info);
    double preco_medio = 0;
    double total_gasto = 0;
    unsigned int num_rides = 0;
    if (!is_in_hash_cities(catalog_cities,city)) fclose (output);
    else {
        total_gasto = get_total_gasto_city (catalog_cities,city);
        num_rides = get_num_rides_city (catalog_cities,city);
        preco_medio = total_gasto / num_rides;
        if (preco_medio != 0) fprintf(output, "%.3f\n",preco_medio);
        free (city);
        fclose (output);
    }
}


