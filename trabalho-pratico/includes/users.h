#ifndef USERS_H
#define USERS_H

#include <glib.h>

typedef struct users Users;

GHashTable * users_catalog(char* pathfiles);
void initHash_users (GHashTable * hash_users);
void incUserNumeroViagens(GHashTable * users_hash, Users * copyU);
void avaliacaoTotalUser(GHashTable * users_hash, Users * copyUsers, short int r);
void totalDistanceUser(GHashTable * users_hash, Users * copyUsers, int r);
void dateUser(GHashTable * users_hash, Users * copyUsers, unsigned short int r);
void totalGastoUser(GHashTable * users_hash, Users * copyUsers, double tg);
char * getUsernameUser(GHashTable * users_hash, Users* copyUsers);
int getDistanceUser(GHashTable * users_hash, Users* copyUsers);
unsigned short int getDateUser(GHashTable * users_hash, Users* copyUsers);
char * getNameUser(GHashTable * users_hash, Users* copyUsers);
bool getAccountStatusUser(GHashTable * users_hash, Users* copyUsers);




#endif