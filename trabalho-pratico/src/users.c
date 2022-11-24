#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <glib.h>

#include "../includes/users.h"

//campo gasto -> incrementar
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
};
//campo gasto -> incrementar

GHashTable * users_catalog(char * pathfiles) {
  char * line = NULL;
  size_t len;
  GHashTable * hash_users = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
  char userfile[256];
  strcpy(userfile, pathfiles);
  char * filename = strcat(userfile, "/users.csv");
  FILE * file = fopen(filename, "r");

  if (file == NULL) {
    printf("Error opening file.\n");
  }
  // int records = 0;
  int i = 0;
  do {
    while (getline( & line, & len, file) != -1) {
      Users * u = malloc(sizeof(struct users));
      char * token;
      int i = 0;
      while ((token = strsep( & line, ";\n"))) {
        switch (i) {
        case 0:
          u -> username = strdup(token);
          break;
        case 1:
          u -> name = strdup(token);
          break;
        case 2:
          u -> gender = * (token);
          break;
        case 3:
          u -> birth_date = strdup(token);
          break;
        case 4:
          u -> account_creation = strdup(token);
          break;
        case 5:
          u -> pay_method = strdup(token);
          break;
        case 6:
          if (strcmp(token, "active")) {
              u -> account_status = true;
            } else {
              u -> account_status = false;
            }
        }
        i++;
      }
      g_hash_table_insert(hash_users, u -> username, u);
    }
    i++;
  } while (!feof(file));

  fclose(file);

  GHashTable * v = hash_users;
  return v;
}

void initHash_users(GHashTable * hash_users) {
  uint size = g_hash_table_size(hash_users);
  Users * u;
  gpointer * keys = g_hash_table_get_keys_as_array(hash_users, & size);
  for (uint i = 0; i < size; i++) {
    u = g_hash_table_lookup(hash_users, keys[i]);
    u -> date = 0;
    u -> distance = 0;
  }
}

//***************************************************** Funções de encapsulamento de users usadas em riders.c *****************************************
  
//***************************************************** Funções de encapsulamento de users usadas em riders.c *****************************************
  
//***************************************************** Funções de encapsulamento de users usadas em riders.c *****************************************



char * getUsernameUser(GHashTable * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash, id);
  return strdup(u -> username);
}


int getDistanceUser(GHashTable * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash, id);
  return u -> distance;
}


unsigned short int getDateUser(GHashTable * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash, id);
  return u -> date;
}



char * getBirthDateUser(GHashTable * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash, id);
  return strdup(u -> birth_date);
}



char * getNameUser(GHashTable * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash, id);
  return strdup(u -> name);
}


char  getGenderUser(GHashTable * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash, id);
  return u -> gender;
}


short int  getNviagensUser(GHashTable * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash, id);
  return u -> numero_viagens_user;
}


double getAvaliacaoMediaUser(GHashTable * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash, id);
  return u -> avaliacao_media_user;
}


double getTotalGastoUser(GHashTable * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash, id);
  return u -> total_gasto;
}

short int  getAvaliacaoTotalUser(GHashTable * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash, id);
  return u -> avaliacao_total_user;
}

bool getAccountStatusUser(GHashTable * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash, id);
  return u -> account_status;
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void avaliacaoMediaUser(GHashTable * users_hash, char* id, double r){
  Users * u;
  u = g_hash_table_lookup(users_hash, id);
  u ->avaliacao_media_user = r;
}


void incUserNumeroViagens(GHashTable * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash, id);
  u -> numero_viagens_user = u-> numero_viagens_user + 1;
}


void avaliacaoTotalUser(GHashTable * users_hash, char* id, short int r){
  Users * u;
  u = g_hash_table_lookup(users_hash, id);
  u -> avaliacao_total_user = u-> avaliacao_total_user + r;
}


void totalDistanceUser(GHashTable * users_hash, char* id, int r){
  Users * u;
  u = g_hash_table_lookup(users_hash, id);
  u -> distance = u-> distance + r;
}

void dateUser(GHashTable * users_hash, char* id, unsigned short int r){
  Users * u;
  u = g_hash_table_lookup(users_hash, id);
  if (r > u -> date)  u -> date = r;
}


void totalGastoUser(GHashTable * users_hash, char* id, double tg){
  Users * u;
  u = g_hash_table_lookup(users_hash, id);
  u->total_gasto =u-> total_gasto + tg;
}

