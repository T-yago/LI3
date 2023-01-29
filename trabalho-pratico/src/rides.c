#include <stdio.h>

#include <stdbool.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>

#include <glib.h>

#include "../includes/parser.h"

#include "../includes/dates.h"

#include "../includes/query1.h"

#include "../includes/query4.h"

#include "../includes/rides.h"

#include "../includes/rides_services.h"
#include <math.h>

/**
 * @brief Struct respetiva ao catálogo das viagens
 * 
 */
struct catalog_rides
{
  /**
   * @brief Array das viagens
   * 
   */
  Ride **array_rides;
  /**
   * @brief Comprimento do array das viagens
   * 
   */
  uint array_length;
  /**
   * @brief Array das viagens realizadas por membros do sexo masculino
   * 
   */
  Ride_Ages **array_ages_M;
   /**
   * @brief Comprimento do array das viagens realizadas por membros do sexo masculino
   * 
   */
  uint array_ages_M_length;
   /**
   * @brief Array das viagens realizadas por membros do sexo feminino
   * 
   */
  Ride_Ages **array_ages_F;
   /**
   * @brief Comprimento do array das viagens realizadas por membros do sexo feminino
   * 
   */
  uint array_ages_F_length;
  /**
   * @brief Array das viagens ordenadas pela distância por viagem
   * 
   */
  Dist_Array* top_dist;
  /**
   * @brief Comprimento do array das viagens ordenadas pela distância por viagem
   * 
   */
  int top_dist_length;
};


/**
 * @brief Struct respetiva a cada viagem
 * 
 */
struct ride
{
  /**
   * @brief Id
   * 
   */
  int id;
  /**
   * @brief Data em que a viagem foi feita
   * 
   */
  unsigned short int date;
  /**
   * @brief Driver que realizou a viagem
   * 
   */
  int driver;
  /**
   * @brief User que realizou a viagem
   * 
   */
  char *user;
  /**
   * @brief Cidade onde foi realizada a viagem
   * 
   */
  char *city;
  /**
   * @brief Distância da viagem
   * 
   */
  unsigned short int distance;
  /**
   * @brief Avaliação dada ao user nessa viagem
   * 
   */
  unsigned short int score_user;
  /**
   * @brief Avaliação dada ao driver nessa viagem
   * 
   */
  unsigned short int score_driver;
  /**
   * @brief Gorjeta dada ao driver nessa viagem
   * 
   */
  double tip;
};


/*
int compare_rides(const void *a, const void *b)
{
  const Ride *ride1 = *(Ride **)a;
  const Ride *ride2 = *(Ride **)b;

  return ride1->date - ride2->date;
  }



void sort_rides_by_date(Ride **rides, uint num_rides)
{
  qsort((void *)rides, num_rides, sizeof(Ride *), compare_rides);
}
*/

/**
 * @brief Verifica se uma linha corresponde a uma potencial ride válida
 * 
 * @param tokens linha a avaliar
 * @return -1 se for inválida
 * @return 0 se for válida
 */
int is_valid_ride (char** tokens) {

    // se os campos id, driver, user ou city forem vazios
    for (int i=0; i <= 8;i++) {
      if (strlen (tokens[i]) == 0) return -1;
    }

    if (convert_to_day (tokens[1]) == 65535) return -1;
    
    // se a distância não for um inteiro  >= 0
    if (tokens[5][0] == '0' && strlen(tokens[5]) == 1) return -1;
    for (int i = 0; tokens[5][i] != '\0'; i++) if (!isdigit(tokens[5][i])) return -1;

    // se o score_user não for um valor inteiro > 0
    if (tokens[6][0] == '0' && strlen(tokens[6]) == 1) return -1;
    for (int i = 0; tokens[6][i] != '\0'; i++) if (!isdigit(tokens[6][i])) return -1;
    
    // se o score_user não for um valor inteiro > 0
    if (tokens[7][0] == '0' && strlen(tokens[7]) == 1) return -1;
    for (int i = 0; tokens[7][i] != '\0'; i++) if (!isdigit(tokens[7][i])) return -1;

    // se a tip não for um valor (inteiro ou float) >= 0
    char* end = NULL;
    double ride_tip = strtod (tokens[8],&end);
    if (*end != '\0' || ride_tip < 0 || isnan (ride_tip)) return -1; 

return 0;
}

/**
 * @brief Cria uma ride dada uma linha válida
 * 
 * @param tokens Linha válida de uma ride
 * @param catalog Catálogo das rides
 * @return Ride criada
 */
