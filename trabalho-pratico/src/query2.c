#include <stdio.h>
#include <glib.h>
#include <stdbool.h>

#include "../includes/query2.h"
#include "../includes/drivers.h"





struct query2 {
  char * id;
  double avaliacao_media;
  char* name;
  unsigned short int data;
};

int compare(const void * a,
  const void * b) {
   Query2 *ia = (struct query2 *) a;
   Query2 *ib = (struct query2 *) b;

  if (ia -> avaliacao_media < ib -> avaliacao_media) return 1;

  if (ia -> avaliacao_media > ib -> avaliacao_media) return -1;

  if (ia -> avaliacao_media == ib -> avaliacao_media) {
    if (ia -> data < ib -> data) return 1; //se id for igual retorna a data + recente
    if (ia -> data > ib -> data) return -1;
    else if (ia -> data == ib -> data) { // se for para trocar é este
      if (ia -> id > ib -> id) return 1;
      if (ia -> id < ib -> id) return -1;
    }
    return -1; // se datas também forem iguais retorna 
  } else {
    return 0;
  }
}

void query2(GHashTable * hash_drivers, char * info, int n) {
  Drivers * d;
  int numb = atoi(info);
  uint size = g_hash_table_size(hash_drivers);
  struct query2 * query2 = malloc(sizeof(struct query2));
  gpointer * keys = g_hash_table_get_keys_as_array(hash_drivers, & size);
  for (uint i = 0; i < size; i++) {

    d = g_hash_table_lookup(hash_drivers, keys[i]);

    //(query2 + i) -> id = (d -> id);
    (query2 + i) -> id = getIdDriver(hash_drivers, d);

    //(query2 + i) -> avaliacao_media = d -> avaliacao_media_driver;
    (query2 + i) -> avaliacao_media = getAvaliacaoMediaDriver(hash_drivers, d);
    
    //query2 + i) -> data = d -> date;
    (query2 + i) -> data = getDateDriver(hash_drivers, d);
    
    //(query2 + i) -> name = d -> name;
    (query2 + i) -> name = getNameaDriver(hash_drivers, d);

  }

  qsort((void * ) query2, size, sizeof(struct query2), compare);

  char buffer[256];
  snprintf(buffer, 256, "Resultados/command%d_output.txt", n);

  FILE * output = fopen(buffer, "w");
  for (int i = 0; i < numb; i++) {
    d = g_hash_table_lookup(hash_drivers, (query2 + i) -> id);
    if (!getAccountStatus(hash_drivers, d)) { //(!d->account_status)
      fprintf(output, "%s;"
        "%s;"
        "%.3f\n", (query2 + i) -> id, (query2 + i) -> name, (query2 + i) -> avaliacao_media);
    } else {
      numb++;
    }
  }
  free (query2);
  fclose(output);
}

