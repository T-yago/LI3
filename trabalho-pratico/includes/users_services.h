#ifndef USERS_SERVICES_H
#define USERS_SERVICES_H

#include "../includes/users.h"

typedef struct user_distance_data User_Distance_Data;
void top_N_users (Catalog_Users * catalog_users);
char * get_top_N_users_id (Catalog_Users* catalog_users,int index);
char * get_top_N_users_name (Catalog_Users* catalog_users, int index);
unsigned short int get_top_N_users_distance (Catalog_Users * catalog_users, int index);

void free_users_services (Catalog_Users* top_N_users, unsigned int size);

#endif