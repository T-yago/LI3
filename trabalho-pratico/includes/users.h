#ifndef USERS_H
#define USERS_H

#include <glib.h>
#include <stdbool.h>

typedef struct users Users;
typedef struct  catalog_users Catalog_Users;

void free_users_catalog (Catalog_Users * catalog_users);
Catalog_Users * users_catalog(char* pathfiles);
uint get_hash_size_users (Catalog_Users * catalog_users);
gpointer * get_hash_keys_as_array_users (Catalog_Users * catalog_users, uint size);
void initHash_users(Catalog_Users * catalog_users);
void incUserNumeroViagens(Catalog_Users * catalog_users, char * id);
void avaliacaoTotalUser(Catalog_Users * catalog_users, char * id, short int r);
void totalDistanceUser(Catalog_Users * catalog_users, char * id, int r);
void dateUser(Catalog_Users * catalog_users, char * id, unsigned short int r);
void totalGastoUser(Catalog_Users * catalog_users, char * id, double tg);
char * getUsernameUser(Catalog_Users * catalog_users, char * id);
int getDistanceUser(Catalog_Users * catalog_users, char * id);
unsigned short int getDateUser(Catalog_Users * catalog_users, char * id);
char * getNameUser(Catalog_Users * catalog_users, char * id);
bool getAccountStatusUser(Catalog_Users * catalog_users, char * id);
short int get_age_user(Catalog_Users * users_hash, char* id);
char  getGenderUser(Catalog_Users * catalog_users, char * id);
short int  getAvaliacaoTotalUser(Catalog_Users * catalog_users, char * id);
short int  getNviagensUser(Catalog_Users * catalog_users, char * id);
double getAvaliacaoMediaUser(Catalog_Users * catalog_users, char * id);
double getTotalGastoUser(Catalog_Users * catalog_users, char * id);
void avaliacaoMediaUser(Catalog_Users * catalog_users, char * id, double r);


typedef struct user_distance_data User_Distance_Data;
void top_N_users (Catalog_Users * catalog_users);
char * get_top_N_users_id (Catalog_Users* catalog_users,int index);
char * get_top_N_users_name (Catalog_Users* catalog_users, int index);
unsigned short int get_top_N_users_distance (Catalog_Users * catalog_users, int index);




#endif