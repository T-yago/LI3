#include <stdio.h>
#include "../includes/query9.h"

void query9(Catalog_Rides* catalog_rides, char* datea, char* dateb, int n) {

    char buffer[256];
    snprintf(buffer, 256, "Resultados/command%d_output.txt", n);
    FILE * output = fopen(buffer, "w");

    unsigned short int dateinf = convert_to_day (datea);
    unsigned short int datesup = convert_to_day (dateb);

    unsigned short int date;
    int ride_id;
    unsigned short int distance;
    char* city;
    double tip;
    char* date_string = NULL;
    int array_rides_index;

    int array_size = get_top_dist_length(catalog_rides);
    int i = 0;
    while(i < array_size) {
        date = get_ride_dateint_dist (catalog_rides, i);
        if (date >= dateinf && date <= datesup) {

        ride_id = get_ride_id_dist(catalog_rides, i);
        array_rides_index = get_array_rides_index_dist (catalog_rides, i);
        distance = get_ride_dist_dist(catalog_rides, i);
        city = get_ride_city (catalog_rides, array_rides_index );
        tip = get_ride_tip(catalog_rides, array_rides_index);
        date_string = convert_to_date(date);
            
        fprintf(output, "%012d;%s;%d;%s;%.3f\n", ride_id + 1, date_string, distance, city, tip);
        free (city);
        free (date_string);
        }
        i++;
    }
}