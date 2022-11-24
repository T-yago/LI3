#ifndef USERS_H
#define USERS_H

#include <glib.h>

typedef struct users Users;

GHashTable * users_catalog(char* pathfiles);
void initHash_users (GHashTable * hash_users);
void incUserNumeroViagens(GHashTable * users_hash, char * id);
void avaliacaoTotalUser(GHashTable * users_hash, char * id, short int r);
void totalDistanceUser(GHashTable * users_hash, char * id, int r);
void dateUser(GHashTable * users_hash, char * id, unsigned short int r);
void totalGastoUser(GHashTable * users_hash, char * id, double tg);
char * getUsernameUser(GHashTable * users_hash, char * id);
int getDistanceUser(GHashTable * users_hash, char * id);
unsigned short int getDateUser(GHashTable * users_hash, char * id);
char * getNameUser(GHashTable * users_hash, char * id);
bool getAccountStatusUser(GHashTable * users_hash, char * id);
char * getBirthDateUser(GHashTable * users_hash, char * id);
char  getGenderUser(GHashTable * users_hash, char * id);
short int  getAvaliacaoTotalUser(GHashTable * users_hash, char * id);
short int  getNviagensUser(GHashTable * users_hash, char * id);
double getAvaliacaoMediaUser(GHashTable * users_hash, char * id);
double getTotalGastoUser(GHashTable * users_hash, char * id);
void avaliacaoMediaUser(GHashTable * users_hash, char * id, double r);







#endif