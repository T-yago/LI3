#include <stdio.h>

#include <glib.h>

#include "../includes/query5.h"

#include "../includes/rides.h"

#include "../includes/users.h"

#include "../includes/query1.h" // por causa do calcula_tt_gasto

#include "../includes/dates.h"


void query5 (char * dateA, char * dateB, Catalog_Drivers * catalog_drivers, Catalog_Rides * catalog_rides, int n) {
   unsigned short int date = 0; 
   double total_gasto_sem_tips = 0;
   double preco_medio = 0;
   uint num_rides = 0;
   unsigned short int dateinf = convert_to_day (dateA);
   unsigned short int datesup = convert_to_day (dateB);
    
    int hash_rides_size = get_hash_rides_size (catalog_rides);
    gpointer * keys = get_hash_keys_as_array_rides (catalog_rides,hash_rides_size);
    for (int i=0; i < hash_rides_size; i++) 
    {
    date = get_ride_date (catalog_rides,keys[i]);
    char * driver =  (get_ride_driver (catalog_rides,keys[i]));
    char * car_class =  (getCarClassDriver(catalog_drivers,driver));
    unsigned short int distance = get_ride_distance(catalog_rides,keys[i]); // talvz trocar para long?
    total_gasto_sem_tips = calcula_total_gasto (car_class, distance, 0);
        if (date >= dateinf && date <= datesup) 
        {
            preco_medio += total_gasto_sem_tips;
            num_rides++;
        }
                free (car_class);

    
            free (driver);
    }
    if (num_rides != 0) preco_medio = preco_medio / num_rides;

    free (keys);
    char buffer[256];
    snprintf(buffer, 256, "Resultados/command%d_output.txt", n);

    FILE * output = fopen(buffer, "w");
     if (preco_medio != 0) fprintf(output, "%.3f\n", preco_medio);
    fclose(output);
}