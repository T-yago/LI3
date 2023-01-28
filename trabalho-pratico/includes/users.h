#ifndef USERS_H
#define USERS_H

#include <glib.h>
#include <stdbool.h>
#include "../includes/drivers.h"

typedef struct user User;
typedef struct  catalog_users Catalog_Users;

void free_users_catalog (Catalog_Users * catalog_users);
Catalog_Users * users_catalog(char* pathfiles);
uint get_hash_size_users (Catalog_Users * catalog_users);


void initHash_users(Catalog_Users * catalog_users);
void update_aval_medias_users (Catalog_Users* catalog_users);
void fill_users_hash (Catalog_Users* catalog_users, Catalog_Rides* catalog_rides, Catalog_Drivers* catalog_drivers);
//------------------------------------ getters ---------------------------------------------------//

gpointer * get_hash_keys_as_array_users (Catalog_Users * catalog_users, uint size);
char * getUsernameUser(Catalog_Users * catalog_users, char * id);
int getDistanceUser(Catalog_Users * catalog_users, char * id);
unsigned short int getDateUser(Catalog_Users * catalog_users, char * id);
char * getNameUser(Catalog_Users * catalog_users, char * id);
bool getAccountStatusUser(Catalog_Users * catalog_users, char * id);
short int get_age_user(Catalog_Users * users_hash, char* id);
char  getGenderUser(Catalog_Users * catalog_users, char * id);
double  get_aval_media_user(Catalog_Users * catalog_users, char * id);
short int  getNviagensUser(Catalog_Users * catalog_users, char * id);
double getTotalGastoUser(Catalog_Users * catalog_users, char * id);
unsigned short int get_data_creation_days_user (Catalog_Users* catalog_users, char* key);


void set_top_N_users(Catalog_Users* catalog_users, void* top_N_users);
void* get_top_N_users(Catalog_Users* catalog_users);

#endif