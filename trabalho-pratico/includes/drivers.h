#ifndef DRIVERS_H
#define DRIVERS_H

#include <glib.h>

typedef struct drivers Drivers;
typedef struct catalog_drivers Catalog_Drivers;

Catalog_Drivers * drivers_catalog(char * pathfiles);
void initHash_drivers(Catalog_Drivers * hash_drivers);
void totalAuferidoDriver(Catalog_Drivers * drivers_hash, char * key, double ta);
void avaliacaoTotalDriver(Catalog_Drivers * drivers_hash, char * key, short int r);
void numeroViagensDriver(Catalog_Drivers * drivers_hash, char * key);
void dateDriver(Catalog_Drivers * drivers_hash, char * key, unsigned short int r);
char * getIdDriver(Catalog_Drivers * drivers_hash, char * key);
bool   getAccountStatus(Catalog_Drivers * drivers_hash, char * key);
double getAvaliacaoMediaDriver(Catalog_Drivers * drivers_hash, char * key);
double getDateDriver(Catalog_Drivers * drivers_hash, char * key);
char * getNameaDriver(Catalog_Drivers * drivers_hash, char * key);
char   getGenderDriver(Catalog_Drivers * drivers_hash, char * key);
char* getBirthDayDriver(Catalog_Drivers * drivers_hash, char * key);
double getTotalAuferidoDriver(Catalog_Drivers * drivers_hash, char * key);
char * getCarClassDriver(Catalog_Drivers * drivers_hash, char * key);
int getAvaliacaoTotalDriver(Catalog_Drivers * drivers_hash, char * key);
int getNviagensDriver(Catalog_Drivers * drivers_hash, char * key);
void avaliacaoMediaDriver(Catalog_Drivers * drivers_hash, char * key, double r);
uint get_hash_drivers_size (Catalog_Drivers * hash_drivers);
gpointer * get_keys_as_array_drivers (Catalog_Drivers * hash_drivers, uint size);


#endif