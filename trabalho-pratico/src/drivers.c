#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <glib.h>
#include "../includes/parser.h"
#include "../includes/query1.h"
#include "../includes/dates.h"
#include "../includes/drivers_services.h"
#include "../includes/drivers.h"

struct catalog_drivers {
  GHashTable * hash_drivers;
  Driver_Aval_Date * top_N_drivers;
};

struct driver {
  char * id;
  char * name;
  short int age;
  char gender;
  char * car_class;
  char * license_plate;
  unsigned short int date;
  char * city;
  unsigned short int account_creation;
  bool account_status;
  double total_auferido;
  int avaliacao_total_driver;
  int numero_viagens_driver;
  double avaliacao_media_driver;
};

  Driver* create_driver(char** tokens, void* catalog) {
    Driver* driver = malloc(sizeof(Driver));
    driver->id = strdup(tokens[0]);
    driver->name = strdup(tokens[1]);
    driver->age = calcula_idade (tokens[2]);
    driver->gender = *tokens[3];
    driver->car_class = strdup(tokens[4]);
    driver->license_plate = strdup(tokens[5]);
    driver->city = strdup(tokens[6]);
    driver->account_creation = convert_to_day(tokens[7]);
    driver->account_status = (tokens[8][0] == 'a' || tokens[8][0] == 'A') == 1;
    Catalog_Drivers* catalog_drivers = (Catalog_Drivers*)catalog;
    g_hash_table_insert(catalog_drivers->hash_drivers, driver->id, driver);
    return driver;
  }



Catalog_Drivers * drivers_catalog(char * pathfiles) {
  Catalog_Drivers * catalog_drivers = malloc (sizeof (struct catalog_drivers));
  GHashTable * hash_drivers = g_hash_table_new(g_str_hash, g_str_equal); 
  catalog_drivers -> hash_drivers = hash_drivers;

  char driverfile[256];
  strcpy(driverfile, pathfiles);
  char * filename = strcat(driverfile, "/drivers.csv");

  // Call parse_csv with the create and insert functions
  parse_csv(filename, (create_fn)create_driver, catalog_drivers);
  return catalog_drivers;
}


//---------------------------------------Estrutura auxiliar dos drivers (query2) ---------------------------------------------//
void set_top_N_drivers(Catalog_Drivers* catalog_drivers, void* top_N_drivers) {
    catalog_drivers->top_N_drivers = (Driver_Aval_Date*) top_N_drivers;
}
void* get_top_N_drivers(Catalog_Drivers* catalog_drivers) {
    return (void*) catalog_drivers->top_N_drivers;
}


//----------------------------------------------------------------------------------------------------------------------

void initHash_drivers(Catalog_Drivers * catalog_drivers) { 
  uint size = g_hash_table_size(catalog_drivers->hash_drivers);
  Driver * d;
gpointer * keys = g_hash_table_get_keys_as_array(catalog_drivers->hash_drivers, & size);
  for (uint i = 0; i < size; i++) {
    d = g_hash_table_lookup(catalog_drivers->hash_drivers, keys[i]);
    d -> avaliacao_media_driver = 0;
    d -> avaliacao_total_driver = 0;
    d -> numero_viagens_driver = 0;
    d ->total_auferido = 0;
    d-> date = 0;
  }
  free (keys);
}

void update_avaliacao_media_driver (Catalog_Drivers * catalog_drivers) {
  uint size = get_hash_drivers_size(catalog_drivers);
  double r = 0;
 gpointer *  keys = get_hash_keys_as_array_drivers(catalog_drivers, size);
  for (uint i = 0; i < size; i++) {
    r = (float) getAvaliacaoMediaDriver(catalog_drivers, keys[i]) / (float) getNviagensDriver(catalog_drivers, keys[i]);
    avaliacaoMediaDriver(catalog_drivers, keys[i], r);
  }
  free (keys);
}



//***************************************************** Funções de encapsulamento de drivers *********************************************************
 
