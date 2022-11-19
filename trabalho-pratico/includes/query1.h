#ifndef QUERY1_H
#define QUERY1_H

#include "../includes/rides.h" 

double calcula_total_gasto (char* car_class, short int distance, double tip);
short int calcula_idade (char* birthdate);
void update_valor (GHashTable * hash_drivers);
void query1_driver (char*id, GHashTable * hash_drivers, int n);
void query1_user (char*id, GHashTable * hash_users, int n);
void query1_main (char*id, GHashTable * hash_users, GHashTable * hash_drivers, int n);


#endif