#include "../includes/cities_services.h"


  struct catalog_cities {
      GHashTable * cities_hash;
  };

  struct avaliacao_media_driver{
      uint id_driver;
      unsigned short int score_driver;
      unsigned short int num_rides;
  };

  struct city {
      double total_gasto;
      unsigned int num_rides;
      unsigned int* array_rides_city; //array que contém os ids das rides feitas nessa cidade
      unsigned int array_rides_city_length;
      Avaliacao_media_driver * array_avaliacao;
      unsigned int array_avaliacao_length;
  };




  int compare2(const void * a, const void * b) {

    Avaliacao_media_driver *ia = (Avaliacao_media_driver *) a;
    Avaliacao_media_driver *ib = (Avaliacao_media_driver*) b;
    double score_medio_a = (double)(ia->score_driver) / (double)(ia->num_rides);
    double score_medio_b = (double)(ib->score_driver) / (double)(ib->num_rides);

    if (score_medio_a < score_medio_b) return 1;

    if (score_medio_a > score_medio_b) return -1;
  
    else {
      if (ia -> id_driver < ib -> id_driver) return 1; 
      if (ia -> id_driver > ib -> id_driver) return -1;
    }
    return 0;
  }


  void sort_array_avaliacoes (gpointer key, gpointer value, gpointer user_data) {
    City* city = (City*) value;
    int size = city->array_avaliacao_length;
    qsort((void * ) city->array_avaliacao, size, sizeof(Avaliacao_media_driver), compare2);
    (void) key;/*unused*/
    (void) user_data;/*unused*/
  }

  void sort_arrays_avaliacoes_cities (Catalog_Cities * catalog_cities){
    g_hash_table_foreach (catalog_cities->cities_hash, (GHFunc)sort_array_avaliacoes, NULL);  
  }

  /*
  void update_avaliacoes_medias_array_city (gpointer key, gpointer value, gpointer user_data) {
    City* city = (City*) value;
    int size = city->array_avaliacao_length;
    
  }

  void update_avaliacoes_medias_arrays_cities (Catalog_Cities* catalog_cities) {
      g_hash_table_foreach (catalog_cities->cities_hash, (GHFunc)update_avaliacoes_medias_array_city, NULL);  
  }
  */

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

