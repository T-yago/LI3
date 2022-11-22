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

/*
void get_age (char * v) {
printf ("%s",*v);
age ()
}

void age(int present_date, int present_month, int present_year, int birth_date, int birth_month, int birth_year) {//09/10/2022
int month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
   if (birth_date > present_date) {
      present_date = present_date + month[birth_month - 1];
      present_month = present_month - 1;
   }
   if (birth_month > present_month) {
      present_year = present_year - 1;
      present_month = present_month + 12;
   }
   int final_date = present_date - birth_date;
   int final_month = present_month - birth_month;
   int final_year = present_year - birth_year;
   printf("Present Age Years: %d Months: %d Days: %d", final_year, final_month, final_date);
}
*/

//int main() {
//users_catalog("PeBaptista3");

//struct users** p = catalog;
//printf("%p",p);
//return 0;
//}
 
 
//***************************************************** Funções de encapsulamento de users usadas em riders.c *****************************************
  
//***************************************************** Funções de encapsulamento de users usadas em riders.c *****************************************
  
//***************************************************** Funções de encapsulamento de users usadas em riders.c *****************************************



char * getUsernameUser(GHashTable * users_hash, Users * copyUsers){
  Users * u;
  u = g_hash_table_lookup(users_hash, copyUsers -> username);
  return u -> username;
}


int getDistanceUser(GHashTable * users_hash, Users * copyUsers){
  Users * u;
  u = g_hash_table_lookup(users_hash, copyUsers -> username);
  return u -> distance;
}


unsigned short int getDateUser(GHashTable * users_hash, Users * copyUsers){
  Users * u;
  u = g_hash_table_lookup(users_hash, copyUsers -> username);
  return u -> date;
}



char * getBirthDateUser(GHashTable * users_hash, Users * copyUsers){
  Users * u;
  u = g_hash_table_lookup(users_hash, copyUsers -> username);
  return u -> birth_date;
}



char * getNameUser(GHashTable * users_hash, Users * copyUsers){
  Users * u;
  u = g_hash_table_lookup(users_hash, copyUsers -> username);
  return u -> name;
}


char  getGenderUser(GHashTable * users_hash, Users * copyUsers){
  Users * u;
  u = g_hash_table_lookup(users_hash, copyUsers -> username);
  return u -> gender;
}


short int  getNviagensUser(GHashTable * users_hash, Users * copyUsers){
  Users * u;
  u = g_hash_table_lookup(users_hash, copyUsers -> username);
  return u -> numero_viagens_user;
}


double getAvaliacaoMediaUser(GHashTable * users_hash, Users * copyUsers){
  Users * u;
  u = g_hash_table_lookup(users_hash, copyUsers -> username);
  return u -> avaliacao_media_user;
}


double getTotalGastoUser(GHashTable * users_hash, Users * copyUsers){
  Users * u;
  u = g_hash_table_lookup(users_hash, copyUsers -> username);
  return u -> total_gasto;
}

short int  getAvaliacaoTotalUser(GHashTable * users_hash, Users * copyUsers){
  Users * u;
  u = g_hash_table_lookup(users_hash, copyUsers -> username);
  return u -> avaliacao_total_user;
}

bool getAccountStatusUser(GHashTable * users_hash, Users * copyUsers){
  Users * u;
  u = g_hash_table_lookup(users_hash, copyUsers -> username);
  return u -> account_status;
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void avaliacaoMediaUser(GHashTable * users_hash, Users * copyUsers, double r){
  Users * u;
  u = g_hash_table_lookup(users_hash, copyUsers -> username);
  u ->avaliacao_media_user = r;
}


void incUserNumeroViagens(GHashTable * users_hash, Users * copyUsers){
  Users * u;
  u = g_hash_table_lookup(users_hash, copyUsers -> username);
  u -> numero_viagens_user = copyUsers -> numero_viagens_user + 1;
}


void avaliacaoTotalUser(GHashTable * users_hash, Users * copyUsers, short int r){
  Users * u;
  u = g_hash_table_lookup(users_hash, copyUsers -> username);
  u -> avaliacao_total_user = copyUsers -> avaliacao_total_user + r;
}


void totalDistanceUser(GHashTable * users_hash, Users * copyUsers, int r){
  Users * u;
  u = g_hash_table_lookup(users_hash, copyUsers -> username);
  u -> distance = copyUsers -> distance + r;
}

void dateUser(GHashTable * users_hash, Users * copyUsers, unsigned short int r){
  Users * u;
  u = g_hash_table_lookup(users_hash, copyUsers -> username);
  if (r > u -> date)  u -> date = r;
}


void totalGastoUser(GHashTable * users_hash, Users * copyUsers, double tg){
  Users * u;
  u = g_hash_table_lookup(users_hash, copyUsers -> username);
  u->total_gasto = copyUsers -> total_gasto + tg;
}

