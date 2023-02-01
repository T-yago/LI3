#include "../includes/query5.h"
#include <time.h>


/**
 * @brief Preço médio das viagens (sem considerar gorjetas) num dado intervalo de tempo
 * @param dateA Data inferior a considerar
 * @param dateB Data superior a considerar
 * @param catalog_drivers Catálogo dos drivers
 * @param catalog_rides Catálogo dos rides
 * @param n Número do ficheiro de output a gerar
 */
void query5 (char * dateA, char * dateB, Catalog_Drivers * catalog_drivers, Catalog_Rides * catalog_rides, int n) {
   unsigned short int date = 0; 
   double total_gasto_sem_tips = 0;
   double preco_medio = 0;
   uint num_rides = 0;
   unsigned short int dateinf = convert_to_day (dateA);
   unsigned short int datesup = convert_to_day (dateB);
   int index;
    //para cada ride,
    uint length = get_array_rides_length (catalog_rides);
    int flag = 0;
    for (uint i=0; i < length ; i++) 
    {
    index = get_ride_index_sorted_date (catalog_rides,i);
    date = get_ride_date (catalog_rides,index);
        if (date >= dateinf && date <= datesup) {
        int driver =  (get_ride_driver (catalog_rides,index));
        char car_class =  (get_driver_carclass (catalog_drivers,driver - 1));
        unsigned short int distance = get_ride_distance(catalog_rides,index); // talvz trocar para long?
        total_gasto_sem_tips = calcula_total_gasto (car_class, distance, 0);
        preco_medio += total_gasto_sem_tips;
        num_rides++;
        //free (car_class);
        }
       else if (date > datesup ) {
//rintf ("%d\n",i);
break;        } 
    }
    if (num_rides != 0) preco_medio = preco_medio / num_rides;
    char buffer[256];
    snprintf(buffer, 256, "Resultados/command%d_output.txt", n);

    FILE * output = fopen(buffer, "w");
     if (preco_medio != 0) fprintf(output, "%.3f\n", preco_medio);
    fclose(output);

}