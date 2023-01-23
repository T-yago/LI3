#include "../includes/query2.h"


void query2(Catalog_Drivers * catalog_drivers, char * info, int n) {
  int numb = atoi(info);

  char buffer[256];
  snprintf(buffer, 256, "Resultados/command%d_output.txt", n);


  FILE * output = fopen(buffer, "w");
  for (int i = 0; i < numb; i++) {
    int id = get_id_driver_top_N (catalog_drivers,i);
    char * name = get_name_driver_top_N (catalog_drivers,i);
    double avaliacao_media = get_aval_med_top_N (catalog_drivers,i);
      fprintf(output, "%012d;"
        "%s;"
        "%.3f\n", id, name, avaliacao_media);
    free (name);
  }

  fclose(output);
}

