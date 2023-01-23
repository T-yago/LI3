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

struct catalog_rides
{
  Ride **array_rides;
  uint array_length;
  Ride_Ages **array_ages_M;
  uint array_ages_M_length;
  Ride_Ages **array_ages_F;
  uint array_ages_F_length;
  Dist_Array* top_dist;
  int top_dist_length;
};

struct ride
{
  int id;
  unsigned short int date;
  int driver;
  char *user;
  char *city;
  unsigned short int distance;
  unsigned short int score_user;
  unsigned short int score_driver;
  double tip;
  // char * comment;
};

int compare_rides(const void *a, const void *b)
{
  const Ride *ride1 = *(Ride **)a;
  const Ride *ride2 = *(Ride **)b;
  return (int)(ride1->date - ride2->date);
}

void sort_rides_by_date(Ride **rides, size_t num_rides)
{
  qsort((void *)rides, num_rides, sizeof(Ride *), compare_rides);
}

Ride *create_ride(char **tokens, void *catalog, int is_valid)
{
  if (is_valid == 1) return NULL; 
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
  if (is_valid == 1) ride->id = -1; // maneira de ver se ride é inválido


 // Para ver se uma ride é válida, verificar se a cidade na qual foi feita é diferente de NULL
  if (ride->date == 65535) ride->id = -1; 
  // Adiciona a ride ao catálogo
  array_rides[num_rides] = ride;
  catalog_rides->array_length++;
  num_rides++;
  if (num_rides % 100 == 0)
    catalog_rides->array_rides = realloc(array_rides, sizeof(Ride *) * (num_rides + 100));

  return ride;
}

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

  // Ordena o catálogo por datas
  // sort_rides_by_date (array_rides, catalog_rides->array_length);

  fclose(file);
  return catalog_rides;
}

// struct definida para a query8
struct ride_ages
{
  int id_driver;
  char *id_user;
  unsigned short int data_creation_user; // as datas de criação são convertidas para dias para se poderem comparar
  unsigned short int data_creation_driver;
  unsigned int id_ride;
};

void init_array_genders(Catalog_Rides *catalog_rides)
{
  Ride_Ages **array_ages_M = malloc(100 * sizeof(Ride_Ages *));
  catalog_rides->array_ages_M = array_ages_M;
  catalog_rides->array_ages_M_length = 0;

  Ride_Ages **array_ages_F = malloc(100 * (sizeof(Ride_Ages *)));
  catalog_rides->array_ages_F = array_ages_F;
  catalog_rides->array_ages_F_length = 0;
}

void insert_arrays_genders(Catalog_Users *catalog_users, Catalog_Drivers *catalog_drivers, Catalog_Rides *catalog_rides, char *user, int driver, int id)
{
  char gender_user = getGenderUser(catalog_users, user);
  char gender_driver = get_driver_gender (catalog_drivers, driver);

  if (gender_driver == gender_user)
  {
    Ride_Ages *ride = malloc(sizeof(Ride_Ages));
    ride->id_driver = driver;
    ride->data_creation_driver = get_data_creation_days_driver(catalog_drivers, driver);
    ride->data_creation_user = get_data_creation_days_user(catalog_users, user);
    ride->id_user = strdup(user);
    ride->id_ride = id;

    if (gender_driver == 'M')
    {

      catalog_rides->array_ages_M[catalog_rides->array_ages_M_length] = ride;
      catalog_rides->array_ages_M_length++;
      if (catalog_rides->array_ages_M_length % 100 == 0)
        catalog_rides->array_ages_M = realloc(catalog_rides->array_ages_M, sizeof(Ride_Ages *) * (catalog_rides->array_ages_M_length + 100));
    }
    else
    {
      catalog_rides->array_ages_F[catalog_rides->array_ages_F_length] = ride;
      catalog_rides->array_ages_F_length++;
      if (catalog_rides->array_ages_F_length % 100 == 0)
        catalog_rides->array_ages_F = realloc(catalog_rides->array_ages_F, sizeof(Ride_Ages *) * (catalog_rides->array_ages_F_length + 100));
    }
  }
}

