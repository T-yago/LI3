#include "../includes/query3.h"
#include <stdio.h>
#include <glib.h>

/*
int compare (const void * a, const void * b)
{
  double l = ((struct query2 *)a)->data;
  double r = ((struct query2 *)b)->data;
if (l < r) return -1;
else return 0;
  //return ( l -r);
}
*/

void initHash_users (GHashTable * hash_users) {
      uint size = g_hash_table_size (hash_users); 
        struct users * u;
              gpointer* keys = g_hash_table_get_keys_as_array (hash_users,&size);
for (int i=0; i < size;i++) {
    u = g_hash_table_lookup(hash_users,keys[i]);
    u->date = 0;
    u->distance = 0;
  }
  free (u);
}


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

void query3 (GHashTable * hash_users, int n) {
  struct query3 * query3 = malloc (sizeof(struct query3)); 
  int i;
  struct users * u;
  uint size = g_hash_table_size (hash_users);
  gpointer* keys = g_hash_table_get_keys_as_array (hash_users,&size);
  for (i=0; i < size ; i++) {
 
    u = g_hash_table_lookup(hash_users,keys[i]);
    
    (query3+i)->id = (u->username);
    (query3 + i)->distance = u->distance; 
    (query3 + i) -> data = u->date;
    (query3 + i)->name = u->name;
    
  }
qsort((void*)query3,size,sizeof(struct query3),compare_users);
FILE * output3 = fopen("output3.txt", "w");
 for (int i=1; i<n+1;i++) {
            u = g_hash_table_lookup(hash_users,(query3 +i)->id);
            if (!u->account_status) {
          fprintf (output3,"%s;" "%s;" "%d\n",(query3 + i)->id, (query3 + i)->name,(query3 +i)->distance); 

            }
            else  {n++;}
          }
          free (query3);
//          free (u);
          fclose (output3);
 }
/*
 for (int i =0; i < size; i++) {
 printf ("AVAL:%f\n",query2[i].avaliacao_media);
 printf("ID:%s\n",q2[i].id);
 printf ("Data:%hu\n",q2[i].data);
*/


/*GCompareFunc * ()

void query2 (GHashTable * hash_users) {
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