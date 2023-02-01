#include "../includes/rides_services.h"
#include <stdio.h>
#include <time.h>


struct ride_date {
  int ride_index;
  unsigned short int date; 
};

int compare_dates (const void * a, const void * b) {
  Ride_Date* ia = (Ride_Date*) a;
  Ride_Date* ib = (Ride_Date*) b;

  return ia->date - ib->date;
}


void create_array_rides_sorted (Catalog_Rides* catalog_rides) {
  uint size = get_array_rides_length (catalog_rides);
  Ride_Date* array = malloc (sizeof (Ride_Date) * size);
  
  unsigned short int date;

  for (uint i = 0; i < size; i++) {

    date = get_ride_date (catalog_rides, i);
    array[i].date = date;
    array[i].ride_index = i;
  }
  qsort ((void*)array, size, sizeof (Ride_Date),compare_dates );
  set_array_rides_dates (catalog_rides, array, size);
}


int get_ride_index_sorted_date (Catalog_Rides* catalog_rides, int index) {
  Ride_Date* ride = get_array_rides_ids (catalog_rides);
  return ride[index].ride_index; 
}


/**
 * @brief Struct usada para ordenar os drivers e os users agrupados em género em função da data de criação da conta e do id
 * 
 */
struct ride_ages
{
  /**
   * @brief Id do driver
   * 
   */
  int id_driver;
  /**
   * @brief Id do user
   * 
   */
  char *id_user;
  /**
   * @brief Data de criação da conta do user em dias
   * 
   */
  unsigned short int data_creation_user;
  /**
   * @brief Data de criação do driver em dias
   * 
   */
  unsigned short int data_creation_driver;
  /**
   * @brief Id da viajem
   * 
   */
  unsigned int id_ride;
};


/**
 * @brief Função de comparação para o array das rides argupadas por géneros
 * 
 * @param a void pointer para um elemento do array a ser convertido para comparar
 * @param b void pointer para um elemento do array a ser convertido para comparar
 * @return elemento a escolher na comparação
 */
int compare_rides_ages(const void *a, const void *b)
{
  const Ride_Ages *ride1 = *(Ride_Ages **)a;
  const Ride_Ages *ride2 = *(Ride_Ages **)b;

  if (ride1->data_creation_driver < ride2->data_creation_driver) return -1;

  else if (ride1->data_creation_driver > ride2->data_creation_driver) return 1;

  else 
  {
    if (ride1->data_creation_user > ride2->data_creation_user) return 1;
    
    else if (ride1->data_creation_user < ride2->data_creation_user) return -1;
    
    else return ride1->id_ride - ride2->id_ride;
  }
  return 0;
}

/**
 * @brief Insere o array dos dos drivers e users agrupados por género no catálogo das rides
 * 
 * @param catalog_users Catálogo dos users
 * @param catalog_drivers Catálogo dos drivers
 * @param catalog_rides Catálogo das rides
 */
void insert_arrays_genders(Catalog_Users *catalog_users, Catalog_Drivers *catalog_drivers, Catalog_Rides *catalog_rides)
{
    // Preenche o array dos drivers e users agrupados por géneros
    uint size = get_array_rides_length (catalog_rides);
    
    char gender_user;
    char gender_driver;
    char* user;
    int driver; 
            
    Ride_Ages** array_ages_M = malloc(100 * sizeof(Ride_Ages *));
    Ride_Ages** array_ages_F = malloc (100 * sizeof (Ride_Ages*));
    uint array_ages_M_length = 0;
    uint array_ages_F_length = 0;

    for (uint i = 0; i < size; i++) {
        driver = get_ride_driver (catalog_rides,i);
        user = get_ride_user (catalog_rides,i);
        gender_driver = get_driver_gender (catalog_drivers,driver-1);
        gender_user = getGenderUser (catalog_users, user);

        if (gender_driver == gender_user) {
            
            Ride_Ages *ride = malloc(sizeof(Ride_Ages));
            ride->id_driver = driver-1;
            ride->data_creation_driver = get_data_creation_days_driver(catalog_drivers, driver - 1);
            ride->data_creation_user = get_data_creation_days_user(catalog_users, user);
            ride->id_user = strdup(user);
            ride->id_ride = i;
        
            if (gender_driver == 'M')
            { 
            array_ages_M[array_ages_M_length] = ride;
            array_ages_M_length++;
            if (array_ages_M_length % 100 == 0)
                array_ages_M = realloc(array_ages_M, sizeof(Ride_Ages *) * (array_ages_M_length + 100));
            }
            else
            {
            array_ages_F[array_ages_F_length] = ride;
            array_ages_F_length++;
            if (array_ages_F_length % 100 == 0)
                array_ages_F = realloc(array_ages_F, sizeof(Ride_Ages *) * (array_ages_F_length + 100));
            }
        }
    free (user);
    }
        
    // Coloca o array no catálogo das rides
    set_arrays_genders (catalog_rides, array_ages_M, array_ages_M_length, array_ages_F, array_ages_F_length);
}
  