int compare_rides_ages(const void *a, const void *b)
{
  const Ride_Ages *ride1 = *(Ride_Ages **)a;
  const Ride_Ages *ride2 = *(Ride_Ages **)b;

  if (ride1->data_creation_driver < ride2->data_creation_driver)
    return -1;
  else if (ride1->data_creation_driver > ride2->data_creation_driver)
    return 1;
  else if (ride1->data_creation_driver == ride2->data_creation_driver)
  {
    if (ride1->data_creation_user > ride2->data_creation_user)
      return 1;
    else if (ride1->data_creation_user < ride2->data_creation_user)
      return -1;
    else if (ride1->data_creation_user == ride2->data_creation_user)
    {
      return ride1->id_ride - ride2->id_ride;
    }
  }
  return 0;
}
void sort_array_genders(Catalog_Rides *catalog_rides)
{
  Ride_Ages **aux = catalog_rides->array_ages_F;
  uint length = catalog_rides->array_ages_F_length;
  qsort((void *)aux, length, sizeof(Ride_Ages *), compare_rides_ages);

  aux = catalog_rides->array_ages_M;
  length = catalog_rides->array_ages_M_length;
  qsort((void *)aux, length, sizeof(Ride_Ages *), compare_rides_ages);
}

unsigned int *check_gender_in_rides(Catalog_Rides *catalog_rides, char gender, unsigned short int age_in_days)
{
  unsigned int *array_ids = malloc(10 * sizeof(unsigned int));
  unsigned int cont = 0;
  if (gender == 'M')
  {
    for (unsigned int i = 0; i < catalog_rides->array_ages_M_length; i++)
    {
      Ride_Ages *ride = catalog_rides->array_ages_M[i];

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
    for (unsigned int i = 0; i < catalog_rides->array_ages_F_length; i++)
    {
      Ride_Ages *ride = catalog_rides->array_ages_F[i];
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

void set_top_dist(Catalog_Rides *catalog_rides, void* array_dist, int size) {
  catalog_rides->top_dist = (Dist_Array*) array_dist;
  catalog_rides->top_dist_length = size;
}

void* get_top_dist(Catalog_Rides* catalog_rides) {
  return (void*) catalog_rides->top_dist;
}

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
  for (uint i = 0; i < catalog_rides->array_ages_F_length; i++)
  {
    Ride_Ages *aux = catalog_rides->array_ages_F[i];
    free(aux->id_user);
    free(aux);
  }
  for (uint i = 0; i < catalog_rides->array_ages_M_length; i++)
  {
    Ride_Ages *aux = catalog_rides->array_ages_M[i];
    free(aux->id_user);
    free(aux);
  }
  // Fazer estes frees aqui ou nas suas próprias funções?
  free(catalog_rides->array_ages_F);
  free(catalog_rides->array_ages_M);
  free(catalog_rides->array_rides);

  free_array_top_dist (catalog_rides);
  free (catalog_rides->top_dist);
  free(catalog_rides);
}

//------------------------------------------------------------------------------------------------------------------------//

// Pertence ao array top_dist
int get_top_dist_length(Catalog_Rides *catalog_rides) {
  return catalog_rides->top_dist_length;
}

//------------------------------------------------------------------------------------------------------------------------//


uint get_array_rides_length(Catalog_Rides *catalog_rides)
{
  return catalog_rides->array_length;
}

int get_ride_id (Catalog_Rides* catalog_rides, int index) {
  Ride* aux = catalog_rides->array_rides [index];
  return aux->id;
}

unsigned short int get_ride_date(Catalog_Rides *catalog_rides, int index)
{
  Ride *aux = catalog_rides->array_rides[index];
  return aux->date;
}

unsigned short int get_ride_distance(Catalog_Rides *catalog_rides, int index)
{
  Ride *aux = catalog_rides->array_rides[index];
  return aux->distance;
}

int get_ride_driver(Catalog_Rides *catalog_rides, int index)
{
  Ride *aux = catalog_rides->array_rides[index];
  return aux->driver;
}

char *get_ride_city(Catalog_Rides *catalog_rides, int index)
{
  Ride *aux = catalog_rides->array_rides[index];
  return strdup(aux->city);
}

double get_ride_tip(Catalog_Rides *catalog_rides, int index)
{
  Ride *aux = catalog_rides->array_rides[index];
  return aux->tip;
}

char *get_ride_user(Catalog_Rides *catalog_rides, int index)
{
  Ride *aux = catalog_rides->array_rides[index];
  return strdup(aux->user);
}

unsigned short int get_score_user_ride(Catalog_Rides *catalog_rides, int index)
{
  Ride *aux = catalog_rides->array_rides[index];
  return aux->score_user;
}

unsigned short int get_score_driver_ride(Catalog_Rides *catalog_rides, int index)
{
  Ride *aux = catalog_rides->array_rides[index];
  return aux->score_driver;
}
