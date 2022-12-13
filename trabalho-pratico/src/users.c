#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <glib.h>

#include "../includes/users.h"

struct catalog_users {
  GHashTable * hash_users;
};

struct users {
  char * username;
  char * name;
  char gender;
  unsigned short int date;
  unsigned short int distance;
  char * birth_date;
  char * account_creation;
  char * pay_method;
  bool account_status;
  double total_gasto;
  unsigned short int numero_viagens_user;
  unsigned short int avaliacao_total_user;
};
//campo gasto -> incrementar

Catalog_Users * users_catalog(char * pathfiles) {
  char * line = NULL;
  size_t len;
  GHashTable * hash_users = g_hash_table_new(g_str_hash, g_str_equal);
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
      char * line_aux = line;
      while ((token = strsep( & line_aux, ";\n"))) {
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
      free (line_aux);
    }
    free (line);
    i++;
  } while (!feof(file));

  fclose(file);

  Catalog_Users * catalog_users = malloc (sizeof (struct catalog_users));
  catalog_users -> hash_users = hash_users;
return catalog_users;
}

void initHash_users(Catalog_Users * hash_users) {
  //uint size = get_size_users (hash_users);
  uint size = g_hash_table_size ( hash_users->hash_users);
  Users * u;
  gpointer * keys = get_hash_keys_as_array_users (hash_users, size);
  //gpointer * keys = g_hash_table_get_keys_as_array ( hash_users, &size);
  for (uint i = 0; i < size; i++) {
    u = g_hash_table_lookup(hash_users->hash_users, keys[i]);
    u -> date = 0;
    u -> distance = 0;
  }
  free (keys);
}

//***************************************************** Funções de encapsulamento de users usadas em riders.c *****************************************
  
//***************************************************** Funções de encapsulamento de users usadas em riders.c *****************************************
  
//***************************************************** Funções de encapsulamento de users usadas em riders.c *****************************************

void free_hash_users (Catalog_Users * catalog_users) {
 uint size = g_hash_table_size ( catalog_users->hash_users);
  Users * u;
  gpointer * keys = get_hash_keys_as_array_users (catalog_users, size);
  //gpointer * keys = g_hash_table_get_keys_as_array ( hash_users, &size);
  for (uint i = 0; i < size; i++) {
    u = g_hash_table_lookup(catalog_users->hash_users, keys[i]);
    free (u -> username);
    free (u -> name);
    free (u -> birth_date);
    free (u->account_creation);
    free (u->pay_method);
    free (u);
  }
  free(keys);
    g_hash_table_destroy (catalog_users->hash_users);
}


uint get_hash_size_users (Catalog_Users * users_hash) {
  uint size = g_hash_table_size (users_hash->hash_users);
  return size;
}

gpointer * get_hash_keys_as_array_users (Catalog_Users * users_hash, uint size) {
  gpointer * aux = g_hash_table_get_keys_as_array (users_hash->hash_users, &size);
  return aux;
}


char * getUsernameUser(Catalog_Users * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash->hash_users, id);
  return strdup(u -> username);
}


int getDistanceUser(Catalog_Users * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash->hash_users, id);
  return u -> distance;
}


unsigned short int getDateUser(Catalog_Users * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash->hash_users, id);
  return u -> date;
}


char * getBirthDateUser(Catalog_Users * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash->hash_users, id);
  return strdup (u -> birth_date);
}



char * getNameUser(Catalog_Users * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash->hash_users, id);
  return strdup(u -> name);
}


char  getGenderUser(Catalog_Users * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash->hash_users, id);
  return u -> gender;
}


short int  getNviagensUser(Catalog_Users * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash->hash_users, id);
  return u -> numero_viagens_user;
}


//double getAvaliacaoMediaUser(Catalog_Users * users_hash, char* id){
  //Users * u;
  //u = g_hash_table_lookup(users_hash->hash_users, id);
  //return u -> avaliacao_media_user;
//}


double getTotalGastoUser(Catalog_Users * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash->hash_users, id);
  return u -> total_gasto;
}

short int  getAvaliacaoTotalUser(Catalog_Users * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash->hash_users, id);
  return u -> avaliacao_total_user;
}

bool getAccountStatusUser(Catalog_Users * users_hash, char* id){
  Users * u; // incluir opcao para o caso de nao haver na hash
  u = g_hash_table_lookup(users_hash->hash_users, id);
  if (u== NULL) return true;
  return u -> account_status;
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//void avaliacaoMediaUser(Catalog_Users * users_hash, char* id, double r){
 // Users * u;
  //u = g_hash_table_lookup(users_hash->hash_users, id);
  //u ->avaliacao_media_user = r;
//}


void incUserNumeroViagens(Catalog_Users * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash->hash_users, id);
  u -> numero_viagens_user = u-> numero_viagens_user + 1;
}


void avaliacaoTotalUser(Catalog_Users * users_hash, char* id, short int r){
  Users * u;
  u = g_hash_table_lookup(users_hash->hash_users, id);
  u -> avaliacao_total_user = u-> avaliacao_total_user + r;
}


void totalDistanceUser(Catalog_Users * users_hash, char* id, int r){
  Users * u;
  u = g_hash_table_lookup(users_hash->hash_users, id);
  u -> distance = u-> distance + r;
}

void dateUser(Catalog_Users * users_hash, char* id, unsigned short int r){
  Users * u;
  u = g_hash_table_lookup(users_hash->hash_users, id);
  if (r > u -> date)  u -> date = r;
}


void totalGastoUser(Catalog_Users * users_hash, char* id, double tg){
  Users * u;
  u = g_hash_table_lookup(users_hash->hash_users, id);
  u->total_gasto =u-> total_gasto + tg;
}

