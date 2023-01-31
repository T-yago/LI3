#ifndef RIDES_H
#define RIDES_H

#include <stdbool.h>
#include <glib.h>


typedef struct ride Ride;
typedef struct catalog_rides Catalog_Rides;
typedef struct ride_ages Ride_Ages;

Catalog_Rides* rides_catalog(char * pathfiles);

int get_ride_id (Catalog_Rides* catalog_rides, int index);
unsigned short int get_ride_date (Catalog_Rides * catalog_rides, int index);
unsigned short int get_ride_distance (Catalog_Rides * catalog_rides,  int index);
int get_ride_driver (Catalog_Rides * catalog_rides, int index);
char * get_ride_city (Catalog_Rides * catalog_rides, int index);
void free_rides_catalog (Catalog_Rides * catalog_rides);
uint get_array_rides_length (Catalog_Rides * catalog_rides);
double get_ride_tip (Catalog_Rides* catalog_rides, int index);
char* get_ride_user (Catalog_Rides* catalog_rides, int index);
unsigned short int get_score_user_ride (Catalog_Rides* catalog_rides, int index);
unsigned short int get_score_driver_ride (Catalog_Rides* catalog_rides, int index);

void init_array_genders (Catalog_Rides* catalog_rides);
unsigned int * check_gender_in_rides (Catalog_Rides* catalog_rides, char gender, unsigned short int age);

void set_top_dist(Catalog_Rides *catalog_rides, void* array_dist, int size);
void* get_top_dist(Catalog_Rides* catalog_rides);


void set_arrays_genders(Catalog_Rides* catalog_rides, void* array_ages_M, uint array_ages_M_length, void* array_ages_F, uint array_ages_F_length);
void* get_array_genders_F (Catalog_Rides* catalog_rides);
void* get_array_genders_M (Catalog_Rides* catalog_rides);

uint get_array_genders_F_length (Catalog_Rides* catalog_rides);
uint get_array_genders_M_length (Catalog_Rides* catalog_rides);

void sort_rides_by_date(Catalog_Rides* catalog_rides);
int get_top_dist_length(Catalog_Rides *catalog_rides);

void* get_array_rides_ids (Catalog_Rides* catalog_rides);
void set_array_rides_dates (Catalog_Rides* catalog_rides, void* array_ids, int size);

#endif