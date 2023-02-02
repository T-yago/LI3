#ifndef CATALOGS_H
#define CATALOGS_H

typedef struct catalogs Catalogs;

#include "../includes/data.h"
#include "../includes/users.h"
#include "../includes/drivers.h"
#include "../includes/rides.h"
#include "../includes/cities.h"

Catalogs* create_catalogs (char * pathfiles, char * input);
Catalog_Users* get_users_catalog (Catalogs* catalogs);
Catalog_Drivers* get_drivers_catalog (Catalogs* catalogs);
Catalog_Rides* get_rides_catalog (Catalogs* catalogs);
Catalog_Cities* get_cities_catalog (Catalogs* catalogs);



#endif