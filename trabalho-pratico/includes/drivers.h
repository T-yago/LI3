#ifndef DRIVERS_H
#define DRIVERS_H

#include <glib.h>

typedef struct drivers Drivers;

GHashTable * drivers_catalog (char* pathfiles);
void initHash_drivers (GHashTable * hash_drivers);
char * getCarClassDriver(GHashTable * drivers_hash, Drivers * copyDrivers);
void totalAuferidoDriver(GHashTable * drivers_hash, Drivers * copyDrivers, double ta);
void avaliacaoTotalDriver(GHashTable * drivers_hash, Drivers * copyDrivers, short int r);
void numeroViagensDriver(GHashTable * drivers_hash, Drivers * copyDrivers);
void dateDriver(GHashTable * drivers_hash, Drivers * copyDrivers, unsigned short int r);



#endif