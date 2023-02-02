#ifndef INTERACTMODE_H
#define INTERACTMODE_H

#include "../includes/users.h"
#include "../includes/drivers.h"
#include "../includes/rides.h"
#include "../includes/cities.h"

int interactmode();
void queries_menu(int x, int y, Catalog_Users *catalog_users, Catalog_Drivers* catalog_drivers, Catalog_Rides *catalog_rides, Catalog_Cities *catalog_cities);

#endif