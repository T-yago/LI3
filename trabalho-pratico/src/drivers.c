#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <glib.h>

#include "../includes/drivers.h"

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
  double total_auferido_no_tips;
  int avaliacao_total_driver; // short int nao chegou 
  int numero_viagens_driver;
  double avaliacao_media_driver;
};

GHashTable * drivers_catalog(char * pathfiles) {
  char * line = NULL;
  size_t len;

  GHashTable * hash_drivers = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free); // FAZER DESTROY NO FIM 
  char driverfile[256];
  strcpy(driverfile, pathfiles);
  char * filename = strcat(driverfile, "/drivers.csv");
  FILE * file = fopen(filename, "r");
  int i = 0;
  do {
    while (getline( & line, & len, file) != -1) {
      Drivers * d = malloc(sizeof(struct drivers));
      char * token;
      int i = 0;
      while ((token = strsep( & line, ";\n"))) {
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
          d -> car_class = strdup(token);
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

    }
    i++;
  } while (!feof(file));
  fclose(file);
  //  g_hash_table_destroy(hash);
  GHashTable * v = hash_drivers;
  return v;
}

void initHash_drivers(GHashTable * hash_drivers) { ///// COLOCAR A initHash NUM SÍTIO + APROPRIADO
  uint size = g_hash_table_size(hash_drivers);
  Drivers * d;
  gpointer * keys = g_hash_table_get_keys_as_array(hash_drivers, & size);

  for (uint i = 0; i < size; i++) {
    d = g_hash_table_lookup(hash_drivers, keys[i]);
    d -> avaliacao_media_driver = 0;
    d -> avaliacao_total_driver = 0;
    d -> numero_viagens_driver = 0;
    d->date = 0;
  }
}


//***************************************************** Funções de encapsulamento de drivers *********************************************************
 
//***************************************************** Funções de encapsulamento de drivers *********************************************************
 
//***************************************************** Funções de encapsulamento de drivers *********************************************************



char * getIdDriver(GHashTable * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash, key);
  return strdup (d -> id);
}


bool getAccountStatus(GHashTable * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash, key);
  return d -> account_status;
}


double getAvaliacaoMediaDriver(GHashTable * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash, key);
  return d -> avaliacao_media_driver;
}


double getDateDriver(GHashTable * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash, key);
  return d -> date;
}


char * getNameaDriver(GHashTable * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash, key);
  return strdup(d -> name);
}


int getAvaliacaoTotalDriver(GHashTable * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash, key);
  return d->avaliacao_total_driver;
}


int getNviagensDriver(GHashTable * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash, key);
  return d -> numero_viagens_driver;
}


void avaliacaoMediaDriver(GHashTable * drivers_hash, char * key, double r){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash, key);
  d -> avaliacao_media_driver = r;
}


char  getGenderDriver(GHashTable * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash, key);
  return d -> gender;
}


char * getBirthDayDriver(GHashTable * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash, key);
  return strdup(d -> birth_day);
}


double getTotalAuferidoDriver(GHashTable * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash, key);
  return d -> total_auferido;
}


char * getCarClassDriver(GHashTable * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash, key);
  return strdup (d -> car_class);
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void totalAuferidoDriver(GHashTable * drivers_hash, char * key, double ta){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash, key);
  d -> total_auferido += ta;
}


void totalAuferidoDriverNoTips(GHashTable * drivers_hash, char * key, double ta0){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash, key);
  d -> total_auferido_no_tips += ta0;
}


void avaliacaoTotalDriver(GHashTable * drivers_hash, char * key, short int r){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash, key);
  d -> avaliacao_total_driver += r;
}


void numeroViagensDriver(GHashTable * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash, key);
  d -> numero_viagens_driver += 1;
}


void dateDriver(GHashTable * drivers_hash,char * key, unsigned short int r){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash, key);
  if (r > d -> date)  d -> date = r;
}