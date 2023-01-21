#include "../includes/rides_services.h"
#include <stdio.h>


struct dist_array
{
  int ride_id;
  unsigned short int ride_dateint;
  char *city;
  unsigned short int distance;
  double tip;
};

int compare_dist(const void *a, const void *b)
{

    Dist_Array *aa = *(Dist_Array**) a;
    Dist_Array *bb = *(Dist_Array**) b;

    // Sort by distance first
    if (aa->distance > bb->distance) return -1;

    else if (aa->distance < bb->distance) return 1;

    // If distances are equal, sort by dateint
    else if (aa->distance == bb->distance) {
        if (aa->ride_dateint > bb->ride_dateint) return -1;

        else if (aa->ride_dateint < bb->ride_dateint) return 1;

        // If distances and dateints are equal, sort by ride_id
        else if (aa->ride_dateint == bb->ride_dateint) {

            if (aa->ride_id > bb->ride_id) return -1;

            else if (aa->ride_id < bb->ride_id) return 1;
        }
    }
    // If everything is equal, return 0
    return 0;
}

void insert_array_dist (Catalog_Rides* catalog_rides) {
    int size_rides = get_array_rides_length (catalog_rides);
    Dist_Array ** array_dist = malloc (sizeof (Dist_Array*) * 10);
    int array_length = 0;

    for (int i = 0; i < size_rides; i++) {
        Dist_Array * aux = malloc(sizeof(Dist_Array)); 
        double tip = get_ride_tip(catalog_rides, i);
        if (tip == 0) i++;
        else {
            aux->ride_id = i + 1 ;
            aux->ride_dateint = get_ride_date(catalog_rides, i);
            aux->distance = get_ride_distance(catalog_rides, i);
            aux->city = get_ride_city(catalog_rides, i);
            aux->tip = tip;

            array_dist[i] = aux;
            array_length++;
        }
        if (array_length % 10 == 0) array_dist = realloc (array_dist, sizeof(Dist_Array*) * (array_length + 10));
    }
    
    qsort((void * ) array_dist, array_length, sizeof(Dist_Array*), compare_dist);
    set_top_dist(catalog_rides, array_dist, array_length);
}

int get_ride_id_dist(Catalog_Rides* catalog_rides, int index) {
    Dist_Array** top_dist = (Dist_Array**) get_top_dist(catalog_rides);
    Dist_Array* aux = top_dist[index];
    return aux->ride_id;
}

unsigned short int get_ride_dateint_dist(Catalog_Rides* catalog_rides, int index) {
    Dist_Array** top_dist = (Dist_Array**) get_top_dist(catalog_rides);
    Dist_Array* aux = top_dist[index];
    return aux->ride_dateint;
}

char* get_city_dist(Catalog_Rides* catalog_rides, int index) {
    Dist_Array** top_dist = (Dist_Array**) get_top_dist(catalog_rides);
    Dist_Array* aux = top_dist[index];
    return strdup(aux->city);
}

unsigned short int get_ride_dist_dist(Catalog_Rides* catalog_rides, int index) {
    Dist_Array** top_dist = (Dist_Array**) get_top_dist(catalog_rides);
    Dist_Array* aux = top_dist[index];
    return aux->distance;
}

double get_ride_tip_dist(Catalog_Rides* catalog_rides, int index) {
    Dist_Array** top_dist = (Dist_Array**) get_top_dist(catalog_rides);
    Dist_Array* aux = top_dist[index];
    return aux->tip;
}