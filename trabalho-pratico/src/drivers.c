#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <glib.h>

#include "../includes/drivers.h"

struct catalog_drivers {
  GHashTable * hash_drivers;
  Query2 * top_N_drivers;
};

struct query2 {
  char * id;
  double avaliacao_media;
  char* name;
  unsigned short int data;
};

struct drivers {
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

Catalog_Drivers * drivers_catalog(char * pathfiles) {
  char * line = NULL;
  size_t len;
  GHashTable * hash_drivers = g_hash_table_new(g_str_hash, g_str_equal); 
  char driverfile[256];
  strcpy(driverfile, pathfiles);
  char * filename = strcat(driverfile, "/drivers.csv");
  FILE * file = fopen(filename, "r");
  int i = 0;
  getline (&line,&len,file);
  do {
    while (getline( & line, & len, file) != -1) {
      Drivers * d = malloc(sizeof(struct drivers));
      char * token;
      int i = 0;
      char * line_aux = line;
      while ((token = strsep( & line_aux, ";\n"))) {
        switch (i) {
        case 0:
          d -> id = strdup(token);
          break;
        case 1:
          d -> name = strdup(token);
          break;
        case 2:
          d -> birth_day = strdup(token);
          break;
        case 3:
          d -> gender = * (token);
          break;
        case 4:
          d -> car_class = strdup (token);
          break;
        case 5:
          d -> license_plate = strdup(token);
          break;
        case 6:
          d -> city = strdup(token);
          break;
        case 7:
          d -> account_creation = strdup(token);
          break;
        case 8:
          if (strcmp(token, "active")) {
            d -> account_status = true;
          } else {
            d -> account_status = false;
          }
        }
        i++;
      }
      g_hash_table_insert(hash_drivers, d -> id, d);
            free (line_aux);
    }
    free (line);
    i++;
  } while (!feof(file));
  fclose(file);
  
  Catalog_Drivers * catalog_drivers = malloc (sizeof (struct catalog_drivers));
  catalog_drivers -> hash_drivers = hash_drivers;

return catalog_drivers;
}


int compare(const void * a,
  const void * b) {
   Query2 *ia = (struct query2 *) a;
   Query2 *ib = (struct query2 *) b;

  if (ia -> avaliacao_media < ib -> avaliacao_media) return 1;

  if (ia -> avaliacao_media > ib -> avaliacao_media) return -1;

  if (ia -> avaliacao_media == ib -> avaliacao_media) {
    if (ia -> data < ib -> data) return 1; //se id for igual retorna a data + recente
    if (ia -> data > ib -> data) return -1;
    else if (ia -> data == ib -> data) { // se for para trocar é este
      if (ia -> id > ib -> id) return 1;
      if (ia -> id < ib -> id) return -1;
    }
    return -1; // se datas também forem iguais retorna 
  } else {
    return 0;
  }
}

void top_N_drivers (Catalog_Drivers * catalog_drivers) {
  uint size_hash = get_hash_drivers_size(catalog_drivers);
  Query2 * query2 = malloc (size_hash * (sizeof (Query2)));
  
  gpointer * keys = get_hash_keys_as_array_drivers(catalog_drivers, size_hash);
  for (uint i = 0; i < size_hash; i++) {
    if (strcmp (keys[i],"id")) {
      
    Drivers * d = g_hash_table_lookup(catalog_drivers->hash_drivers,keys[i]);
    double aval_total = d->avaliacao_total_driver;
    double num_rides = getNviagensDriver (catalog_drivers,keys[i]);
    (query2 + i) -> id = getIdDriver(catalog_drivers, keys[i]);
    (query2 +i) -> avaliacao_media =  aval_total / num_rides;
    (query2 + i) -> data = getDateDriver(catalog_drivers, keys[i]);
    (query2 + i) -> name = getNameDriver(catalog_drivers, keys[i]);
    }
  }
  free (keys);

  qsort((void * ) query2, size_hash, sizeof(struct query2), compare);
  catalog_drivers->top_N_drivers = query2;
  
}

void initHash_drivers(Catalog_Drivers * catalog_drivers) { ///// COLOCAR A initHash NUM SÍTIO + APROPRIADO
  uint size = g_hash_table_size(catalog_drivers->hash_drivers);
  Drivers * d;
gpointer * keys = g_hash_table_get_keys_as_array(catalog_drivers->hash_drivers, & size);
  for (uint i = 0; i < size; i++) {
    d = g_hash_table_lookup(catalog_drivers->hash_drivers, keys[i]);
    d -> avaliacao_media_driver = 0;
    d -> avaliacao_total_driver = 0;
    d -> numero_viagens_driver = 0;
    d->date = 0;
  }
  free (keys);
}

char * get_name_driver_top_N (Catalog_Drivers * catalog_drivers,int n) {
  Query2  aux = catalog_drivers->top_N_drivers[n];
return  strdup(aux.name);

}

char * get_id_driver_top_N (Catalog_Drivers * catalog_drivers, int n) {
  Query2  aux = catalog_drivers->top_N_drivers[n];
  return  strdup(aux.id);
}

double get_aval_med_top_N (Catalog_Drivers * catalog_drivers, int n) {
   Query2 aux = catalog_drivers->top_N_drivers[n];
   return aux.avaliacao_media;
}

void free_hash_drivers (Catalog_Drivers * catalog_drivers) {
 uint size = g_hash_table_size ( catalog_drivers->hash_drivers);
  Drivers *d ;
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
    Query2 aux;
    for (uint i = 0; i < size; i++) {
      aux = catalog_drivers->top_N_drivers[i];
    free (aux.id);
    free (aux.name);
    }
    free (catalog_drivers->top_N_drivers);
}

//***************************************************** Funções de encapsulamento de drivers *********************************************************
 
//***************************************************** Funções de encapsulamento de drivers *********************************************************
 
//***************************************************** Funções de encapsulamento de drivers *********************************************************



char * getIdDriver(Catalog_Drivers * catalog_drivers, char * key){
  Drivers * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return strdup (d -> id);
}


bool getAccountStatus(Catalog_Drivers * catalog_drivers, char * key){
  Drivers * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  if (d== NULL) return true;
  return d -> account_status;
}


double getAvaliacaoMediaDriver(Catalog_Drivers * catalog_drivers, char * key){
  Drivers * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return d -> avaliacao_media_driver;
}


double getDateDriver(Catalog_Drivers * catalog_drivers, char * key){
  Drivers * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return d -> date;
}


char * getNameDriver(Catalog_Drivers * catalog_drivers, char * key){
  Drivers * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return strdup(d -> name);
}


int getAvaliacaoTotalDriver(Catalog_Drivers * catalog_drivers, char * key){
  Drivers * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return d->avaliacao_total_driver;
}


int getNviagensDriver(Catalog_Drivers * catalog_drivers, char * key){
  Drivers * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return d -> numero_viagens_driver;
}


void avaliacaoMediaDriver(Catalog_Drivers * catalog_drivers, char * key, double r){
  Drivers * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  d -> avaliacao_media_driver = r;
}


char  getGenderDriver(Catalog_Drivers * catalog_drivers, char * key){
  Drivers * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return d -> gender;
}


char* getBirthDayDriver(Catalog_Drivers * catalog_drivers, char * key){
  Drivers * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return strdup (d -> birth_day);
}


double getTotalAuferidoDriver(Catalog_Drivers * catalog_drivers, char * key){
  Drivers * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  return d -> total_auferido;
}


char * getCarClassDriver(Catalog_Drivers * catalog_drivers, char * key){
  Drivers * d;
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


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void totalAuferidoDriver(Catalog_Drivers * catalog_drivers, char * key, double ta){
  Drivers * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  d -> total_auferido += ta;
}


void avaliacaoTotalDriver(Catalog_Drivers * catalog_drivers, char * key, short int r){
  Drivers * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  d -> avaliacao_total_driver += r;
}


void numeroViagensDriver(Catalog_Drivers * catalog_drivers, char * key){
  Drivers * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  d -> numero_viagens_driver += 1;
}


void dateDriver(Catalog_Drivers * catalog_drivers,char * key, unsigned short int r){
  Drivers * d;
  d = g_hash_table_lookup(catalog_drivers->hash_drivers, key);
  if (r > d -> date)  d -> date = r;
}


