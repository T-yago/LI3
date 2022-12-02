#ifndef RIDES_H
#define RIDES_H

#include <stdbool.h>
#include <glib.h>
#include "../includes/drivers.h"
#include "../includes/users.h"


typedef struct rides Rides;

void rides_catalog(Catalog_Users * users_hash, Catalog_Drivers * drivers_hash, char * pathfiles);

#endif