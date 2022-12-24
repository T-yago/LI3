#ifndef RIDES_H
#define RIDES_H

#include <stdbool.h>
#include <glib.h>
#include "../includes/drivers.h"
#include "../includes/users.h"


typedef struct ride Ride;
typedef struct catalog_rides Catalog_Rides;

Catalog_Rides* rides_catalog(char * pathfiles);
unsigned short int get_ride_date (Catalog_Rides * catalog_rides, int index);
unsigned short int get_ride_distance (Catalog_Rides * catalog_rides,  int index);
char * get_ride_driver (Catalog_Rides * catalog_rides, int index);
char * get_ride_city (Catalog_Rides * catalog_rides, int index);
void free_rides_catalog (Catalog_Rides * catalog_rides);
uint get_array_rides_length (Catalog_Rides * catalog_rides);
unsigned int get_ride_id (Catalog_Rides* catalog_rides,  int index);
double get_ride_tip (Catalog_Rides* catalog_rides, int index);
char* get_ride_user (Catalog_Rides* catalog_rides, int index);
unsigned short int get_score_user_ride (Catalog_Rides* catalog_rides, int index);
unsigned short int get_score_driver_ride (Catalog_Rides* catalog_rides, int index);

#endif