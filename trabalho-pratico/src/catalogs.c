#include "../includes/catalogs.h"


void create_catalogs (char * pathfiles, char * input) {

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


  queries_handler (input, catalog_users, catalog_drivers, catalog_rides, catalog_cities);

  
  free_users_catalog (catalog_users);
  free_drivers_catalog (catalog_drivers);
  free_rides_catalog (catalog_rides);
  free_cities_catalog (catalog_cities);
}