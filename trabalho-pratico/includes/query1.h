#ifndef QUERY1_H
#define QUERY1_H

#include  "../includes/users.h"
#include "../includes/drivers.h"


double calcula_total_gasto (char car_class, unsigned short int distance, double tip);
void query1_main(char * id, Catalog_Users * catalog_users, Catalog_Drivers * hash_drivers, int n);

#endif