Ride *create_ride(char **tokens, void *catalog)
{
  if (is_valid_ride (tokens) == -1){
return NULL; 
  } 
   // Desreferencia apontador
  Catalog_Rides *catalog_rides = (Catalog_Rides *)catalog;

  // Fetch das informações do catálogo
  uint num_rides = catalog_rides->array_length;
  Ride **array_rides = catalog_rides->array_rides;


  Ride *ride = malloc(sizeof(struct ride));
  
  ride->id = atoi (tokens[0]);
  ride->date = convert_to_day(tokens[1]);
  ride->driver = atoi(tokens[2]);
  ride->user = strdup(tokens[3]);
  ride->city = strdup(tokens[4]);
  ride->distance = atoi(tokens[5]);
  ride->score_user = atoi(tokens[6]);
  ride->score_driver = atoi(tokens[7]);
  ride->tip = atof(tokens[8]);


  // Adiciona a ride ao catálogo
  array_rides[num_rides] = ride;
  catalog_rides->array_length++;
  num_rides++;
  if (num_rides % 100 == 0)
    catalog_rides->array_rides = realloc(array_rides, sizeof(Ride *) * (num_rides + 100));

  return ride;
}


/**
 * @brief Cria o catálogo das rides
 * 
 * @param pathfiles Caminho do ".csv" das rides
 * @return Catálogo das rides
 */
Catalog_Rides *rides_catalog(char *pathfiles)
{
  Ride **array_rides = malloc(100 * sizeof(Ride *));

  Catalog_Rides *catalog_rides = malloc(sizeof(struct catalog_rides));
  catalog_rides->array_length = 0;
  catalog_rides->array_rides = array_rides;

  // abertura do ficheiro
  char ridesfile[256];
  strcpy(ridesfile, pathfiles);
  char *filename = strcat(ridesfile, "/rides.csv");
  FILE *file = fopen(filename, "r");

  // parsing
  parse_csv(filename, (create_fn)create_ride, catalog_rides);

  fclose(file);
  return catalog_rides;
}

/**
 * @brief Coloca ambos arrays das rides agrupadas por género no catálogo das rides
 * 
 * @param catalog_rides Catálogo das rides
 * @param array_ages_M Array das rides agrupada pelo género masculino
 * @param array_ages_M_length Comprimento do array das rides agrupada pelo género masculino
 * @param array_ages_F Array das rides agrupada pelo género masculino
 * @param array_ages_F_length Comprimento das rides agrupada pelo género masculino
 */
void set_arrays_genders(Catalog_Rides* catalog_rides, void* array_ages_M, uint array_ages_M_length, void* array_ages_F, uint array_ages_F_length)
{
    catalog_rides->array_ages_M = (Ride_Ages**) array_ages_M;
    catalog_rides->array_ages_M_length = array_ages_M_length;
    catalog_rides->array_ages_F = (Ride_Ages**) array_ages_F;
    catalog_rides->array_ages_F_length = array_ages_F_length;
}


/**
 * @brief Devolve o array auxiliar das cópias das rides agrupadas por géneros
 * 
 * @param catalog_rides Catálogo das rides
 * @return Array auxiliar com cópias das rides com membros do sexo feminino
 */
void* get_array_genders_F (Catalog_Rides* catalog_rides) {
  return (void*) catalog_rides->array_ages_F;
}

/**
 * @brief Get the array genders M object
 * 
 * @param catalog_rides Catálogo das rides
 * @return Array auxiliar com cópias das rides com membros do sexo masculino
 */
void* get_array_genders_M (Catalog_Rides* catalog_rides) {
  return (void*) catalog_rides->array_ages_M;
}


/**
 * @brief Set the top dist object
 * 
 * @param catalog_rides Catálogo das rides 
 * @param array_dist Array com cópias das rides ordenadas por distâncias
 * @param size Tamanho do array com cópias das rides ordenadas por distâncias
 */
void set_top_dist(Catalog_Rides *catalog_rides, void* array_dist, int size) {
  catalog_rides->top_dist = (Dist_Array*) array_dist;
  catalog_rides->top_dist_length = size;
}

/**
 * @brief Devolve o array auxiliar com as cópias das rides ordenadas por distâncias
 * 
 * @param catalog_rides Catálogo das rides
 * @return Array auxiliar com as cópias das rides ordenadas por distâncias
 */
void* get_top_dist(Catalog_Rides* catalog_rides) {
  return (void*) catalog_rides->top_dist;
}

/**
 * @brief Liberta a memória associada ao catálogo das rides
 * 
 * @param catalog_rides Catálogo das rides
 */
void free_rides_catalog(Catalog_Rides *catalog_rides)
{
  uint length = catalog_rides->array_length;
  for (uint i = 0; i < length; i++)
  {
    Ride *aux = catalog_rides->array_rides[i];
    free(aux->city);
    // free (aux->comment);
    free(aux->user);
    free(aux);
  }
  free_array_ages_rides (catalog_rides);  

  free(catalog_rides->array_ages_F);
  free(catalog_rides->array_ages_M);



  free(catalog_rides->array_rides);

  free_array_top_dist (catalog_rides);
  free (catalog_rides->top_dist);
  free(catalog_rides);
}

