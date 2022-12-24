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

struct city {
    double total_gasto;
    unsigned int num_rides;
    unsigned int* array_dates;
    unsigned int array_dates_length;
};

Catalog_Cities * cities_catalog () {
        GHashTable * cities_hash = g_hash_table_new (g_str_hash, g_str_equal);
        Catalog_Cities * catalog_cities = malloc  (sizeof (struct catalog_cities));
        catalog_cities->cities_hash  = cities_hash;

        return catalog_cities;
    }

// função que é chamada aquando da primeira leitura das rides e que insere a city na sua hashtable
void fill_cities_catalog (Catalog_Cities * cities_catalog , char * city_to_check, double total_gasto_por_ride, unsigned int ride_id) {
            if (g_hash_table_lookup (cities_catalog->cities_hash,city_to_check) == NULL) {
                char* key = strdup (city_to_check);
                City* city = malloc (sizeof (City));
                city->total_gasto = 0;
                city->total_gasto += total_gasto_por_ride;
                city->num_rides =1;
                
                city->array_dates_length = 0;
                city->array_dates = malloc (100 *sizeof(uint));
                city->array_dates[city->array_dates_length] = ride_id;
                city->array_dates_length ++;
                g_hash_table_insert (cities_catalog->cities_hash, key, city); 

            }
    else {
                City *city = g_hash_table_lookup (cities_catalog->cities_hash,city_to_check);
                city->num_rides++;
                city->total_gasto += total_gasto_por_ride;

                city->array_dates[city->array_dates_length] = ride_id;
                city->array_dates_length++;
                if (city->array_dates_length % 100 == 0) city->array_dates = realloc(city->array_dates, sizeof(uint) * (city->array_dates_length + 100)); 
    }     
}

void free_city_data(gpointer key, gpointer value, gpointer user_data) {
  City *city = (City *)value;
  free (city->array_dates);
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
      for (uint i = 0; i < aux->array_dates_length; i++) {
        
        unsigned int id = aux->array_dates[i];
        date = get_ride_date (catalog_rides,id-1);
        
        if (date >= dateInf && date <= dateSup) {
        
            distance = get_ride_distance (catalog_rides,id-1);
            distancia_media += distance;
            cont++;
        }
      }
    
    distancia_media = distancia_media / cont;   
    return distancia_media;
}

