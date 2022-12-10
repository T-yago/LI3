#include <stdio.h>

#include <glib.h>

#include "../includes/query5.h"

#include "../includes/rides.h"

#include "../includes/users.h"

#include "../includes/drivers.h"


void query5_main(char * dateA, char * dateB, Catalog_Drivers * catalog_drivers, int n) {
    char buffer[256];
    snprintf(buffer, 256, "Resultados/command%d_output.txt", n);
    double preco_medio = 

    FILE * output = fopen(buffer, "w");
    fprintf(output, "%.3f\n", preco_medio);
    fclose(output);
    free (preco_medio);
}