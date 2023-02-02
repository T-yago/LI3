#include "../includes/catalogs.h"
#include "../includes/queries_handler.h"


struct catalogs {
    Catalog_Users* catalog_users;
    Catalog_Drivers* catalog_drivers;
    Catalog_Rides* catalog_rides;
    Catalog_Cities* catalog_cities;
};

Catalogs* create_catalogs (char * pathfiles) {

  Catalogs* catalogs = malloc (sizeof (Catalogs));
  //criação dos catálogos
  Catalog_Users * catalog_users = users_catalog(pathfiles);
  initHash_users(catalog_users);
  
  Catalog_Drivers * catalog_drivers = drivers_catalog(pathfiles);
  init_array_drivers(catalog_drivers);
  
  Catalog_Rides * catalog_rides = rides_catalog(pathfiles);
  
  Catalog_Cities * catalog_cities = cities_catalog ();
  fill_data (catalog_users,catalog_drivers,catalog_rides,catalog_cities);
  
  //criação das estruturas auxiliares para as queries
  top_N_drivers (catalog_drivers);  
  top_N_users (catalog_users);

  catalogs -> catalog_users = catalog_users;
  catalogs -> catalog_drivers = catalog_drivers;
  catalogs -> catalog_rides = catalog_rides;
  catalogs -> catalog_cities = catalog_cities;

  

  return catalogs;
}

void free_catalogs (Catalogs* catalogs) {

  free_users_catalog (catalogs->catalog_users);
  free_drivers_catalog (catalogs->catalog_drivers);
  free_rides_catalog (catalogs->catalog_rides);
  free_cities_catalog (catalogs->catalog_cities);
  free (catalogs);
}

Catalog_Users* get_users_catalog (Catalogs* catalogs) {
    return catalogs->catalog_users;
}

Catalog_Drivers* get_drivers_catalog (Catalogs* catalogs) {
    return catalogs->catalog_drivers;
}

Catalog_Rides* get_rides_catalog (Catalogs* catalogs) {
    return catalogs->catalog_rides;
}

Catalog_Cities* get_cities_catalog (Catalogs* catalogs) {
    return catalogs->catalog_cities;
}