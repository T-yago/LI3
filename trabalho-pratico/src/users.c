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
#include "../includes/drivers.h"

/**
 * @brief Catálodo dos users
 * 
 */
struct catalog_users {
  /**
   * @brief Hashtable dos users
   * 
   */
  GHashTable * hash_users;
  /**
   * @brief Array com as cópias dos users ordenados por distâncias, datas e ids
   * 
   */
  User_Distance_Data* top_N_users;
  /**
   * @brief Tamanho do array com as cópias dos users ordenados por distâncias, datas e ids
   * 
   */
  int top_N_users_length;
};

/**
 * @brief Struct respetiva a cada user
 * 
 */
struct user {
  /**
   * @brief Username
   * 
   */
  char * username;
  /**
   * @brief Nome do user
   * 
   */
  char * name;
  /**
   * @brief Género do user
   * 
   */
  char gender;
  /**
   * @brief Distância do user
   * 
   */
  unsigned short int date;
  /**
   * @brief Distância total percorrida pelo user
   * 
   */
  unsigned short int distance;
  /**
   * @brief Idade do user
   * 
   */
  short int age;
  /**
   * @brief Data de criação da conta do user
   * 
   */
  unsigned short int account_creation;
  /**
   * @brief Método de pagamento usado pelo user
   * 
   */
  char * pay_method;
  /**
   * @brief Status da conta do user
   * 
   */
  bool account_status;
  /**
   * @brief Total gasto pelo user 
   * 
   */
  double total_gasto;
  /**
   * @brief Número de viagens feitas pelo user
   * 
   */
  unsigned short int numero_viagens_user;
  /**
   * @brief Avalição média do user
   * 
   */
  double avaliacao_media_user;
};


/**
 * @brief Verifica se uma linha corresponde a um user válido
 * 
 * @param tokens Linha a avaliar
 * @return -1 se não for válido
 * @return 0 se for válido
 */

int is_valid_user (char** tokens) {
  // se username, name, gender, pay_method forem vazioss
  if (strlen (tokens[0]) == 0 || strlen (tokens [1]) == 0 || strlen (tokens [2]) == 0 || strlen (tokens [5]) == 0) return -1;

  // se datsas for inválidas
  if (convert_to_day (tokens[4]) == 65535 || convert_to_day (tokens[3]) == 65535)  return -1;

  // se o acc_status for inválido
  if (!strcasecmp(tokens[6], "active") == 0 && !strcasecmp(tokens[6], "inactive") == 0 )  return -1;
  return 0;
}

/**
 * @brief Cria um user e adiciona-o ao catálogo dos users
 * 
 * @param tokens linha possivelmente válida de um user
 * @param catalog Catálogo do user
 * @return User criado
 */
User* create_user (char** tokens, void* catalog) {
  
  if (is_valid_user (tokens)== -1) return NULL;
  else{


  User* user = malloc(sizeof(User));

  // se algum outro campo for inválido, o status é modificado
  user->username = strdup (tokens[0]);
  user->name = strdup (tokens[1]);
  user->gender = *tokens[2];
  user->age = calcula_idade (tokens[3]);
  user->account_creation = convert_to_day (tokens[4]); 
  user->pay_method = strdup (tokens[5]);
  user->account_status = ((tokens[6][0] == 'a') || (tokens[6][0] == 'A')); //se for ("missing" oh "???" retorna false)

  
  Catalog_Users* catalog_users = (Catalog_Users*)catalog;
  g_hash_table_insert(catalog_users->hash_users, user->username, user);
  return user;
  }
}

/**
 * @brief Cria o catálogo dos users
 * 
 * @param pathfiles Caminho para o ".csv" dos users
 * @return Catálogo dos users
 */
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

/**
 * @brief Inicializa os valores que serão posteriormente preenchidos através das rides
 * 
 * @param key Chave da hashtable (id do user)
 * @param value User (struct user)
 * @param user_data Informação adicional (não usado)
 */
static void foreach_init(gpointer key, gpointer value, gpointer user_data) {
    User * u = (User*)value;
    u -> date = 0;
    u -> distance = 0;
    u -> total_gasto = 0;
    u -> numero_viagens_user = 0;
    u -> avaliacao_media_user = 0;
  (void) key;/*unused*/
  (void) user_data;/*unused*/
}


/**
 * @brief Para cada user da hashtable, inicializa os valores que serão posteriormente preenchidos através das rides
 * 
 * @param catalog_users Catálogo dos users
 */
void initHash_users(Catalog_Users * catalog_users) {
  g_hash_table_foreach(catalog_users->hash_users, (GHFunc)foreach_init, NULL);
}


/**
 * @brief Preenche a hashtable dos users com as informações do catálogo das rides
 * 
 * @param catalog_users Catálogo dos users
 * @param catalog_rides Catálogo das rides
 * @param catalog_drivers Catálogo dos drivers
 */
