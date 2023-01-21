#include "../includes/rides_services.h"
#include <stdio.h>


// Guardar data ambos em string e int já que é consultada mais que uma vez
struct dist_array
{
  int ride_id;
  unsigned short int ride_dateint;
  unsigned short int distance;
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
    Dist_Array ** array_dist = malloc (sizeof (Dist_Array*) * 100);
    int array_length = 0;

    for (int i = 0; i < size_rides; i++) {
        Dist_Array * aux = malloc(sizeof(Dist_Array)); 
        double tip = get_ride_tip(catalog_rides, i);
        if (tip == 0); // se o tip for 0 não faz nada (avança no loop apenas)
        else {
            aux->ride_id = i  ;
            aux->ride_dateint = get_ride_date(catalog_rides, i);
            aux->distance = get_ride_distance(catalog_rides, i);

            array_dist[i] = aux;
            array_length++;
        }
        if (array_length % 100 == 0) array_dist = realloc (array_dist, sizeof(Dist_Array*) * (array_length + 100));
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


unsigned short int get_ride_dist_dist(Catalog_Rides* catalog_rides, int index) {
    Dist_Array** top_dist = (Dist_Array**) get_top_dist(catalog_rides);
    Dist_Array* aux = top_dist[index];
    return aux->distance;
}

void free_array_top_dist (Catalog_Rides* catalog_rides) {
    Dist_Array** top_dist = (Dist_Array**) get_top_dist(catalog_rides);
    int size = get_top_dist_length (catalog_rides);
        Dist_Array* aux = NULL;
        for (int i = 0; i < size; i++) {
            aux = top_dist[i]; 
            free (aux);
        }
}