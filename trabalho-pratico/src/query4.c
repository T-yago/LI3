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
                  //  printf ("Dentro da check_city: %p\n",cities_catalog->cities_hash);
        
        int size = 0;
            for (int i =0; cities_catalog->cities_list[i]; i++) { 
    size++;
            }
        for (int i =0; cities_catalog->cities_list[i]; i++) { 
        

            if (!strcmp (city, cities_catalog->cities_list[i])) {
                found = 1;
            }

        }
        if (found == 0) {
                cities_catalog->cities_list[size] = strdup (city);
            }
        //printf ("%s não estava na lista\n", city);
        if (cities_catalog->cities_list[0] == NULL) cities_catalog->cities_list[0] = strdup (city);
        //printf ("acabou o check_city\n\n");
        return found;
    }


    void insert_cities_hash (Catalog_Cities * cities_catalog , char * city, double total_gasto_por_ride) {
            char* aux = strdup (city);
            Cities * cities = malloc (sizeof (struct cities));
                if (check_city (cities_catalog,city) == 0) {
                    cities->total_gasto = 0;
                    cities->total_gasto += total_gasto_por_ride;
                    cities->num_rides =0;
                    cities->num_rides +=1;

                    g_hash_table_insert (cities_catalog->cities_hash, aux, cities); 
                 //   printf ("Num_rides: %d\n",cities->num_rides);
                }
        // Cities * cities = malloc (sizeof (struct cities));  
        else {
                    Cities * cities = g_hash_table_lookup (cities_catalog->cities_hash,aux);
                    cities->num_rides++;
                    cities->total_gasto += total_gasto_por_ride;
                //    printf ("Num_rides: %d",cities->num_rides);
          //  printf ("vai checkar na hash\n\n");
        }              //   printf ("Num_rides: %f\n",aux2->total_gasto);


    }

    void query4 (Catalog_Cities * catalog_cities, char * info , int n) {
          char* city = strdup(info);
        Cities * aux = g_hash_table_lookup (catalog_cities->cities_hash, city);
        double avaliacao_media = aux->total_gasto / aux->num_rides;
        printf ("%f\n",avaliacao_media);

        char buffer[256];
        snprintf(buffer, 256, "Resultados/command%d_output.txt", n);
        FILE * output = fopen(buffer, "w");
        fprintf(output, "%.3f",avaliacao_media);
    }