void fill_users_hash (Catalog_Users* catalog_users, Catalog_Rides* catalog_rides, Catalog_Drivers* catalog_drivers) {

  double total_gasto = 0;
  int ride_id;
  int driver;
  unsigned short int ride_distance = 0;
  char car_class;
  double ride_tip = 0;
  char* user;
  unsigned short int ride_date;
  User* u;
  float ride_score_user;



  unsigned int array_rides_length = get_array_rides_length (catalog_rides);
  for (uint i=0; i < array_rides_length; i++) {
    
    ride_id = get_ride_id (catalog_rides,i);
    if (ride_id != -1) {
      
      driver = get_ride_driver (catalog_rides,i);
      car_class = get_driver_carclass(catalog_drivers, driver-1);
      ride_distance = get_ride_distance (catalog_rides,i);
      ride_tip = get_ride_tip (catalog_rides,i);
      total_gasto = calcula_total_gasto (car_class,ride_distance,ride_tip);
      user = get_ride_user (catalog_rides,i);
      ride_score_user = get_score_user_ride (catalog_rides, i);
      ride_date = get_ride_date (catalog_rides,i);

      
      u = g_hash_table_lookup (catalog_users->hash_users,user);
      u -> total_gasto += total_gasto;
      u -> avaliacao_media_user += ride_score_user;
      u -> numero_viagens_user++;
      u -> distance += ride_distance;
      if (ride_date > u -> date) u->date = ride_date;

    free (user);
   }
  }
}

/**
 * @brief Para um user atualiza o valor da avaliação média do user
 * 
 * @param key Chave da hashtable dos users (id do user)
 * @param value Valor da hashtable (struct user)
 * @param user_data Informação adicional (não usado)
 */

static void update_aval_media_user (gpointer key, gpointer value, gpointer user_data) {
    
    User * u = (User*)value;
    double r = 0;
    double aval_media = u -> avaliacao_media_user;
    unsigned short int N_viagens = u -> numero_viagens_user;

    if (N_viagens != 0) {
      r = (float) aval_media / (float) N_viagens;
      u -> avaliacao_media_user = r;
    }
  (void) key;/*unused*/
  (void) user_data;/*unused*/
}

/**
 * @brief Atualiza as avaliações médias dos users depois de serem preenchidas pelo catálogo das rides
 * 
 * @param catalog_users Catálogo dos users
 */

void update_aval_medias_users (Catalog_Users* catalog_users) {
  g_hash_table_foreach (catalog_users->hash_users, (GHFunc)update_aval_media_user, NULL);
}


//--------------------------------Estrutura auxiliar dos users (query3)--------------------------//

/**
 * @brief Coloca o array ordenado dos users no catálogo dos users
 * 
 * @param catalog_users Catálogo dos users
 * @param top_N_users Array ordenado dos users
 */

void set_top_N_users(Catalog_Users* catalog_users, void* top_N_users, int array_length) {
    catalog_users->top_N_users = (User_Distance_Data*) top_N_users;
    catalog_users->top_N_users_length = array_length;
}

/**
 * @brief Devolve o array ordenado dos users do catálogo dos users
 * 
 * @param catalog_users Catálogo dos users
 * @return Array ordenado dos users
 */
void* get_top_N_users(Catalog_Users* catalog_users) {
    return (void*) catalog_users->top_N_users;
}
//***************************************************** Funções de encapsulamento de users usadas em riders.c *****************************************
    
/**
 * @brief Devolve a data de criação do user 
 * 
 * @param catalog_users Catálogo do users
 * @param key Id do user
 * @return Data de criação do user 
 */
unsigned short int get_data_creation_days_user (Catalog_Users* catalog_users, char* key) {
  User * u;
  u = g_hash_table_lookup(catalog_users->hash_users, key);
  return u->account_creation;
}    

/**
 * @brief Devolve o tamanho da hashtable dos users
 * 
 * @param catalog_users Catálogo dos usrs
 * @return Tamanho da hashtable dos users
 */
uint get_hash_size_users (Catalog_Users * catalog_users) {
  uint size = g_hash_table_size (catalog_users->hash_users);
  return size;
}

/**
 * @brief Devolve um array com as cópias das chaves da hashtable
 * 
 * @param catalog_users Catálogo dos users
 * @param size Tamanho da hashtable dos users
 * @return Array com as cópias das chaves da hashtable
 */
gpointer * get_hash_keys_as_array_users (Catalog_Users * catalog_users, uint size) {
  gpointer * aux = g_hash_table_get_keys_as_array (catalog_users->hash_users, &size);
  return aux;
}

/**
 * @brief Devolve o username do user com um certo id
 * 
 * @param catalog_users Catálogo dos users
 * @param id Id do user
 * @return Username 
 */