//***************************************************** Funções de encapsulamento de drivers *********************************************************
 
//***************************************************** Funções de encapsulamento de drivers *********************************************************

unsigned short int get_data_creation_days_driver (Catalog_Drivers* catalog_drivers, char* key) {
  Driver * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return d->account_creation;
}


char * getIdDriver(Catalog_Drivers * catalog_drivers, char * key){
  Driver * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return strdup (d -> id);
}


bool getAccountStatus(Catalog_Drivers * catalog_drivers, char * key){
  Driver * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  if (d== NULL) return false;
  return d -> account_status;
}


double getAvaliacaoMediaDriver(Catalog_Drivers * catalog_drivers, char * key){
  Driver * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return d -> avaliacao_media_driver;
}


double getDateDriver(Catalog_Drivers * catalog_drivers, char * key){
  Driver * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return d -> date;
}


char * getNameDriver(Catalog_Drivers * catalog_drivers, char * key){
  Driver * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return strdup(d -> name);
}

int getNviagensDriver(Catalog_Drivers * catalog_drivers, char * key){
  Driver * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return d -> numero_viagens_driver;
}


void avaliacaoMediaDriver(Catalog_Drivers * catalog_drivers, char * key, double r){
  Driver * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  d -> avaliacao_media_driver = r;
}


char  getGenderDriver(Catalog_Drivers * catalog_drivers, char * key){
  Driver * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return d -> gender;
}


short int get_age_driver (Catalog_Drivers * catalog_drivers, char * key){
  Driver * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return (d -> age);
}


double getTotalAuferidoDriver(Catalog_Drivers * catalog_drivers, char * key){
  Driver * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return d -> total_auferido;
}


char * getCarClassDriver(Catalog_Drivers * catalog_drivers, char * key){
  Driver * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return strdup (d -> car_class);
}

uint get_hash_drivers_size (Catalog_Drivers * catalog_drivers) {
  uint size = g_hash_table_size (catalog_drivers->hash_drivers);
  return size;
}

gpointer * get_hash_keys_as_array_drivers (Catalog_Drivers * catalog_drivers, uint size) {
  gpointer * aux = g_hash_table_get_keys_as_array (catalog_drivers->hash_drivers, &size);
  return aux;
}


//-----------------------Funções que interagem com o catálogo dos drivers---------------------------------------------------------------------------------------------------------------------------------


void totalAuferidoDriver(Catalog_Drivers * catalog_drivers, char * key, double ta){
  Driver * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  d -> total_auferido += ta;
}


void inc_avaliacao_media_driver(Catalog_Drivers * catalog_drivers, char * key, short int r){
  Driver * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  d -> avaliacao_media_driver += r;
}


void numeroViagensDriver(Catalog_Drivers * catalog_drivers, char * key){
  Driver * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  d -> numero_viagens_driver += 1;
}


void dateDriver(Catalog_Drivers * catalog_drivers,char * key, unsigned short int r){
  Driver * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  if (r > d -> date)  d -> date = r;
}

//--------------------------------------------Função free---------------------------------------------------------//

void free_driver_data(gpointer key, gpointer value, gpointer user_data) {
  Driver *d = (Driver *)value;
  free (d->id);
  free (d->name);
  //free (d->birth_day);
  free (d->car_class);
  free (d->license_plate);
  free (d->city);
  //free (d->account_creation);
  free (d);
  (void)key;/*unused*/
  (void)user_data;/*unused*/
}


void free_drivers_catalog (Catalog_Drivers * catalog_drivers) {
  uint size = g_hash_table_size ( catalog_drivers->hash_drivers);
  
  g_hash_table_foreach(catalog_drivers->hash_drivers, (GHFunc)free_driver_data, NULL);
  g_hash_table_destroy (catalog_drivers->hash_drivers);
  free_drivers_services (catalog_drivers, size);
  free (catalog_drivers->top_N_drivers);
  free (catalog_drivers);
}