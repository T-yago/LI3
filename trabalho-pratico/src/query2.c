#include <stdio.h>
#include <glib.h>
#include "../includes/query2.h"


int compare (const void *a, const void *b) {
  struct query2 *ia = (struct query2 *) a;
  struct query2 *ib = (struct query2 *) b;

  if( ia->avaliacao_media < ib->avaliacao_media ) return 1;
  
  if( ia->avaliacao_media > ib->avaliacao_media ) return -1;

  if (ia ->avaliacao_media == ib->avaliacao_media) {
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

void query2 (GHashTable * hash_drivers, char* info, int n) {
  struct drivers * d ;
  int numb = atoi(info);
  uint size = g_hash_table_size (hash_drivers);
  struct query2 * query2 = malloc (sizeof(struct query2)); 
  gpointer* keys = g_hash_table_get_keys_as_array (hash_drivers, &size);
  for (uint i=0; i < size ; i++) {
 
    d = g_hash_table_lookup(hash_drivers,keys[i]);
    
    (query2+i)->id = (d->id);
    (query2 + i)->avaliacao_media = d->avaliacao_media_driver; 
    (query2 + i) -> data = d->date;
    (query2 + i)->name = d->name;
  }

  qsort((void*)query2,size,sizeof(struct query2),compare);

  char buffer[256];
  snprintf(buffer, 256, "Resultados/command%d_output", n);
  FILE * output = fopen(buffer, "w");
  for (int i=0; i< numb; i++) {
    d = g_hash_table_lookup(hash_drivers,(query2 +i)->id);
    if (!d->account_status) {
      fprintf (output,"%s;" "%s;" "%.3f\n",(query2 + i)->id, (query2 + i)->name,(query2 +i)->avaliacao_media); 
    }
    else  {numb++;}
  }
  free (d);
  fclose (output);
}
/*
 for (int i =0; i < size; i++) {
 printf ("AVAL:%f\n",query2[i].avaliacao_media);
 printf("ID:%s\n",q2[i].id);
 printf ("Data:%hu\n",q2[i].data);
*/


/*GCompareFunc * ()

void query2 (GHashTable * hash_drivers) {
struct drivers * d = malloc (sizeof(struct drivers));
gpointer* keys = g_hash_table_get_keys_as_array (hash_drivers,&size);
uint size = g_hash_table_size (hash_drivers);
GList aval_list = g_list_alloc ();

for (int i=0; i < size ; i++) {
  d = g_hash_table_lookup(hash_drivers,)
double *data = &(d->avaliacao_media_driver)  ;
   g_list_insert_sorted(aval_list,data,)
  
  }  

}
*/



/*
void query2 (GHashTable * hash_drivers) {
struct avaliacoes * avaliacao = malloc (sizeof(struct avaliacoes));
struct avaliacoes * nextnode;
struct avaliacoes * firstNode;
struct drivers * d = malloc (sizeof(struct drivers));
uint size = g_hash_table_size (hash_drivers);
gpointer* keys = g_hash_table_get_keys_as_array (hash_drivers,&size);
  for (int i=0; i < size ; i++) {
    if (i==0) {
    firstNode = malloc (size * sizeof(struct avaliacoes));    }
   else { 
    d = g_hash_table_lookup (hash_drivers,keys[i]);
    avaliacao->avaliacao_media = d->avaliacao_media_driver;
        avaliacao->id = keys[i];

    printf ("AVAL:%f\n", avaliacao->avaliacao_media); 
     printf ("id:%s\n", avaliacao->id);
    nextnode = malloc (size * sizeof(struct avaliacoes));
    avaliacao->next = nextnode;
    avaliacao = avaliacao->next;
    }
  }   

struct avaliacoes* last_node(struct Node* head)
{
    struct avaliacoes* temp = head;
    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }
    return temp;
}

//   printf ("%p",avaliacao);  




void query2 (GHashTable * hash_drivers) {
GTree * avaliacoes_tree = g_tree_new (g_str_equal);
uint size = g_hash_table_size (hash_drivers);
gpointer* keys = g_hash_table_get_keys_as_array (hash_drivers,&size);
struct drivers * d = malloc(sizeof(struct drivers));
//printf ("Avaliacao do 999;%f",d->avaliacao_media_driver);
//printf ("Size do array das keys:%d\n",size);
printf ("key:%s\n",keys[0]);
printf ("key999:%s\n", keys[9998]);
  for (int i=0; i < size; i++) {
//printf ("%s\n",keys[i]);
//if (!strcmp(keys[0],"000000003874")) {
  //printf ("Ola");
//}
    d = g_hash_table_lookup (hash_drivers,keys[i]);
 // printf("%f \n",d->avaliacao_media_driver);
   double * data = &(d->avaliacao_media_driver)  ;
  //printf ("%f",*data);
  //printf ("Keys:%s\n",keys[i]);
    g_tree_insert (avaliacoes_tree, d->id, data);
  }

d = g_hash_table_lookup (hash_drivers,"000000004780");
printf ("%p\n",d);
printf ("%f\n",d->avaliacao_media_driver);
//d = g_hash_table_lookup (hash_drivers,"000000007141");
//printf ("este%f\n",d->avaliacao_media_driver);


printf("Na ávrvore:%p\n",g_tree_lookup_node(avaliacoes_tree,"000000004780"));
double * valor = g_tree_lookup_node(avaliacoes_tree,"000000004780");
printf ("valor:%f\n",valor);
valor = g_tree_lookup(avaliacoes_tree,"000000007141");
printf ("valor:%f\n",valor);
printf("Na ávrvore:%f\n",g_tree_lookup(avaliacoes_tree,"000000004780"));
printf("Na ávrvore:%f\n",g_tree_lookup_node(avaliacoes_tree,"000000007141"));

printf ("N_nodes = %d",g_tree_nnodes);
printf ("Altura:%d\n",g_tree_height (avaliacoes_tree));
}
//        printf ("%p\n",d);
  //      printf ("%f\n",d->avaliacao_media_driver);


//printf ("%f\n",d->avaliacao_media_driver);

*/





//        printf ("%p\n",d);
  //      printf ("%f\n",d->avaliacao_media_driver);


//printf ("%f\n",d->avaliacao_media_driver);