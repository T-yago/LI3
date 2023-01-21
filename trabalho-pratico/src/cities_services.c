#include "../includes/cities_services.h"


//DEFENIR DE FORMA A NAO QUEBRAR O ENCAPSULAMENTE
int compare2(const void * a, const void * b) {

   Avaliacao_media_driver *ia = (Avaliacao_media_driver *) a;
   Avaliacao_media_driver *ib = (Avaliacao_media_driver*) b;
   double score_medio_a = (double)(ia->score_driver) / (double)(ia->num_rides);
   double score_medio_b = (double)(ib->score_driver) / (double)(ib->num_rides);

   if (score_medio_a < score_medio_b) return 1;

   if (score_medio_a > score_medio_b) return -1;
 
   if (score_medio_a == score_medio_b) {
    if (ia -> id_driver < ib -> id_driver) return 1; 
    if (ia -> id_driver > ib -> id_driver) return -1;
    return -1; 
  } else {
    return 0;
  }
}



void sort_array_avaliacoes_city (Catalog_Cities * catalog_cities, char * city_to_check){
  City *city = g_hash_table_lookup (catalog_cities->cities_hash, city_to_check);
  uint size = city -> array_avaliacao_length;
  Avaliacao_media_driver * array_avaliacao = city -> array_avaliacao;
  
  qsort((void * ) array_avaliacao, size, sizeof(Avaliacao_media_driver), compare2);
}



uint get_id_driver_from_ordered_array (Catalog_Cities * catalog_cities, char * city_to_check, int index) {
  City *city = g_hash_table_lookup (catalog_cities->cities_hash, city_to_check);
  Avaliacao_media_driver * array = city -> array_avaliacao;  
  Avaliacao_media_driver aux = array[index];
  return aux.id_driver;
}


double get_aval_med_from_ordered_array (Catalog_Cities * catalog_cities, char * city_to_check, int index) {
  City *city = g_hash_table_lookup (catalog_cities->cities_hash, city_to_check);
  Avaliacao_media_driver * array = city -> array_avaliacao;   
  Avaliacao_media_driver aux = array[index];
  double score_total = (double) aux.score_driver;
  double total_rides = (double) aux.num_rides;
  double r = 0;
  if(total_rides != 0) r = score_total / total_rides;
return r;
}