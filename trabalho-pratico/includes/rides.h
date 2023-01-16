#ifndef RIDES_H
#define RIDES_H

#include <stdbool.h>
#include <glib.h>
#include "../includes/drivers.h"
#include "../includes/users.h"


typedef struct ride Ride;
typedef struct catalog_rides Catalog_Rides;
typedef struct ride_ages Ride_Ages;
typedef struct q9 Q9;

Catalog_Rides* rides_catalog(char * pathfiles);
unsigned short int get_ride_date (Catalog_Rides * catalog_rides, int index);
unsigned short int get_ride_distance (Catalog_Rides * catalog_rides,  int index);
char * get_ride_driver (Catalog_Rides * catalog_rides, int index);
char * get_ride_city (Catalog_Rides * catalog_rides, int index);
void free_rides_catalog (Catalog_Rides * catalog_rides);
uint get_array_rides_length (Catalog_Rides * catalog_rides);
unsigned int get_ride_id (Catalog_Rides* catalog_rides,  int index);
char* get_ride_datestr(Catalog_Rides *catalog_rides, int index);
double get_ride_tip (Catalog_Rides* catalog_rides, int index);
char* get_ride_user (Catalog_Rides* catalog_rides, int index);
unsigned short int get_score_user_ride (Catalog_Rides* catalog_rides, int index);
unsigned short int get_score_driver_ride (Catalog_Rides* catalog_rides, int index);

void init_array_genders (Catalog_Rides* catalog_rides);
void insert_arrays_genders (Catalog_Users* catalog_users,Catalog_Drivers* catalog_drivers, Catalog_Rides* catalog_rides,  char *user, char* driver, unsigned int id);
void sort_array_genders (Catalog_Rides* catalog_rides);
unsigned int * check_gender_in_rides (Catalog_Rides* catalog_rides, char gender, unsigned short int age);

void init_array_q9(Catalog_Rides* catalog_rides);
void insert_array_q9(Catalog_Rides* catalog_rides, int id, unsigned short int ride_distance, char* ride_city, double ride_tip, unsigned short int ride_dateint, int index);
void sort_arrayq9(Catalog_Rides* catalog_rides);

int get_arrayq9_size(Catalog_Rides* catalog_rides);
int get_ride_id_q9(Catalog_Rides* catalog_rides, int index);
char* get_ride_date_q9(Catalog_Rides* catalog_rides, int index);
char* get_ride_city_q9(Catalog_Rides* catalog_rides, int index);
unsigned short int get_ride_distance_q9(Catalog_Rides* catalog_rides, int index);
double get_ride_tip_q9(Catalog_Rides* catalog_rides, int index);
unsigned short int get_ridedateint_q9(Catalog_Rides *catalog_rides, int index);

#endif