char * getUsernameUser(Catalog_Users * catalog_users, char* id){
  User * u;
  u = g_hash_table_lookup(catalog_users->hash_users, id);
  return strdup(u -> username);
}

/**
 * @brief Devolve a distância percorrida por um user com um certo id
 * 
 * @param catalog_users Catálogo dos users
 * @param id Id do user
 * @return Distância percorrida
 */
int getDistanceUser(Catalog_Users * catalog_users, char* id){
  User * u;
  u = g_hash_table_lookup(catalog_users->hash_users, id);
  return u -> distance;
}

/**
 * @brief Devolve a data do user com um certo id
 * 
 * @param catalog_users Catálogo dos users 
 * @param id Id do user
 * @return Data do user
 */

unsigned short int getDateUser(Catalog_Users * catalog_users, char* id){
  User * u;
  u = g_hash_table_lookup(catalog_users->hash_users, id);
  return u -> date;
}


/**
 * @brief Devolve a idade do user com um certo id
 * 
 * @param catalog_users Catálogo dos users
 * @param id Id do user
 * @return Idade do user
 */

short int get_age_user(Catalog_Users * catalog_users, char* id){
  User * u;
  u = g_hash_table_lookup(catalog_users->hash_users, id);
  return  u -> age;
}


/**
 * @brief Devolve o nome do user com um certo id
 * 
 * @param catalog_users Catálogo dos users
 * @param id Id do user
 * @return Nome do user
 */
char * getNameUser(Catalog_Users * catalog_users, char* id){
  User * u;
  u = g_hash_table_lookup(catalog_users->hash_users, id);
  return strdup(u -> name);
}


/**
 * @brief Devolve o género do user com um certo id
 * 
 * @param catalog_users Catálogo dos users
 * @param id Id do user
 * @return Género do user
 */
char  getGenderUser(Catalog_Users * catalog_users, char* id){
  User * u;
  u = g_hash_table_lookup(catalog_users->hash_users, id);
  return u -> gender;
}

/**
 * @brief Devolve o número de viagens do user com um certo id
 * 
 * @param catalog_users Catálogo dos users
 * @param id Id do user
 * @return Número de viagens
 */
short int  getNviagensUser(Catalog_Users * catalog_users, char* id){
  User * u;
  u = g_hash_table_lookup(catalog_users->hash_users, id);
  return u -> numero_viagens_user;
}


/**
 * @brief Devolve o total gasto de um user com um certo id
 * 
 * @param catalog_users Catálogo dos users
 * @param id Id do user
 * @return Total gasto
 */
double getTotalGastoUser(Catalog_Users * catalog_users, char* id){
  User * u;
  u = g_hash_table_lookup(catalog_users->hash_users, id);
  return u -> total_gasto;
}

/**
 * @brief Devolve a avaliação média de um user com um certo id
 * 
 * @param catalog_users Catálogo dos users
 * @param id Id do user
 * @return Avaliação média do user 
 */
double get_aval_media_user(Catalog_Users * catalog_users, char* id){
  User * u;
  u = g_hash_table_lookup(catalog_users->hash_users, id);
  return u -> avaliacao_media_user;
}

/**
 * @brief Devolve o account status de um user com um certo id
 * 
 * @param catalog_users Catálogo dos users
 * @param id Id do user
 * @return True se o status for verdadeiro
 * @return False se o status for falso
 */

bool getAccountStatusUser(Catalog_Users * catalog_users, char* id){
  User * u; // incluir opcao para o caso de nao haver na hash
  u = g_hash_table_lookup(catalog_users->hash_users, id);
  if (u== NULL) return false;
  return u -> account_status;
}


//--------------------------Funções que interagem com o catálogo dos users-----------------------------------------------------------------------------------------------------------------



//----------------------------------------------Função free--------------------------------------------------//

/**
 * @brief Liberta a memória associada a um user
 * 
 * @param key Chave da hashtable (id do usedr)
 * @param value Valor da hashtable (struct user)
 * @param user_data Informação adicional (não usada)
 */
void free_user_data(gpointer key, gpointer value, gpointer user_data) {
  User *u = (User *)value;
  free (u->username);
  free (u->name);
  free (u->pay_method);
  free (u);
  (void)key;/*unused*/
  (void)user_data;/*unused*/
}

/**
 * @brief Liberta a memória associada ao catálogo dos users
 * 
 * @param catalog_users Catálogo dos users
 */
void free_users_catalog (Catalog_Users * catalog_users) {
 unsigned int size = catalog_users->top_N_users_length;
  g_hash_table_foreach(catalog_users->hash_users, (GHFunc)free_user_data, NULL);
  g_hash_table_destroy (catalog_users->hash_users);
  free_users_services (catalog_users, size);
  free (catalog_users->top_N_users);
  free (catalog_users);
}

