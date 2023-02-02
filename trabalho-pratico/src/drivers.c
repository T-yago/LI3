#include "../includes/drivers.h"
#include "../includes/query1.h"

/**
 * @brief Catálogo dos drivers
 * 
 */
struct catalog_drivers {
  /**
   * @brief Array dos drivers
   * 
   */
  Driver ** array_drivers;
  /**
   * @brief Tamanho do array dos drivers
   * 
   */
  uint array_length;
  /**
   * @brief Array ordenado dos drivers
   * 
   */
  Driver_Aval_Date * top_N_drivers;
  /**
   * @brief Tamanho do array ordenado dos drivers
   * 
   */
  int array_top_N_drivers_length;
};

/**
 * @brief Struct respetiva a cada driver
 */
struct driver {
  /**
   * @brief Nome do driver
   * 
   */
  char * name;
  /**
   * @brief Idade do driver
   * 
   */
  short int age;
  /**
   * @brief Género do driver
   * 
   */
  char gender;
  /**
   * @brief Classe do carro do driver
   * 
   */
  char  car_class;
  /**
   * @brief Matrícula do driver
   * 
   */
  char * license_plate;
  /**
   * @brief Data da última viagem do driver
   * 
   */
  unsigned short int date;
  /**
   * @brief Cidade do driver
   * 
   */
  char * city;
  /**
   * @brief Data de criação do driver em dias
   * 
   */
  unsigned short int account_creation;
  /**
   * @brief Estado da conta do driver
   * 
   */
  bool account_status;
  
  /**
   * @brief Total auferido pelo driver
   * 
   */
  double total_auferido;
  /**
   * @brief Número total de viagens efetuadas pelo driver;
   * 
   */
  int numero_viagens_driver;
  /**
   * @brief Avaliação média do driver
   * 
   */
  double avaliacao_media_driver;
};

//---------------------------------------------Estrutura auxiliar dos drivers (query2) ---------------------------------------------//

/**
 * @brief Struct usada para ordenar os drivers em função da avaliação média, datas e ids
 * 
 */

struct driver_aval_date {
  /**
   * @brief Id do driver
   * 
   */
  int id;
  /**
   * @brief Avaliação média do driver
   * 
   */
  double avaliacao_media;

  /**
   * @brief data da viagem mais recente do driver (convertida)
   * 
   */
  unsigned short int data;
};

// Função de comparação que ordena o array com os top_N_drivers
/**
 * @brief Função de comparação usada para os top_N_drivers
 * 
 * @param a posição arbitrária "a" do array a comparar
 * @param b posição arbitrária "b" do array a comparar
 * @return escolha para ordenação
 */

/**
 * @brief Verifica a validade de um driver perante o que foi lido no .csv
 * 
 * @param tokens array de informações lidas no csv
 * @return -1 se não for válido
 * @return 0 se for válido
 */
int is_valid_driver (char** tokens) {
  
  // se id, name, gender, license_plate ou city forem vazios
  if (strlen (tokens[0]) == 0 || strlen (tokens [1]) == 0 || strlen (tokens [3]) == 0 || strlen (tokens [5]) == 0 || strlen (tokens [6]) == 0) return -1;

  // se as datas forem inválidas
  if (convert_to_day (tokens [2]) == 65535 || convert_to_day (tokens [7]) == 65535 ) return -1;

  // se acc_creation for inválido
  if (!strcasecmp(tokens[8], "active") == 0 && !strcasecmp(tokens[8], "inactive") == 0 )  return -1;
  // se car_class for inválido
  if (!strcasecmp(tokens[4], "basic") == 0 &&  !strcasecmp(tokens[4], "premium") == 0 && !strcasecmp(tokens[4], "green") == 0 )  return -1;

  return 0;
}

/**
 * @brief Cria um driver
 * 
 * @param tokens informações lidas no csv 
 * @param catalog void pointer a ser desreferenciado para catalog_drivers
 * @return apontador para o driver criado 
 */

