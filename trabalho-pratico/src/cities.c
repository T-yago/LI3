#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <glib.h>
#include "../includes/cities.h"


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

Catalog_Cities * cities_catalog () {
        GHashTable * cities_hash = g_hash_table_new (g_str_hash, g_str_equal);
        Catalog_Cities * catalog_cities = malloc  (sizeof (struct catalog_cities));
        catalog_cities->cities_hash  = cities_hash;

        return catalog_cities;
    }

// função que é chamada aquando da primeira leitura das rides e que insere a city na sua hashtable
void fill_cities_catalog (Catalog_Cities * catalog_cities, char * city_to_check, double total_gasto_por_ride, uint size_drivers, uint driver_id, unsigned short int score_driver, unsigned int ride_id) {
    
    if (g_hash_table_lookup (catalog_cities->cities_hash,city_to_check) == NULL) {
        char* key = strdup (city_to_check);
        City* city = malloc (sizeof (City));
        city->total_gasto = 0;
        city->total_gasto += total_gasto_por_ride;
        city->num_rides = 1;
        
        city->array_avaliacao = malloc (size_drivers * sizeof(Avaliacao_media_driver));
        for(uint i = 0; i < size_drivers; i++){
          city->array_avaliacao[i].id_driver = 0;
          city->array_avaliacao[i].score_driver = 0;
          city->array_avaliacao[i].num_rides = 0;
        }
        city->array_avaliacao[driver_id].id_driver = driver_id + 1;
        city->array_avaliacao[driver_id].score_driver = score_driver;
        city->array_avaliacao[driver_id].num_rides = 1;
        city->array_avaliacao_length = size_drivers;

        city->array_rides_city_length = 0;
        city->array_rides_city = malloc (100 *sizeof(uint));
        city->array_rides_city[city->array_rides_city_length] = ride_id;
        city->array_rides_city_length ++;
        g_hash_table_insert (catalog_cities->cities_hash, key, city); 
    }
    else {
        City *city = g_hash_table_lookup (catalog_cities->cities_hash,city_to_check);
        city->num_rides++;
        city->total_gasto += total_gasto_por_ride;

        city->array_avaliacao[driver_id].id_driver = driver_id + 1; 
        city->array_avaliacao[driver_id].score_driver += score_driver;
        city->array_avaliacao[driver_id].num_rides ++;

        city->array_rides_city[city->array_rides_city_length] = ride_id;
        city->array_rides_city_length++;
        if (city->array_rides_city_length % 100 == 0) city->array_rides_city = realloc(city->array_rides_city, sizeof(uint) * (city->array_rides_city_length + 100)); 
    }    
}

void free_city_data(gpointer key, gpointer value, gpointer user_data) {
  City *city = (City *)value;
  free (city->array_rides_city);
  free (city->array_avaliacao);
  free (city);
  free (key);
  (void)(user_data); /* unused */   // flag que diz ao compilador para ignorar a não utiliação de uma variável.
}


void free_cities_catalog (Catalog_Cities * catalog_cities) {
    g_hash_table_foreach(catalog_cities->cities_hash, (GHFunc)free_city_data, NULL);
    g_hash_table_destroy (catalog_cities->cities_hash);
    free (catalog_cities);
}


uint get_num_rides_city (Catalog_Cities * catalog_cities, char * city) {
    City* aux = g_hash_table_lookup (catalog_cities->cities_hash,city);
     return aux->num_rides;
}

double get_total_gasto_city (Catalog_Cities* catalog_cities, char * city) {
    City* aux = g_hash_table_lookup (catalog_cities->cities_hash,city);
    return aux->total_gasto;
}

bool is_in_hash_cities (Catalog_Cities * catalog_cities, char* city) {
    City* aux = g_hash_table_lookup (catalog_cities->cities_hash,city);
    if (!aux) return false;
    else return true;
}


double get_average_distance (Catalog_Cities* catalog_cities, Catalog_Rides* catalog_rides,char * city, unsigned short int dateInf, unsigned short int dateSup) {
      unsigned int cont=0;
      unsigned short int distance = 0;
      double distancia_media = 0;
      City * aux = g_hash_table_lookup (catalog_cities->cities_hash, city);

      unsigned short int date = 0;
      for (uint i = 0; i < aux->array_rides_city_length; i++) {
        
        unsigned int id = aux->array_rides_city[i];
        date = get_ride_date (catalog_rides,id);
        
        if (date >= dateInf && date <= dateSup) {
        
            distance = get_ride_distance (catalog_rides,id);
            distancia_media += distance;
            cont++;
        }
      }
    if (cont != 0) distancia_media = distancia_media / cont;   
    return distancia_media;
}




//----------------------------------------------------------------------------------------------------------------------------------------------------------------

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
  Avaliacao_media_driver * array_ordenado = malloc (100 * sizeof (Avaliacao_media_driver));
  uint j=0;
  //por alguma razao os valores de num_rides sao sempre iguais
  for (uint i = 0; i < size; i++) {
    if((array_avaliacao + i) -> num_rides){
    (array_ordenado + j) -> id_driver = (array_avaliacao + i) -> id_driver;
    (array_ordenado + j) -> score_driver = (array_avaliacao + i) -> score_driver;
    (array_ordenado + j) -> num_rides = (array_avaliacao + i) -> num_rides;
    j++;
    }
    if (j % 100 == 0) array_ordenado = realloc(array_ordenado, sizeof(Avaliacao_media_driver) * (j + 100)); 
  }
  free(array_avaliacao);
  qsort((void * ) array_ordenado, j, sizeof(Avaliacao_media_driver), compare2);
  city->array_avaliacao = array_ordenado;
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

