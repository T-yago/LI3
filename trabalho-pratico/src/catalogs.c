#include "../includes/catalogs.h"
#include "../includes/queries_handler.h"

/**
 * @brief Struct composta por cada um dos catálogos criados
 * 
 */
struct catalogs {
    /**
     * @brief Catálogo dos users
     * 
     */
    Catalog_Users* catalog_users;
    /**
     * @brief Catálogo dos drivers
     * 
     */
    Catalog_Drivers* catalog_drivers;
    /**
     * @brief Catálogo das viagens
     * 
     */
    Catalog_Rides* catalog_rides;
    /**
     * @brief Catálogo das cidades
     * 
     */
    Catalog_Cities* catalog_cities;
};

/**
 * @brief Cria todos os catálogos e returna a struct composta por cada um deles
 * 
 * @param pathfiles Caminho para os ".csv"
 * @return Struct composta por todos os catálogos
 */
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

/**
 * @brief Liberta a memória associada a cada um dos catálogos
 * 
 * @param catalogs Struct composta por todos os catálogos
 */
void free_catalogs (Catalogs* catalogs) {

  free_users_catalog (catalogs->catalog_users);
  free_drivers_catalog (catalogs->catalog_drivers);
  free_rides_catalog (catalogs->catalog_rides);
  free_cities_catalog (catalogs->catalog_cities);
  free (catalogs);
}

/**
 * @brief Devolve o catálogo dos users
 * 
 * @param catalogs Struct composta por todos os catálogos 
 * @return Catálogo dos users 
 */
Catalog_Users* get_users_catalog (Catalogs* catalogs) {
    return catalogs->catalog_users;
}

/**
 * @brief Devolve o catálogo dos drivers
 * 
 * @param catalogs Struct composta por todos os catálogos
 * @return Catálogo dos drivers 
 */
Catalog_Drivers* get_drivers_catalog (Catalogs* catalogs) {
    return catalogs->catalog_drivers;
}

/**
 * @brief Devolve o catálogo das viagens
 * 
 * @param catalogs Struct composta por todos os catálogos
 * @return Catálogo das viagens
 */
Catalog_Rides* get_rides_catalog (Catalogs* catalogs) {
    return catalogs->catalog_rides;
}

/**
 * @brief Devolve o catálogo das cidades
 * 
 * @param catalogs Struct composta por todos os catálogos
 * @return Catálogo das cidades
 */
Catalog_Cities* get_cities_catalog (Catalogs* catalogs) {
    return catalogs->catalog_cities;
}