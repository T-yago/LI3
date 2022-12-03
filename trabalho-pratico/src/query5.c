#include <stdio.h>
#include <glib.h>

void query5_main(char * dateA, char * dateB, GHashTable * hash_drivers, int n) {
    char buffer[256];
    snprintf(buffer, 256, "Resultados/command%d_output.txt", n);
    FILE * output = fopen(buffer, "w");
    if (output == NULL) {
        printf("Error opening output.\n");
    }







    
    fprintf(output, "%.3f\n", );
    fclose(output);
}