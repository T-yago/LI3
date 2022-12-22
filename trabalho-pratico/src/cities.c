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
    char * key;
    double total_gasto;
    uint num_rides;
};


Catalog_Cities * cities_catalog () {
        GHashTable * cities_hash = g_hash_table_new (g_str_hash, g_str_equal);
        Catalog_Cities * catalog_cities = malloc  (sizeof (struct catalog_cities));
        catalog_cities->cities_hash  = cities_hash;
        return catalog_cities;
    }

// função que é chamada aquando da primeira leitura das rides e que insere a city na sua hashtable
void insert_cities_hash (Catalog_Cities * cities_catalog , char * city_to_check, double total_gasto_por_ride) {
            if (g_hash_table_lookup (cities_catalog->cities_hash,city_to_check) == NULL) {
                char* key = strdup (city_to_check);
                City* city = malloc (sizeof (City));
                city->total_gasto = 0;
                city->key = key;
                city->total_gasto += total_gasto_por_ride;
                city->num_rides =1;
                g_hash_table_insert (cities_catalog->cities_hash, key, city); 

            }
    else {
                City *city = g_hash_table_lookup (cities_catalog->cities_hash,city_to_check);
                city->num_rides++;
                city->total_gasto += total_gasto_por_ride;
    }     
}

void free_cities_catalog (Catalog_Cities * catalog_cities) {
    uint size = g_hash_table_size ( catalog_cities->cities_hash);
    City *city ;
    gpointer * keys = g_hash_table_get_keys_as_array (catalog_cities->cities_hash, &size);
    for (uint i = 0; i < size; i++) {
    city = g_hash_table_lookup(catalog_cities->cities_hash, keys[i]);
    free (city->key);
    free (city);
    }
    free (keys); 
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