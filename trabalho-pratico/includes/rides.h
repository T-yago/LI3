#ifndef RIDES_H
#define RIDES_H

#include <stdbool.h>
#include <glib.h>
#include "../includes/drivers.h"
#include "../includes/users.h"


typedef struct rides Rides;

void rides_catalog(Catalog_Users * catalog_users, Catalog_Drivers * catalog_drivers, char * pathfiles);

#endif