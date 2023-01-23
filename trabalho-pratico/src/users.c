#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <glib.h>

#include "../includes/users.h"
#include "../includes/users_services.h"
#include "../includes/parser.h"
#include "../includes/query1.h"
#include "../includes/dates.h"

struct catalog_users {
  GHashTable * hash_users;
  User_Distance_Data* top_N_users;
};

struct users {
  char * username;
  char * name;
  char gender;
  unsigned short int date;
  unsigned short int distance;
  short int age;
  unsigned short int account_creation;
  char * pay_method;
  bool account_status;
  double total_gasto;
  unsigned short int numero_viagens_user;
  unsigned short int avaliacao_total_user;
};


Users* create_user (char** tokens, void* catalog, int is_valid) {

  if (is_valid == 1) return NULL;
  
  else{
  Users* user = malloc(sizeof(Users));

  // se algum outro campo for inválido, o status é modificado
  user->username = strdup (tokens[0]);
  user->name = strdup (tokens[1]);
  user->gender = *tokens[2];
  user->age = calcula_idade (tokens[3]);
  user->account_creation = convert_to_day (tokens[4]); 
  user->pay_method = strdup (tokens[5]);
  user->account_status = ((tokens[6][0] == 'a') || (tokens[6][0] == 'A')); //se for ("missing" oh "???" retorna false)

  // Se a data não for válida
  if (user->account_creation == 65535) user->account_status = false;
  
  Catalog_Users* catalog_users = (Catalog_Users*)catalog;
  g_hash_table_insert(catalog_users->hash_users, user->username, user);
  return user;
  }
}

Catalog_Users * users_catalog(char * pathfiles) {
  
  // Cria a hashtable e adiciona-a ao catálogo
  GHashTable * hash_users = g_hash_table_new(g_str_hash, g_str_equal);
  Catalog_Users * catalog_users = malloc (sizeof (struct catalog_users));
  catalog_users -> hash_users = hash_users;

  //chama a função parser para o ficheiro pretendido
  char userfile[256];
  strcpy(userfile, pathfiles);
  char * filename = strcat(userfile, "/users.csv");
  parse_csv(filename, (create_fn)create_user, catalog_users);

return catalog_users;
}


static void foreach_init(gpointer key, gpointer value, gpointer user_data) {
    Users * u = (Users *)value;
    u -> date = 0;
    u -> distance = 0;
    u -> total_gasto = 0;
    u -> numero_viagens_user = 0;
    u -> avaliacao_total_user = 0;
  (void) key;/*unused*/
  (void) user_data;/*unused*/
}

void initHash_users(Catalog_Users * hash_users) {
  g_hash_table_foreach(hash_users->hash_users, (GHFunc)foreach_init, NULL);
}



//--------------------------------Estrutura auxiliar dos users (query3)--------------------------//

void set_top_N_users(Catalog_Users* catalog_users, void* top_N_users) {
    catalog_users->top_N_users = (User_Distance_Data*) top_N_users;
}
void* get_top_N_users(Catalog_Users* catalog_users) {
    return (void*) catalog_users->top_N_users;
}
//***************************************************** Funções de encapsulamento de users usadas em riders.c *****************************************
    

unsigned short int get_data_creation_days_user (Catalog_Users* catalog_users, char* key) {
  Users * u;
  u = g_hash_table_lookup(catalog_users->hash_users, key);
  return u->account_creation;
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

short int get_age_user(Catalog_Users * users_hash, char* id){
  Users * u;
  u = g_hash_table_lookup(users_hash->hash_users, id);
  return  u -> age;
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
  if (u== NULL) return false;
  return u -> account_status;
}


//--------------------------Funções que interagem com o catálogo dos users-----------------------------------------------------------------------------------------------------------------


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

//----------------------------------------------Função free--------------------------------------------------//

void free_user_data(gpointer key, gpointer value, gpointer user_data) {
  Users *u = (Users *)value;
  free (u->username);
  free (u->name);
  //free (u->birth_date);
//  free (u->account_creation);
  free (u->pay_method);
  free (u);
  (void)key;/*unused*/
  (void)user_data;/*unused*/
}


void free_users_catalog (Catalog_Users * catalog_users) {
 unsigned int size = g_hash_table_size ( catalog_users->hash_users);
  g_hash_table_foreach(catalog_users->hash_users, (GHFunc)free_user_data, NULL);
  g_hash_table_destroy (catalog_users->hash_users);
  free_users_services (catalog_users, size);
  free (catalog_users->top_N_users);
  free (catalog_users);
}

