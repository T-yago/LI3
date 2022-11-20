#ifndef RIDES_H
#define RIDES_H

#include <stdbool.h>
#include <glib.h>

struct users {
  char * username;
  char * name;
  char gender;
  unsigned short int date;
  int distance;
  char * birth_date;
  char * account_creation;
  char * pay_method;
  bool account_status;
  double total_gasto;
  short int numero_viagens_user;
  short int avaliacao_total_user;
  double avaliacao_media_user;
  short int age;
};

struct drivers {
  char * id;
  char * name;
  char * birth_day;
  char gender;
  char*  car_class;
  char * license_plate;
  unsigned short int date;
  char * city;
  char * account_creation;
  bool account_status;
  double total_auferido;
  int avaliacao_total_driver;  
  int numero_viagens_driver;
  double avaliacao_media_driver;
  short int age;
};

void rides_catalog(GHashTable * users_hash, GHashTable * drivers_hash, char* pathfiles);

#endif