Driver* create_driver(char** tokens, void* catalog) {
  // Desreferencia apontador
  Catalog_Drivers* catalog_drivers = (Catalog_Drivers*)catalog;
  
  // Fetch das informações do catálogo
  uint num_drivers = catalog_drivers->array_length;
  Driver** array_drivers = catalog_drivers->array_drivers;  

  // Cria espaço para o driver e adiciona a posição ao array
  Driver* driver = malloc(sizeof(Driver));
  

  // Alterar de forma a que não se perca a posição mas não seja preciso encher o array se (is_valid == 1)
  driver->name = strdup(tokens[1]);
  driver->age = calcula_idade (tokens[2]);
  driver->gender = *tokens[3];
  driver->car_class = (tokens[4][0]);
  driver->license_plate = strdup(tokens[5]);
  driver->city = strdup(tokens[6]);
  driver->account_creation = convert_to_day(tokens[7]);
  driver->account_status = (tokens[8][0] == 'a' || tokens[8][0] == 'A');  //se for ("missing" oh "???" retorna false)

// Se o driver for válido, ele permanece no array para preservar as propriedades do índice mas o seu status passa para inválido
  if (is_valid_driver (tokens) == -1)  driver->account_status = false;

    array_drivers[num_drivers] = driver;
    catalog_drivers->array_length++;
    num_drivers++; 
    if (num_drivers % 100 == 0) catalog_drivers->array_drivers = realloc(array_drivers, sizeof(Driver*) * (num_drivers + 100));

return driver; 
}


/**
 * @brief Cria o catálogo dos drivers
 * 
 * @param pathfiles caminho para o csv
 * @return apontador para o catálogo 
 */

Catalog_Drivers * drivers_catalog(char * pathfiles) {
  Driver** array_drivers = malloc (100 * sizeof (Driver*));  

  // Aloca espaço para o catálogo e inicializa os campos
  Catalog_Drivers* catalog_drivers = malloc (sizeof (Catalog_Drivers));
  catalog_drivers -> array_drivers = array_drivers;
  catalog_drivers -> array_length = 0;

  char driverfile[256];
  strcpy(driverfile, pathfiles);
  char * filename = strcat(driverfile, "/drivers.csv");

  // Chama a função de parsing com função que cria o driver
  parse_csv(filename, (create_fn)create_driver, catalog_drivers);
  return catalog_drivers;
}


//---------------------------------------Estrutura auxiliar dos drivers (query2) ---------------------------------------------//
/**
 * @brief Coloca o array ordenado dos drivers no catálogo dos drivers
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @param top_N_drivers Array ordenado dos drivers
 * @param array_length Tamanho do array ordenado dos drivers
 */

void set_top_N_drivers(Catalog_Drivers* catalog_drivers, void* top_N_drivers, int array_length) {
    catalog_drivers->top_N_drivers = (Driver_Aval_Date*) top_N_drivers;
    catalog_drivers->array_top_N_drivers_length = array_length;
}

/**
 * @brief Devolve o array ordenado dos drivers
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @return Void pointer para o array ordenado dos drivers
 */
void* get_top_N_drivers(Catalog_Drivers* catalog_drivers) {
    return (void*) catalog_drivers->top_N_drivers;
}

/**
 * @brief Devolve o tamanho do array ordenado dos drivers
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @return Tamanho do array ordenado dos drivers
 */
int get_array_top_N_drivers_length (Catalog_Drivers* catalog_drivers) {
    return catalog_drivers->array_top_N_drivers_length;
}


int compare(const void * a, const void * b) {
   Driver_Aval_Date *ia = *(Driver_Aval_Date**) a;
   Driver_Aval_Date *ib = *(Driver_Aval_Date**) b;

  if (ia -> avaliacao_media < ib -> avaliacao_media) return 1;

  if (ia -> avaliacao_media > ib -> avaliacao_media) return -1;

  if (ia -> avaliacao_media == ib -> avaliacao_media) {
    if (ia -> data < ib -> data) return 1; 
    if (ia -> data > ib -> data) return -1;
    else if (ia -> data == ib -> data) { 
      return ia->id - ib->id;
    }
  }  return 0;
}

// Função que cria um array com os top "N" users e o coloca no catálogo dos drivers


/**
 * @brief Cria um array com ordenado com os top_N_drivers presentes no catálogo e adiciona-o ao catálogo
 * 
 * @param catalog_drivers catálogo dos drivers
 */

void top_N_drivers (Catalog_Drivers * catalog_drivers) {
  
  uint size = get_array_drivers_size (catalog_drivers);
  Driver_Aval_Date ** driver_aval_date = malloc (sizeof (Driver_Aval_Date*) * 100);
  int array_length = 0;

  // Para cada driver, verifica se é válido e adiciona ao array
  for (uint i = 0; i < size; i++) {
    if (get_driver_acc_Status (catalog_drivers, i) == true) {
    Driver_Aval_Date* aux = malloc (sizeof (Driver_Aval_Date));
    aux -> id = i+1;
    aux -> avaliacao_media = get_driver_avalMedia (catalog_drivers, i);
    aux -> data = get_driver_date (catalog_drivers, i);

    driver_aval_date[array_length] = aux;
    array_length++;
    if (array_length % 100 == 0) driver_aval_date = realloc (driver_aval_date, sizeof (Driver_Aval_Date*) * (array_length + 100));
    }
  }
  qsort((void * ) driver_aval_date, array_length, sizeof(Driver_Aval_Date*), compare);

  set_top_N_drivers (catalog_drivers, driver_aval_date, array_length); 
}

