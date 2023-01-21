#include "../includes/users_services.h"

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
  qsort((void *) user_distance_data, size_hash, sizeof(User_Distance_Data), compare_users);
  set_top_N_users(catalog_users, user_distance_data);
}


char * get_top_N_users_id (Catalog_Users* catalog_users,int index) {
  User_Distance_Data* top_n_users = (User_Distance_Data*) get_top_N_users(catalog_users);
  User_Distance_Data aux = top_n_users[index];  
  return strdup (aux.id);
}

char * get_top_N_users_name (Catalog_Users* catalog_users, int index) {
  User_Distance_Data* top_n_users = (User_Distance_Data*) get_top_N_users(catalog_users);
  User_Distance_Data aux = top_n_users[index];  
  return strdup (aux.name);
}

unsigned short int get_top_N_users_distance (Catalog_Users * catalog_users, int index) {
  User_Distance_Data* top_n_users = (User_Distance_Data*) get_top_N_users(catalog_users);
  User_Distance_Data aux = top_n_users[index];  
  return  aux.distance;
}

void free_users_services (Catalog_Users* catalog_users, unsigned int size) {
  User_Distance_Data* top_N_users = (User_Distance_Data*) get_top_N_users (catalog_users);
  for (uint i = 0; i < size; i++) {
    User_Distance_Data aux = top_N_users[i];
    free (aux.id);
    free (aux.name);
  }
}