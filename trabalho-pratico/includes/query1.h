#ifndef QUERY1_H
#define QUERY1_H

#include  "../includes/drivers.h"
#include  "../includes/users.h"

double calcula_total_gasto (char* car_class, unsigned short int distance, double tip);
void update_avaliacao_media_driver(Catalog_Drivers * catalog_drivers);
void query1_main(char * id, Catalog_Users * catalog_users, Catalog_Drivers * hash_drivers, int n);
short int calcula_idade(char * birthdate);

#endif