#ifndef DRIVERS_H
#define DRIVERS_H

#include <glib.h>

typedef struct drivers Drivers;

GHashTable * drivers_catalog (char* pathfiles);
void initHash_drivers (GHashTable * hash_drivers);
void totalAuferidoDriver(GHashTable * drivers_hash, char * key, double ta);
void avaliacaoTotalDriver(GHashTable * drivers_hash, char * key, short int r);
void numeroViagensDriver(GHashTable * drivers_hash, char * key);
void dateDriver(GHashTable * drivers_hash, char * key, unsigned short int r);
char * getIdDriver(GHashTable * drivers_hash, char * key);
bool   getAccountStatus(GHashTable * drivers_hash, char * key);
double getAvaliacaoMediaDriver(GHashTable * drivers_hash, char * key);
double getDateDriver(GHashTable * drivers_hash, char * key);
char * getNameaDriver(GHashTable * drivers_hash, char * key);
char   getGenderDriver(GHashTable * drivers_hash, char * key);
char * getBirthDayDriver(GHashTable * drivers_hash, char * key);
double getTotalAuferidoDriver(GHashTable * drivers_hash, char * key);
char * getCarClassDriver(GHashTable * drivers_hash, char * key);
int getAvaliacaoTotalDriver(GHashTable * drivers_hash, char * key);
int getNviagensDriver(GHashTable * drivers_hash, char * key);
void avaliacaoMediaDriver(GHashTable * drivers_hash, char * key, double r);



#endif