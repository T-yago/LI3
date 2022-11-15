void query2 (GHashTable * hash_drivers) {

}





/*void query2 (GHashTable * hash_drivers) {
GTree * avaliacoes_tree = g_tree_new (g_str_equal);
uint size = g_hash_table_size (hash_drivers);
gpointer* keys = g_hash_table_get_keys_as_array (hash_drivers,&size);
struct drivers * d = malloc(sizeof(struct drivers));
//printf ("Avaliacao do 999;%f",d->avaliacao_media_driver);
//printf ("Size do array das keys:%d\n",size);
printf ("key:%s\n",keys[10]);
printf ("key999:%s\n", keys[9998]);
  for (int i=0; i < size; i++) {
//printf ("%s\n",keys[i]);
    d = g_hash_table_lookup (hash_drivers,keys[i]);
 // printf("%f \n",d->avaliacao_media_driver);
   double *data = &(d->avaliacao_media_driver)  ;
   printf ("%f",data);
    g_tree_insert (avaliacoes_tree, keys[i], data);
  }

d = g_hash_table_lookup (hash_drivers,"000000004780");
printf ("%p\n",d);
printf ("%f\n",d->avaliacao_media_driver);
d = g_hash_table_lookup (hash_drivers,"000000007141");
printf ("este%f\n",d->avaliacao_media_driver);

d = g_tree_lookup (avaliacoes_tree,"000000004780");
printf ("%f\n",d->avaliacao_media_driver);
printf("Na ávrvore:%f\n",g_tree_lookup_node(avaliacoes_tree,"000000004780"));

printf("Na ávrvore:%f\n",g_tree_lookup(avaliacoes_tree,"000000004780"));
printf("Na ávrvore:%f\n",g_tree_lookup_node(avaliacoes_tree,"000000007141"));

printf ("N_nodes = %d",g_tree_nnodes);
printf ("Altura:%d\n",g_tree_height (avaliacoes_tree));



//        printf ("%p\n",d);
  //      printf ("%f\n",d->avaliacao_media_driver);


//printf ("%f\n",d->avaliacao_media_driver);
}


*/





//        printf ("%p\n",d);
  //      printf ("%f\n",d->avaliacao_media_driver);


//printf ("%f\n",d->avaliacao_media_driver);

