#include <stdio.h>
#include <glib.h>
#include "../includes/query3.h"


int compare_users (const void *a, const void *b) {
  struct query3 *ia = (struct query3 *) a;
    struct query3 *ib = (struct query3 *) b;

    if( ia->distance < ib->distance ) return 1;
    
    if( ia->distance > ib->distance ) return -1;

    if (ia ->distance == ib->distance) {
       if (ia->data < ib->data) return 1; //se id for igual retorna a data + recente
       if (ia->data > ib->data) return -1;
       else if (ia->data == ib->data) { // se for para trocar é este
        if (ia->id > ib->id) return 1;
        if (ia->id < ib->id) return -1;
       }
       return -1;  // se datas também forem iguais retorna 
    }
    else  {return 0;}
}


void query3 (GHashTable * hash_users, char * info, int n) {
  struct users * u;
  int numb = atoi (info);
  uint size = g_hash_table_size (hash_users);

    struct query3 * query3 = malloc (size * sizeof(struct query3)); 
  gpointer* keys = g_hash_table_get_keys_as_array (hash_users,&size);
  for (uint i=0; i < size ; i++) {
 
    u = g_hash_table_lookup(hash_users,keys[i]);
    
    (query3+i)->id = (u->username);
    (query3 + i)->distance = u->distance; 
    (query3 + i) -> data = u->date;
    (query3 + i)->name = u->name;
    
  }
qsort((void*)query3,size,sizeof(struct query3),compare_users);
  char buffer[256];
  snprintf(buffer, 256, "Resultados/command%d_output", n);
  FILE * output = fopen(buffer, "w");
 for (int i=0; i<numb;i++) {
            u = g_hash_table_lookup(hash_users,(query3 +i)->id);
            if (!u->account_status) {
          fprintf (output,"%s;" "%s;" "%d\n",(query3 + i)->id, (query3 + i)->name,(query3 +i)->distance); 

            }
            else  {numb++;}
          }
          free (query3);
//          free (u);
          fclose (output);
 }