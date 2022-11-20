#ifndef DRIVERS_H
#define DRIVERS_H

#include <glib.h>

struct drivers;

GHashTable * drivers_catalog (char* pathfiles);
void initHash_drivers (GHashTable * hash_drivers);

#endif