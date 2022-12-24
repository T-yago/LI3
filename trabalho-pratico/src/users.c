#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <glib.h>

#include "../includes/users.h"
#include "../includes/parser.h"


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
  char * birth_date;
  char * account_creation;
  char * pay_method;
  bool account_status;
  double total_gasto;
  unsigned short int numero_viagens_user;
  unsigned short int avaliacao_total_user;
};


Users* create_user (char** tokens, void* catalog) {
  Users* user = malloc(sizeof(Users));
  user->username = strdup (tokens[0]);
  user->name = strdup (tokens[1]);
  user->gender = *tokens[2];
  user->birth_date = strdup (tokens[3]);
  user->account_creation = strdup (tokens[4]); 
  user->pay_method = strdup (tokens[5]);
  user->account_status = ((tokens[6][0] == 'a') || (tokens[6][0] == 'A')) == 1;
  
  Catalog_Users* catalog_users = (Catalog_Users*)catalog;
  g_hash_table_insert(catalog_users->hash_users, user->username, user);
  return user;
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

void initHash_users(Catalog_Users * hash_users) {
  uint size = g_hash_table_size ( hash_users->hash_users);
  Users * u;
  gpointer * keys = get_hash_keys_as_array_users (hash_users, size);
  for (uint i = 0; i < size; i++) {
    u = g_hash_table_lookup(hash_users->hash_users, keys[i]);
    u -> date = 0;
    u -> distance = 0;
    u -> total_gasto = 0;
    u -> numero_viagens_user = 0;
    u -> avaliacao_total_user = 0;
  }
  free (keys);
}


//--------------------------------Estrutura auxiliar dos users (query3)--------------------------//

struct user_distance_data{
  char * id;
  int distance;
  char* name;
  unsigned short int data;
};

int compare_users(const void * a, const void * b) {
  User_Distance_Data * ia = (User_Distance_Data * ) a;
  User_Distance_Data * ib = (User_Distance_Data * ) b;

  if (ia -> distance < ib -> distance) return 1;

  if (ia -> distance > ib -> distance) return -1;

  if (ia -> distance == ib -> distance) {
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

void top_N_users (Catalog_Users* catalog_users) {
  uint size_hash = get_hash_size_users (catalog_users);
  User_Distance_Data * user_distance_data = malloc (size_hash * sizeof (User_Distance_Data));
  gpointer * keys = get_hash_keys_as_array_users (catalog_users,size_hash);

  for (uint i=0; i < size_hash;i++) {
    (user_distance_data + i) -> id = getUsernameUser(catalog_users, keys[i]);
    (user_distance_data + i) -> distance = getDistanceUser(catalog_users, keys[i]);
    (user_distance_data + i) -> data = getDateUser(catalog_users, keys[i]);
    (user_distance_data + i) -> name = getNameUser(catalog_users, keys[i]);
  }
  free (keys);
  qsort((void * ) user_distance_data, size_hash, sizeof(struct user_distance_data), compare_users);
  catalog_users->top_N_users = user_distance_data;
}

char * get_top_N_users_id (Catalog_Users* catalog_users,int index) {
  User_Distance_Data aux = catalog_users->top_N_users[index];
  return strdup (aux.id);
}

char * get_top_N_users_name (Catalog_Users* catalog_users, int index) {
  User_Distance_Data aux = catalog_users->top_N_users[index];
  return strdup (aux.name);
}

unsigned short int get_top_N_users_distance (Catalog_Users * catalog_users, int index) {
  User_Distance_Data aux = catalog_users->top_N_users[index];
  return  aux.distance;
}



//***************************************************** Funções de encapsulamento de users usadas em riders.c *****************************************
    

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
  free (u->birth_date);
  free (u->account_creation);
  free (u->pay_method);
  free (u);
  (void)key;/*unused*/
  (void)user_data;/*unused*/
}


void free_users_catalog (Catalog_Users * catalog_users) {
 uint size = g_hash_table_size ( catalog_users->hash_users);
    g_hash_table_foreach(catalog_users->hash_users, (GHFunc)free_user_data, NULL);
    g_hash_table_destroy (catalog_users->hash_users);
    for (uint i = 0; i < size; i++) {
    User_Distance_Data aux = catalog_users->top_N_users[i];
    free (aux.id);
    free (aux.name);
  }
  free (catalog_users->top_N_users);
  free (catalog_users);
}