/**
 * @brief Ordena o array dos drivers e users agrupados por género
 * 
 * @param catalog_rides Catálogo das rides
 */
void sort_array_genders(Catalog_Rides *catalog_rides)
{
  Ride_Ages **aux = (Ride_Ages**) get_array_genders_F (catalog_rides);
  uint length = get_array_genders_F_length (catalog_rides);
  qsort((void *)aux, length, sizeof(Ride_Ages *), compare_rides_ages);

  aux = (Ride_Ages**) get_array_genders_M (catalog_rides);
  length = get_array_genders_M_length (catalog_rides);
  qsort((void *)aux, length, sizeof(Ride_Ages *), compare_rides_ages);
}

/**
 * @brief Devolve um array com as posições no array das rides correspondentes aos drivers (e users) do género "gender" com mais de uma certa idade
 * 
 * @param catalog_rides Catálogo das rides
 * @param gender Género a escolher
 * @param age_in_days Idade em dias de referência
 * @return array com as posições no array das rides correspondentes a esses users e drivers
 */
unsigned int *check_gender_in_rides(Catalog_Rides *catalog_rides, char gender, unsigned short int age_in_days)
{

  Ride_Ages** array_ages_F = (Ride_Ages**) get_array_genders_F (catalog_rides);
  Ride_Ages** array_ages_M = (Ride_Ages**) get_array_genders_M (catalog_rides);
  uint array_ages_F_length = get_array_genders_F_length (catalog_rides);
  uint array_ages_M_length = get_array_genders_M_length (catalog_rides);

  unsigned int *array_ids = malloc(10 * sizeof(unsigned int));
  unsigned int cont = 0;
  if (gender == 'M')
  {
    for (unsigned int i = 0; i <array_ages_M_length; i++)
    {
      Ride_Ages *ride =array_ages_M[i];
      if (ride->data_creation_driver <= age_in_days && ride->data_creation_user <= age_in_days)
      {
        array_ids[cont] = ride->id_ride;
        cont++;
        if (cont % 10 == 0)
          array_ids = realloc(array_ids, sizeof(unsigned int) * (cont + 10));
      }
    }
  }
  else
  {
    for (unsigned int i = 0; i <array_ages_F_length; i++)
    {
      Ride_Ages *ride =array_ages_F[i];
      if (ride->data_creation_driver <= age_in_days && ride->data_creation_user <= age_in_days)
      {
        array_ids[cont] = ride->id_ride;
        cont++;
        if (cont % 10 == 0)
          array_ids = realloc(array_ids, sizeof(unsigned int) * (cont + 10));
      }
    }
  }
  array_ids[cont] = 0; // O último elemento é zero para ser possível iterar sem saber o tamanho
  return array_ids;
}


/**
 * @brief Struct usada para ordenar as rides pela distância, data e id
 * 
 */
struct dist_array
{
  /**
   * @brief Id da ride
   * 
   */
  int ride_id;
  /**
   * @brief Data da ride como inteiro
   * 
   */
  unsigned short int ride_dateint;
  /**
   * @brief Distância percorrida na ride
   * 
   */
  unsigned short int distance;
  /**
   * @brief Índice no qual se encontra a ride com o id "ride_id" no array das rides
   * 
   */
  int array_rides_index;
};

/**
 * @brief Função de comparação para ordenar as rides por distância, data e id
 * 
 * @param a void pointer para um elemento do array a ser convertido para comparar
 * @param b void pointer para um elemento do array a ser convertido para comparar
 * @return escolha para ordenação
 */
int compare_dist(const void *a, const void *b)
{

    Dist_Array *aa = *(Dist_Array**) a;
    Dist_Array *bb = *(Dist_Array**) b;

    // Sort by distance first
    if (aa->distance > bb->distance) return -1;

    else if (aa->distance < bb->distance) return 1;

    // If distances are equal, sort by dateint
    else if (aa->distance == bb->distance) {
        if (aa->ride_dateint > bb->ride_dateint) return -1;

        else if (aa->ride_dateint < bb->ride_dateint) return 1;

        // If distances and dateints are equal, sort by ride_id
        else if (aa->ride_dateint == bb->ride_dateint) {

            if (aa->ride_id > bb->ride_id) return -1;

            else if (aa->ride_id < bb->ride_id) return 1;
        }
    }
    // If everything is equal, return 0
    return 0;
}

/**
 * @brief Preenche o array com as rides ordenadas pela data e adiciona-o ao catálogo
 * 
 * @param catalog_rides Catálogo das rides 
 */
