#include <stdio.h>

#include <glib.h>

#include "../includes/query3.h"

#include "../includes/rides.h"

#include "../includes/users.h"

struct users {
  char * username;
  char * name;
  char gender;
  unsigned short int date;
  int distance;
  char * birth_date;
  char * account_creation;
  char * pay_method;
  bool account_status;
  double total_gasto;
  short int numero_viagens_user;
  short int avaliacao_total_user;
  double avaliacao_media_user;
};


struct query3
 {
  char * id;
  int distance;
  char* name;
  unsigned short int data;
};


int compare_users(const void * a,
  const void * b) {
  Query3 * ia = (struct query3 * ) a;
  Query3 * ib = (struct query3 * ) b;

  if (ia -> distance < ib -> distance) return 1;

  if (ia -> distance > ib -> distance) return -1;

  if (ia -> distance == ib -> distance) {
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

void query3(GHashTable * hash_users, char * info, int n) {
  struct users * u;
  int numb = atoi(info);
  uint size = g_hash_table_size(hash_users);

  Query3 * query3 = malloc(size * sizeof(struct query3));
  gpointer * keys = g_hash_table_get_keys_as_array(hash_users, & size);
  for (uint i = 0; i < size; i++) {

    u = g_hash_table_lookup(hash_users, keys[i]);

    (query3 + i) -> id = (u -> username);
    (query3 + i) -> distance = u -> distance;
    (query3 + i) -> data = u -> date;
    (query3 + i) -> name = u -> name;

  }
  qsort((void * ) query3, size, sizeof(struct query3), compare_users);

  char buffer[256];
  snprintf(buffer, 256, "Resultados/command%d_output.txt", n);
  FILE * output = fopen(buffer, "w");
  if (output == NULL) {
    printf("Error opening output.\n");
  }
  for (int i = 0; i < numb; i++) {
    u = g_hash_table_lookup(hash_users, (query3 + i) -> id);
    if (!u -> account_status) {
      fprintf(output, "%s;"
        "%s;"
        "%d\n", (query3 + i) -> id, (query3 + i) -> name, (query3 + i) -> distance);

    } else {
      numb++;
    }
  }
  free(query3);
  //          free (u);
  fclose(output);
  printf("Query3 done.\n");
}