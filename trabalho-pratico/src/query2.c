#include "../includes/query2.h"




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

void query2(Catalog_Drivers * hash_drivers, char * info, int n) {
  int numb = atoi(info);
  uint size = get_hash_drivers_size (hash_drivers); // o tamanho é calculado no drivers.c
  //uint size = g_hash_table_size(hash_drivers->hash_drivers);
  Query2 * query2 = malloc(size * sizeof(struct query2));
  gpointer * keys = get_hash_keys_as_array_drivers(hash_drivers, size);
  for (uint i = 0; i < size; i++) {


    (query2 + i) -> id = getIdDriver(hash_drivers, keys[i]);
    (query2 + i) -> avaliacao_media = getAvaliacaoMediaDriver(hash_drivers, keys[i]);
    (query2 + i) -> data = getDateDriver(hash_drivers, keys[i]);
    (query2 + i) -> name = getNameDriver(hash_drivers, keys[i]);

  }
  free (keys);

  qsort((void * ) query2, size, sizeof(struct query2), compare);

  char buffer[256];
  snprintf(buffer, 256, "Resultados/command%d_output.txt", n);

  FILE * output = fopen(buffer, "w");
  for (int i = 0; i < numb; i++) {
    char* key = getIdDriver(hash_drivers, (query2 + i) -> id);
    if (!getAccountStatus(hash_drivers, key)) { //(!d->account_status)
      fprintf(output, "%s;"
        "%s;"
        "%.3f\n", (query2 + i) -> id, (query2 + i) -> name, (query2 + i) -> avaliacao_media);
    } else {
      numb++;
    }
    free (key);
  }
  for (uint i=0;i<size; i++) {
    free((query2 + i) -> id);
    free ((query2 + i) -> name);
  }
  free (query2);
  fclose(output);
}