void insert_array_dist (Catalog_Rides* catalog_rides) {
    int size_rides = get_array_rides_length (catalog_rides);
    Dist_Array ** array_dist = malloc (sizeof (Dist_Array*) * 100);
    int array_length = 0;
    int ride_id;

    for (int i = 0; i < size_rides; i++) {
        Dist_Array * aux = malloc(sizeof(Dist_Array)); 
        double tip = get_ride_tip(catalog_rides, i);
        if (tip == 0); // se o tip for 0 não faz nada (avança no loop apenas)
        else {
            ride_id = get_ride_index_sorted_date (catalog_rides,i);
            aux->ride_id =  ride_id;
            aux->ride_dateint = get_ride_date(catalog_rides, ride_id);
            aux->distance = get_ride_distance(catalog_rides, ride_id);
            aux->array_rides_index = ride_id;

            array_dist[array_length] = aux;
            array_length++;
        }
        if (array_length % 100 == 0) array_dist = realloc (array_dist, sizeof(Dist_Array*) * (array_length + 100));
    }
    
    qsort((void * ) array_dist, array_length, sizeof(Dist_Array*), compare_dist);
    set_top_dist(catalog_rides, array_dist, array_length);
}

/**
 * @brief Devolve o id da ride do array ordenado
 * 
 * @param catalog_rides Catálogo das rides
 * @param index Index no array ordenado das rides
 * @return Id da ride do array ordenado
 */
int get_ride_id_dist(Catalog_Rides* catalog_rides, int index) {
    Dist_Array** top_dist = (Dist_Array**) get_top_dist(catalog_rides);
    Dist_Array* aux = top_dist[index];
    return aux->ride_id;
}

/**
 * @brief Devolve o índice onde a viagem que está no array ordenado das rides se encontra no array original das rides
 * 
 * @param catalog_rides Catálogo das rides
 * @param index Índice da viagem no array ordenado das viagens
 * @return Índice onde essa viagem se encontra no array original das rides
 */
int get_array_rides_index_dist (Catalog_Rides* catalog_rides, int index) {
    Dist_Array** top_dist = (Dist_Array**) get_top_dist(catalog_rides);
    Dist_Array* aux = top_dist[index];
    return aux->array_rides_index;
}

/**
 * @brief Devolve a data da viagem que está no array ordenado em dias
 * 
 * @param catalog_rides Catálogo das rides
 * @param index Índice da viagem no array ordenado
 * @return Data em inteiro da viagem
 */
unsigned short int get_ride_dateint_dist(Catalog_Rides* catalog_rides, int index) {
    Dist_Array** top_dist = (Dist_Array**) get_top_dist(catalog_rides);
    Dist_Array* aux = top_dist[index];
    return aux->ride_dateint;
}

/**
 * @brief Devolve a distância da ride no array ordenado das rides
 * 
 * @param catalog_rides Catálogo das rides
 * @param index Índice da viagem no array ordenado
 * @return Distância da ride
 */
unsigned short int get_ride_dist_dist(Catalog_Rides* catalog_rides, int index) {
    Dist_Array** top_dist = (Dist_Array**) get_top_dist(catalog_rides);
    Dist_Array* aux = top_dist[index];
    return aux->distance;
}

/**
 * @brief Liberta a memória associada ao array ordenado por distâncias das viagens
 * 
 * @param catalog_rides Catálogo das rides
 */
void free_array_top_dist (Catalog_Rides* catalog_rides) {
    Dist_Array** top_dist = (Dist_Array**) get_top_dist(catalog_rides);
    int size = get_top_dist_length (catalog_rides);
        Dist_Array* aux = NULL;
        for (int i = 0; i < size; i++) {
            aux = top_dist[i]; 
            free (aux);
        }
}

/**
 * @brief Liberta a memória associada ao array ordenado por géneros das viagens 
 * 
 * @param catalog_rides Catálogo das rides
 */
void free_array_ages_rides (Catalog_Rides* catalog_rides) {
 
  Ride_Ages** array_ages_F = (Ride_Ages**) get_array_genders_F (catalog_rides);
  uint array_ages_F_length = get_array_genders_F_length (catalog_rides);

  Ride_Ages** array_ages_M = (Ride_Ages**) get_array_genders_M (catalog_rides);
  uint array_ages_M_length = get_array_genders_M_length (catalog_rides);


  for (uint i = 0; i < array_ages_F_length; i++)
  {
    Ride_Ages *aux = array_ages_F[i];
    free(aux->id_user);
    free(aux);
  }
  for (uint i = 0; i < array_ages_M_length; i++)
  {
    Ride_Ages *aux = array_ages_M[i];
    free(aux->id_user);
    free(aux);
  }
}