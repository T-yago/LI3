#ifndef DRIVERS_H
#define DRIVERS_H

#include <glib.h>
#include <stdbool.h>

typedef struct driver Driver;
typedef struct catalog_drivers Catalog_Drivers;

Catalog_Drivers * drivers_catalog(char * pathfiles);
void initHash_drivers(Catalog_Drivers * catalog_drivers);
void update_avaliacao_media_driver(Catalog_Drivers * catalog_drivers);
void free_drivers_catalog (Catalog_Drivers * catalog_drivers);


void totalAuferidoDriver(Catalog_Drivers * catalog_drivers,  int index, double ta);
void inc_avaliacao_media_driver (Catalog_Drivers * catalog_drivers,  int index, short int r);
void numeroViagensDriver(Catalog_Drivers * catalog_drivers,  int index);
void dateDriver(Catalog_Drivers * catalog_drivers,  int index, unsigned short int r);
void avaliacaoMediaDriver(Catalog_Drivers * catalog_drivers,  int index, double r);


char * get_driver_id (Catalog_Drivers * catalog_drivers,  int index);
bool   get_driver_acc_Status(Catalog_Drivers * catalog_drivers,  int index);
double get_driver_avalMedia (Catalog_Drivers * catalog_drivers,  int index);
double get_driver_date (Catalog_Drivers * catalog_drivers,  int index);
char * get_driver_name (Catalog_Drivers * catalog_drivers,  int index);
char   get_driver_gender (Catalog_Drivers * catalog_drivers,  int index);
short int get_driver_age (Catalog_Drivers * catalog_drivers,  int index);
double get_driver_total_auferido (Catalog_Drivers * catalog_drivers,  int index);
char * get_driver_carclass (Catalog_Drivers * catalog_drivers,  int index);
uint get_array_drivers_size (Catalog_Drivers* catalog_drivers);
int get_driver_Nviagens (Catalog_Drivers * catalog_drivers,  int index);
unsigned short int get_data_creation_days_driver (Catalog_Drivers* catalog_drivers, int index);


void set_top_N_drivers(Catalog_Drivers* catalog_drivers, void* top_N_drivers);
void* get_top_N_drivers(Catalog_Drivers* catalog_drivers);

#endif