//------------------------------------------------------------------------------------------------------------------------//

/**
 * @brief Devolve o comprimento do array ordenado por distâncias
 * 
 * @param catalog_rides Catálogo das rides
 * @return int 
 */
int get_top_dist_length(Catalog_Rides *catalog_rides) {
  return catalog_rides->top_dist_length;
}

//------------------------------------------------------------------------------------------------------------------------//

/**
 * @brief Devolve o comprimento do array das rides cujos membros são do sexo feminino
 * 
 * @param catalog_rides Catálogo das rides
 * @return Comprimento do array das rides cujos membros são do sexo feminino
 */
uint get_array_genders_F_length (Catalog_Rides* catalog_rides) {
  return catalog_rides->array_ages_F_length;
}

/**
 * @brief Devolve o comprimento do array das rides cujos membros são do sexo masculino
 * 
 * @param catalog_rides Catálogo das rides
 * @return Comprimento do array das rides cujos membros são do sexo masculino 
 */
uint get_array_genders_M_length (Catalog_Rides* catalog_rides) {
  return catalog_rides->array_ages_M_length;
}



//------------------------------------------------------------------------------------------------------------------------//

/**
 * @brief Devolve o comprimento do array das rides
 * 
 * @param catalog_rides Catálogo das rides
 * @return omprimento do array das rides
 */
uint get_array_rides_length(Catalog_Rides *catalog_rides)
{
  return catalog_rides->array_length;
}

/**
 * @brief Devolve o id da ride na posição index do array das rides
 * 
 * @param catalog_rides Catálogo das rides
 * @param index Posição no array das rides
 * @return Id da ride 
 */
int get_ride_id (Catalog_Rides* catalog_rides, int index) {
  Ride* aux = catalog_rides->array_rides [index];
  return aux->id;
}

/**
 * @brief  Devolve a data da ride na posição index do array das rides
 * 
 * @param catalog_rides Catálogo das rides
 * @param index Posição no array das rides
 * @return Data da ride 
 */
unsigned short int get_ride_date(Catalog_Rides *catalog_rides, int index)
{
  Ride *aux = catalog_rides->array_rides[index];
  return aux->date;
}


/**
 * @brief Devolve a distância da ride na posção index do array das rides
 * 
 * @param catalog_rides Catálogo das rides
 * @param index Posição no array das rides
 * @return Distância da ride
 */
unsigned short int get_ride_distance(Catalog_Rides *catalog_rides, int index)
{
  Ride *aux = catalog_rides->array_rides[index];
  return aux->distance;
}


/**
 * @brief Devolve o driver da ride na posição index do array das rides
 * 
 * @param catalog_rides Catálogo das rides
 * @param index Posição no array das rides
 * @return Driver da ride 
 */
int get_ride_driver(Catalog_Rides *catalog_rides, int index)
{
  Ride *aux = catalog_rides->array_rides[index];
  return aux->driver;
}


/**
 * @brief Devolve a cidade da ride na posição index do array das rides
 * 
 * @param catalog_rides Catálogo das rides
 * @param index Posição no array das rides
 * @return Cidade da ride 
 */
char *get_ride_city(Catalog_Rides *catalog_rides, int index)
{
  Ride *aux = catalog_rides->array_rides[index];
  return strdup(aux->city);
}


/**
 * @brief Devolve a gorjeta da ride na posição index do array das rides
 * 
 * @param catalog_rides Catálogo das rides
 * @param index Índice do array das rides
 * @return Gorjeta da ride  
 */
double get_ride_tip(Catalog_Rides *catalog_rides, int index)
{
  Ride *aux = catalog_rides->array_rides[index];
  return aux->tip;
}

/**
 * @brief Devolve o user da ride na posição index do array das rides
 * 
 * @param catalog_rides Catálogo das rides
 * @param index Índice do array das rides
 * @return User da ride
 */
char *get_ride_user(Catalog_Rides *catalog_rides, int index)
{
  Ride *aux = catalog_rides->array_rides[index];
  return strdup(aux->user);
}


/**
 * @brief Devolve o score do user da ride na posição index do array das rides
 * 
 * @param catalog_rides Catálogo das rides
 * @param index Índice do array das rides
 * @return Score do user da ride
 */
unsigned short int get_score_user_ride(Catalog_Rides *catalog_rides, int index)
{
  Ride *aux = catalog_rides->array_rides[index];
  return aux->score_user;
}

/**
 * @brief Devolve o score do driver da ride na posição index do array das rides
 * 
 * @param catalog_rides Catálogo das rides
 * @param index Índice do array das rides
 * @return Score do driver da ride
 */
unsigned short int get_score_driver_ride(Catalog_Rides *catalog_rides, int index)
{
  Ride *aux = catalog_rides->array_rides[index];
  return aux->score_driver;
}
