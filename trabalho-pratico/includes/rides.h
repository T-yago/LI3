#ifndef RIDES_H
#define RIDES_H

#include <stdbool.h>
#include <glib.h>
#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/query4.h"


typedef struct rides Rides;

void rides_catalog(Catalog_Users * catalog_users, Catalog_Drivers * catalog_drivers, Catalog_Cities * catalog_cities, char * pathfiles);

#endif