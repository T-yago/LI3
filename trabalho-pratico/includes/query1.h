#ifndef QUERY1_H
#define QUERY1_H

#include  "../includes/drivers.h"
#include  "../includes/users.h"

double calcula_total_gasto (char* car_class, short int distance, double tip);
void update_valor(Catalog_Drivers * catalog_drivers);
void query1_driver (char*id, Catalog_Drivers * catalog_drivers, int n);
void query1_user(char * id, Catalog_Users * catalog_users, int n);
void query1_main(char * id, Catalog_Users * catalog_users, Catalog_Drivers * hash_drivers, int n);

#endif