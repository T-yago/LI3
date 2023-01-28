#ifndef RIDES_SERVICES_H
#define RIDES_SERVICES_H

#include "../includes/rides.h"
#include "../includes/drivers.h"
#include "../includes/users.h"

typedef struct dist_array Dist_Array;

void insert_array_dist (Catalog_Rides* catalog_rides);

int get_ride_id_dist(Catalog_Rides* catalog_rides, int index);
unsigned short int get_ride_dateint_dist(Catalog_Rides* catalog_rides, int index);
unsigned short int get_ride_dist_dist(Catalog_Rides* catalog_rides, int index);
double get_ride_tip_dist(Catalog_Rides* catalog_rides, int index);
int get_array_rides_index_dist (Catalog_Rides* catalog_rides, int index);
void insert_arrays_genders (Catalog_Users* catalog_users,Catalog_Drivers* catalog_drivers, Catalog_Rides* catalog_rides);


void sort_array_genders (Catalog_Rides* catalog_rides);

void free_array_top_dist (Catalog_Rides* catalog_rides);


#endif 