/**
 * @brief Devolve o id do driver presente no array ordenado dos drivers na posição "index"
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @param index Índice do array ordenado
 * @return id do driver
 */

int get_id_driver_top_N (Catalog_Drivers * catalog_drivers, int index) {
  Driver_Aval_Date** top_N_drivers = (Driver_Aval_Date**) get_top_N_drivers (catalog_drivers);
  Driver_Aval_Date* aux = top_N_drivers [index];  
return (aux->id);
}


/**
 * @brief Devolve a avaliação média do driver presente no array ordenado dos drivers na posição "index"
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @param index Índice do array ordenado
 * @return Avaliação média do driver 
 */

double get_aval_med_top_N (Catalog_Drivers * catalog_drivers, int index) {
  Driver_Aval_Date** top_N_drivers = (Driver_Aval_Date**) get_top_N_drivers (catalog_drivers);
  Driver_Aval_Date* aux = top_N_drivers [index]; 
return aux->avaliacao_media;
}

/**
 * @brief Liberta a memória associada ao array ordenado dos drivers
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @param size tamanho do array ordenado dos drivers
 */

void free_top_N_drivers (Catalog_Drivers* catalog_drivers, int size) {
  Driver_Aval_Date** top_N_drivers = (Driver_Aval_Date**) get_top_N_drivers (catalog_drivers);
  for (int i = 0; i < size; i++) {
    Driver_Aval_Date* aux = top_N_drivers [i];
  //  free (aux->name);
    free (aux);
  }
}



//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief Inicializa o array dos drivers para os valores que não são preenchidos pelo csv
 * 
 * @param catalog_drivers Catálogo dos drivers
 */
void init_array_drivers(Catalog_Drivers * catalog_drivers) { 
  uint size = catalog_drivers->array_length;
  Driver * d;
  for (uint i = 0; i < size; i++) {
    d = catalog_drivers->array_drivers[i];
    d -> avaliacao_media_driver = 0;
    d -> numero_viagens_driver = 0;
    d ->total_auferido = 0;
    d-> date = 0;
  }
}

/**
 * @brief Atualiza o valor da avaliação média de cada driver
 * 
 * @param catalog_drivers Catálogo dos drivers
 */
void update_avaliacao_media_driver (Catalog_Drivers * catalog_drivers) {
  uint size = catalog_drivers->array_length;
  Driver* d;
  double r = 0;
  double aval_media;
  int N_viagens;
  for (uint i = 0; i < size; i++) {
    aval_media = get_driver_avalMedia(catalog_drivers, i);
    N_viagens = get_driver_Nviagens(catalog_drivers, i);

    if (N_viagens != 0) 
    {
      r = (float) aval_media / (float) N_viagens;
      
      d = catalog_drivers->array_drivers[i];
      d->avaliacao_media_driver = r;
    }
  
  }
}

/**
 * @brief Preenche o catálogo dos drivers com as informações calculadas pelas rides
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @param catalog_rides Catálogo das rides
 */
void fill_drivers_array (Catalog_Drivers* catalog_drivers, Catalog_Rides* catalog_rides) {
  
  double total_auferido = 0;
  int driver;
  unsigned short int ride_distance = 0;
  double ride_tip = 0;
  Driver* d;
  char car_class;
  float ride_score_driver = 0;
  unsigned short int ride_date;
  int ride_id;

  unsigned int array_rides_length = get_array_rides_length (catalog_rides);
  for (uint i=0; i < array_rides_length; i++) {
    
    ride_id = get_ride_id (catalog_rides,i);
    if (ride_id != -1) {
    
      driver = get_ride_driver (catalog_rides,i);
      d = catalog_drivers->array_drivers[driver-1];

      ride_distance = get_ride_distance (catalog_rides,i);
      ride_tip = get_ride_tip (catalog_rides,i);
      car_class = d->car_class;
      ride_date = get_ride_date (catalog_rides,i);
      total_auferido = calcula_total_gasto(car_class, ride_distance, ride_tip);
      ride_score_driver = get_score_driver_ride (catalog_rides,i);     

      d->total_auferido += total_auferido;
      d->avaliacao_media_driver += ride_score_driver;
      d->numero_viagens_driver++;
      if (ride_date > d->date) d->date = ride_date;
    }
  }
}


//***************************************************** Funções getters *********************************************************

