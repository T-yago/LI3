#ifndef DRIVERS_H
#define DRIVERS_H

#include <glib.h>

typedef struct drivers Drivers;

GHashTable * drivers_catalog (char* pathfiles);
void initHash_drivers (GHashTable * hash_drivers);
void totalAuferidoDriver(GHashTable * drivers_hash, Drivers * copyDrivers, double ta);
void avaliacaoTotalDriver(GHashTable * drivers_hash, Drivers * copyDrivers, short int r);
void numeroViagensDriver(GHashTable * drivers_hash, Drivers * copyDrivers);
void dateDriver(GHashTable * drivers_hash, Drivers * copyDrivers, unsigned short int r);
char * getIdDriver(GHashTable * drivers_hash, Drivers * copyDrivers);
bool   getAccountStatus(GHashTable * drivers_hash, Drivers * copyDrivers);
double getAvaliacaoMediaDriver(GHashTable * drivers_hash, Drivers * copyDrivers);
double getDateDriver(GHashTable * drivers_hash, Drivers * copyDrivers);
char * getNameaDriver(GHashTable * drivers_hash, Drivers * copyDrivers);
char   getGenderDriver(GHashTable * drivers_hash, Drivers * copyDrivers);
char * getBirthDayDriver(GHashTable * drivers_hash, Drivers * copyDrivers);
double getTotalAuferidoDriver(GHashTable * drivers_hash, Drivers * copyDrivers);
char * getCarClassDriver(GHashTable * drivers_hash, Drivers * copyDrivers);
int getAvaliacaoTotalDriver(GHashTable * drivers_hash, Drivers * copyDrivers);
int getNviagensDriver(GHashTable * drivers_hash, Drivers * copyDrivers);
void avaliacaoMediaDriver(GHashTable * drivers_hash, Drivers * copyDrivers, double r);


#endif