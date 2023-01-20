#include <stdio.h>
#include "../includes/query9.h"

void query9(Catalog_Rides* catalog_rides, char* datea, char* dateb, int n) {

    char buffer[256];
    snprintf(buffer, 256, "Resultados/command%d_output.txt", n);
    FILE * output = fopen(buffer, "w");

    unsigned short int dateinf = convert_to_day (datea);
    unsigned short int datesup = convert_to_day (dateb);

    int array_size = get_top_dist_length(catalog_rides);
    int i = 0;
    while(i < array_size) {
        int ride_id = get_ride_id_dist(catalog_rides, i);
        unsigned short int dateaux = get_ride_dateint_dist(catalog_rides, i);
        unsigned short int distance = get_ride_dist_dist(catalog_rides, i);
        char* city = get_city_dist(catalog_rides, i);
        double tip = get_ride_tip_dist(catalog_rides, i);
        if (dateaux >= dateinf && dateaux <= datesup) {
            char* date = convert_to_date(dateaux);
             fprintf(output, "%012d;%s;%d;%s;%.3f\n", ride_id, date, distance, city, tip);
        }
        i++;
    }
}