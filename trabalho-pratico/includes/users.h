#ifndef USERS_H
#define USERS_H

#include <glib.h>

typedef struct users Users;

GHashTable * users_catalog(char* pathfiles);
void initHash_users (GHashTable * hash_users);

#endif