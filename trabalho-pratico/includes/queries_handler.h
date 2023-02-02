#ifndef QUERIES_HANDLER_H
#define QUERIES_HANDLER_H

#include "../includes/users.h"

#include "../includes/drivers.h"

#include "../includes/rides.h"

#include "../includes/cities.h"

void queries_handler(char* pathfiles, Catalog_Users* catalog_users, Catalog_Drivers* catalog_drivers, Catalog_Rides* catalog_rides, Catalog_Cities* catalog_cities);

#endif