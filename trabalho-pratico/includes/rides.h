#ifndef RIDES_H
#define RIDES_H

#include <stdbool.h>
#include <glib.h>
#include "../includes/drivers.h"
#include "../includes/users.h"


typedef struct ride Ride;
typedef struct catalog_rides Catalog_Rides;
typedef struct ride_ages Ride_Ages;

Catalog_Rides* rides_catalog(char * pathfiles);
unsigned int get_ride_id (Catalog_Rides * catalog_rides, int index);
unsigned short int get_ride_date (Catalog_Rides * catalog_rides, int index);
unsigned short int get_ride_distance (Catalog_Rides * catalog_rides,  int index);
char * get_ride_driver (Catalog_Rides * catalog_rides, int index);
char * get_ride_city (Catalog_Rides * catalog_rides, int index);
void free_rides_catalog (Catalog_Rides * catalog_rides);
uint get_array_rides_length (Catalog_Rides * catalog_rides);
double get_ride_tip (Catalog_Rides* catalog_rides, int index);
char* get_ride_user (Catalog_Rides* catalog_rides, int index);
unsigned short int get_score_user_ride (Catalog_Rides* catalog_rides, int index);
unsigned short int get_score_driver_ride (Catalog_Rides* catalog_rides, int index);

void init_array_genders (Catalog_Rides* catalog_rides);
void insert_arrays_genders (Catalog_Users* catalog_users,Catalog_Drivers* catalog_drivers, Catalog_Rides* catalog_rides,  char *user, char* driver, unsigned int id);
void sort_array_genders (Catalog_Rides* catalog_rides);
unsigned int * check_gender_in_rides (Catalog_Rides* catalog_rides, char gender, unsigned short int age);

void set_top_dist(Catalog_Rides *catalog_rides, void* array_dist);
void* get_top_dist(Catalog_Rides* catalog_rides);

#endif