/**
 * @brief Devolve a data de criação de conta (em dias) do driver na posição index do array dos drivers
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @param index Índice no qual se deseja procurar
 * @return data de criação em dias 
 */
unsigned short int get_data_creation_days_driver (Catalog_Drivers* catalog_drivers, int index) {
  Driver * d = catalog_drivers->array_drivers[index]; 
  return d->account_creation;
}

/**
 * @brief Devolve o tamanho do array dos drivers
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @return tamanho do array dos drivers
 */
uint get_array_drivers_size (Catalog_Drivers* catalog_drivers) {
  return catalog_drivers->array_length;
}

/**
 * @brief Devolve o status da conta do driver na posição index do array
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @param index posição do array a procurar
 * @return true se for válido
 * @return false se não for válido
 */

bool get_driver_acc_Status (Catalog_Drivers * catalog_drivers, int index){
  // Um driver é inválido quando o seu índice não faz parte dos índices do array
  if ((uint)index > catalog_drivers->array_length) return false;
  Driver * d = catalog_drivers->array_drivers[index]; 
  return d -> account_status;
}

/**
 * @brief Devolve a avalição média do do driver na posição index do array dos drivers
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @param index Índice do array dos drivers
 * @return Avalição média do do driver 
 */
double get_driver_avalMedia (Catalog_Drivers * catalog_drivers, int index){
  Driver * d = catalog_drivers->array_drivers[index]; 
  return d -> avaliacao_media_driver;
}


/**
 * @brief Devolve a data da viagem mais recente feita pelo driver na posição index do array dos drivers
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @param index Índice do array dos drivers
 * @return double data da viagem mais recente feita pelo driver
 */
double get_driver_date (Catalog_Drivers * catalog_drivers, int index){
  Driver * d = catalog_drivers->array_drivers[index];
  return d -> date;
}

/**
 * @brief Devolve o nome do driver na posição index do array dos drivers
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @param index Índice do array dos drivers
 * @return nome do driver
 */

char * get_driver_name (Catalog_Drivers * catalog_drivers, int index){
  Driver * d = catalog_drivers->array_drivers[index]; 
  return strdup(d -> name);
}


/**
 * @brief Devolve o número de viagens feitas pelo driver na posição index do array dos drivers
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @param index Índice do array dos drivers
 * @return Número de viagens feitas pelo driver
 */

int get_driver_Nviagens (Catalog_Drivers * catalog_drivers, int index){
  Driver * d = catalog_drivers->array_drivers[index]; 
  return d -> numero_viagens_driver;
}




/**
 * @brief Devolve o género do driver na posição index do array dos drivers
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @param index Índice do array dos drivers
 * @return género do driver 
 */

char  get_driver_gender (Catalog_Drivers * catalog_drivers, int index){
  Driver * d = catalog_drivers->array_drivers[index]; 
  return d -> gender;
}


/**
 * @brief Devolve a idade do driver na posição index do array dos drivers
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @param index Índice do array dos drivers
 * @return Idade do driver
 */

short int get_driver_age (Catalog_Drivers * catalog_drivers, int index){
  Driver * d = catalog_drivers->array_drivers[index]; 
  return (d -> age);
}

/**
 * @brief Devolve o total auferido do driver na posição index do array dos drivers
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @param index Índice do array dos drivers
 * @return double 
 */

double get_driver_total_auferido (Catalog_Drivers * catalog_drivers, int index){
  Driver * d = catalog_drivers->array_drivers[index]; 
  return d -> total_auferido;
}

/**
 * @brief Devolve a classe do carro do driver na posição index do array dos drivers
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @param index Índice do array dos drivers
 * @return char* 
 */
char get_driver_carclass (Catalog_Drivers * catalog_drivers, int index){
  Driver * d = catalog_drivers->array_drivers[index]; 
  return (d -> car_class);
}


//--------------------------------------------Função free---------------------------------------------------------//

/**
 * @brief Liberta a memória associada ao catálogo dos drivers
 * 
 * @param catalog_drivers Catálogo dos drivers
 */
void free_drivers_catalog (Catalog_Drivers * catalog_drivers) {
  uint size_array_drivers = catalog_drivers->array_length;
  int array_top_N_drivers_length = catalog_drivers->array_top_N_drivers_length;
  
  for (uint i = 0; i < size_array_drivers; i++) {
  Driver *d = catalog_drivers->array_drivers[i];
  free (d->name);
  free (d->license_plate);
  free (d->city);
  free (d);
  }

  free_top_N_drivers (catalog_drivers, array_top_N_drivers_length);
  free (catalog_drivers->top_N_drivers);
  free (catalog_drivers->array_drivers);
  free (catalog_drivers);
}