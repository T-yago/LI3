#ifndef RIDES_H
#define RIDES_H

#include <stdbool.h>
#include <glib.h>

typedef struct rides Rides;

void rides_catalog(GHashTable * users_hash, GHashTable * drivers_hash, char* pathfiles);

#endif