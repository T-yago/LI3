#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <glib.h>
#include "../includes/parser.h"

#include "../includes/drivers.h"

struct catalog_drivers {
  GHashTable * hash_drivers;
  Driver_Aval_Date * top_N_drivers;
};

struct driver {
  char * id;
  char * name;
  char * birth_day;
  char gender;
  char * car_class;
  char * license_plate;
  unsigned short int date;
  char * city;
  char * account_creation;
  bool account_status;
  double total_auferido;
  int avaliacao_total_driver; // short int nao chegou 
  int numero_viagens_driver;
  double avaliacao_media_driver;
};

  Driver* create_driver(char** tokens, void* catalog) {
    Driver* driver = malloc(sizeof(Driver));
    driver->id = strdup(tokens[0]);
    driver->name = strdup(tokens[1]);
    driver->birth_day = strdup(tokens[2]);
    driver->gender = *tokens[3];
    driver->car_class = strdup(tokens[4]);
    driver->license_plate = strdup(tokens[5]);
    driver->city = strdup(tokens[6]);
    driver->account_creation = strdup(tokens[7]);
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

//---------------------------------------------Estrutura auxiliar dos drivers (query2) ---------------------------------------------//

struct driver_aval_date {
  char * id;
  double avaliacao_media;
  char* name;
  unsigned short int data;
};

// Função de comparação que ordena o array com os top_N_users
int compare(const void * a,
  const void * b) {
   Driver_Aval_Date *ia = (Driver_Aval_Date *) a;
   Driver_Aval_Date *ib = (Driver_Aval_Date*) b;

  if (ia -> avaliacao_media < ib -> avaliacao_media) return 1;

  if (ia -> avaliacao_media > ib -> avaliacao_media) return -1;

  if (ia -> avaliacao_media == ib -> avaliacao_media) {
    if (ia -> data < ib -> data) return 1; 
    if (ia -> data > ib -> data) return -1;
    else if (ia -> data == ib -> data) { 
      if (strcmp (ia -> id , ib -> id) > 0) return 1;
      if (strcmp (ia -> id, ib -> id) < 0) return -1;
    }
    return -1; 
  } else {
    return 0;
  }
}

// Função que cria um array com os top "N" users e o coloca no catálogo dos drivers
void top_N_drivers (Catalog_Drivers * catalog_drivers) {
  uint size_hash = get_hash_drivers_size(catalog_drivers);
  Driver_Aval_Date * driver_aval_date = malloc (size_hash * (sizeof (Driver_Aval_Date)));
  
  double aval_total = 0;
  double num_rides = 0;
  gpointer * keys = get_hash_keys_as_array_drivers(catalog_drivers, size_hash);
  for (uint i = 0; i < size_hash; i++) {

    Driver * d = g_hash_table_lookup(catalog_drivers->hash_drivers,keys[i]);
    aval_total = d->avaliacao_total_driver;
    num_rides = getNviagensDriver (catalog_drivers,keys[i]);
    (driver_aval_date + i) -> id = getIdDriver(catalog_drivers, keys[i]);
    (driver_aval_date +i) -> avaliacao_media =  aval_total / num_rides;
    (driver_aval_date + i) -> data = getDateDriver(catalog_drivers, keys[i]);
    (driver_aval_date + i) -> name = getNameDriver(catalog_drivers, keys[i]);

  }
  free (keys);

  qsort((void * ) driver_aval_date, size_hash, sizeof(Driver_Aval_Date), compare);
  catalog_drivers->top_N_drivers = driver_aval_date;
  
}

//---------------- -------------------------------------------------------------- ---------------------------------------------//


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

char * get_name_driver_top_N (Catalog_Drivers * catalog_drivers,int n) {
  Driver_Aval_Date  aux = catalog_drivers->top_N_drivers[n];
return  strdup(aux.name);

}

char * get_id_driver_top_N (Catalog_Drivers * catalog_drivers, int n) {
  Driver_Aval_Date  aux = catalog_drivers->top_N_drivers[n];
  return  strdup(aux.id);
}

double get_aval_med_top_N (Catalog_Drivers * catalog_drivers, int n) {
   Driver_Aval_Date aux = catalog_drivers->top_N_drivers[n];
   return aux.avaliacao_media;
}


//***************************************************** Funções de encapsulamento de drivers *********************************************************
 
//***************************************************** Funções de encapsulamento de drivers *********************************************************
 
//***************************************************** Funções de encapsulamento de drivers *********************************************************



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


int getAvaliacaoTotalDriver(Catalog_Drivers * catalog_drivers, char * key){
  Driver * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return d->avaliacao_total_driver;
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


char* getBirthDayDriver(Catalog_Drivers * catalog_drivers, char * key){
  Driver * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return strdup (d -> birth_day);
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


void avaliacaoTotalDriver(Catalog_Drivers * catalog_drivers, char * key, short int r){
  Driver * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  d -> avaliacao_total_driver += r;
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

void free_drivers_catalog (Catalog_Drivers * catalog_drivers) {
 uint size = g_hash_table_size ( catalog_drivers->hash_drivers);
  Driver *d ;
  gpointer * keys = get_hash_keys_as_array_drivers (catalog_drivers, size);
  //gpointer * keys = g_hash_table_get_keys_as_array ( hash_drivers, &size);
  for (uint i = 0; i < size; i++) {
    d = g_hash_table_lookup(catalog_drivers->hash_drivers, keys[i]);
    free (d -> id);
    free (d-> name);
    free (d -> birth_day);
    free (d->car_class);
    free (d->license_plate);
    free (d->city);
    free (d->account_creation);
    free (d);
  }
    free (keys);
    g_hash_table_destroy (catalog_drivers->hash_drivers);
    Driver_Aval_Date aux;
    for (uint i = 0; i < size; i++) {
      aux = catalog_drivers->top_N_drivers[i];
    free (aux.id);
    free (aux.name);
    }
    free (catalog_drivers->top_N_drivers);
    free (catalog_drivers);
}