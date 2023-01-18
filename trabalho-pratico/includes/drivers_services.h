#ifndef DRIVERS_SERVICES_H
#define DRIVERS_SERVICES_H

#include "../includes/drivers.h"

typedef struct driver_aval_date Driver_Aval_Date;
void top_N_drivers (Catalog_Drivers * catalog_drivers);
char * get_name_driver_top_N (Catalog_Drivers * catalog_drivers,int n);
char * get_id_driver_top_N (Catalog_Drivers * catalog_drivers, int n);
double get_aval_med_top_N (Catalog_Drivers * catalog_drivers, int n);

void free_drivers_services (Catalog_Drivers* catalog_drivers, unsigned int size);

#endif