    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #include <ctype.h>
    #include <glib.h>


    #include "../includes/query4.h"

    struct catalog_cities {
        GHashTable * cities_hash;
        char **cities_list ;
    };

    struct cities {
    char * key;
    double total_gasto;
    int num_rides;
    };


    Catalog_Cities * init_hash_cities () {
        GHashTable * cities_hash = g_hash_table_new (g_str_hash, g_str_equal);
        Catalog_Cities * catalog_cities = malloc  (sizeof (struct catalog_cities));
        catalog_cities->cities_hash  = cities_hash;
        catalog_cities->cities_list = malloc (159 * sizeof (char*)); //TROCAR ISTO DEPOIS
        for (int i=0; i < 159;i++ ) {
            catalog_cities->cities_list[i] = NULL;
        }
        return catalog_cities;
    }


    int check_city (Catalog_Cities * cities_catalog, char * city) {
        int found = 0;        
        int size = 0;
           
            for (int i =0; cities_catalog->cities_list[i]; i++) { 
                size++;
            }
            for (int i =0; cities_catalog->cities_list[i]; i++) 
            { 
        
                if (!strcmp (city, cities_catalog->cities_list[i])) {
                found = 1;
                }

            }
        if (found == 0) 
        {
                cities_catalog->cities_list[size] = strdup (city);
        }
        if (cities_catalog->cities_list[0] == NULL) cities_catalog->cities_list[0] = strdup (city);
        return found;
    }


void insert_cities_hash (Catalog_Cities * cities_catalog , char * city, double total_gasto_por_ride) {
            if (check_city (cities_catalog,city) == 0) {
                char* key = strdup (city);
                Cities * cities = malloc (sizeof (struct cities));
                cities->total_gasto = 0;
                cities->key = key;
                cities->total_gasto += total_gasto_por_ride;
                cities->num_rides =0;
                cities->num_rides +=1;

                g_hash_table_insert (cities_catalog->cities_hash, key, cities); 

            }
    else {
                Cities * cities = g_hash_table_lookup (cities_catalog->cities_hash,city);
                cities->num_rides++;
                cities->total_gasto += total_gasto_por_ride;
    }     
}

void query4 (Catalog_Cities * catalog_cities, char * info , int n) {
    char buffer[256];
    snprintf(buffer, 256, "Resultados/command%d_output.txt", n);
    FILE * output = fopen(buffer, "w");

    char* city = strdup(info);
    Cities * aux = g_hash_table_lookup (catalog_cities->cities_hash, city);
    if (!aux) fclose(output);
    else 
    {
        double avaliacao_media = aux->total_gasto / aux->num_rides;
        fprintf(output, "%.3f\n",avaliacao_media);
        free (city);
        fclose (output);
    }
  
}

void free_hash_cities (Catalog_Cities * catalog_cities) {
    uint size = g_hash_table_size ( catalog_cities->cities_hash);
    Cities *city ;
    gpointer * keys = g_hash_table_get_keys_as_array (catalog_cities->cities_hash, &size);
    //gpointer * keys = g_hash_table_get_keys_as_array ( hash_drivers, &size);
    for (uint i = 0; i < size; i++) {
    city = g_hash_table_lookup(catalog_cities->cities_hash, keys[i]);
    free (city->key);
    free (city);
    }
    free (keys); 
    g_hash_table_destroy (catalog_cities->cities_hash);
    for (int i=0;i < 159;i++) free (catalog_cities->cities_list[i]);
    free (catalog_cities->cities_list);
    }
