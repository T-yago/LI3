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

    //para cada ride,
    uint length = get_array_rides_length (catalog_rides);
    for (uint i=0; i < length ; i++) 
    {
    date = get_ride_date (catalog_rides,i);
        if (date >= dateinf && date <= datesup) 
        {
        int driver =  (get_ride_driver (catalog_rides,i));
        char * car_class =  (get_driver_carclass (catalog_drivers,driver - 1));
        unsigned short int distance = get_ride_distance(catalog_rides,i); // talvz trocar para long?
        total_gasto_sem_tips = calcula_total_gasto (car_class, distance, 0);
        preco_medio += total_gasto_sem_tips;
        num_rides++;
        free (car_class);
        }
    }
    if (num_rides != 0) preco_medio = preco_medio / num_rides;
    char buffer[256];
    snprintf(buffer, 256, "Resultados/command%d_output.txt", n);

    FILE * output = fopen(buffer, "w");
     if (preco_medio != 0) fprintf(output, "%.3f\n", preco_medio);
    fclose(output);
}