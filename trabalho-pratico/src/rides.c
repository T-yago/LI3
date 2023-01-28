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
/*
void init_array_genders(Catalog_Rides *catalog_rides)
{
  Ride_Ages **array_ages_M = malloc(100 * sizeof(Ride_Ages *));
  catalog_rides->array_ages_M = array_ages_M;
  catalog_rides->array_ages_M_length = 0;

  Ride_Ages **array_ages_F = malloc(100 * (sizeof(Ride_Ages *)));
  catalog_rides->array_ages_F = array_ages_F;
  catalog_rides->array_ages_F_length = 0;
}
*/


void set_arrays_genders(Catalog_Rides* catalog_rides, void* array_ages_M, uint array_ages_M_length, void* array_ages_F, uint array_ages_F_length)
{
    catalog_rides->array_ages_M = (Ride_Ages**) array_ages_M;
    catalog_rides->array_ages_M_length = array_ages_M_length;
    catalog_rides->array_ages_F = (Ride_Ages**) array_ages_F;
    catalog_rides->array_ages_F_length = array_ages_F_length;
}


void* get_array_genders_F (Catalog_Rides* catalog_rides) {
  return (void*) catalog_rides->array_ages_F;
}

void* get_array_genders_M (Catalog_Rides* catalog_rides) {
  return (void*) catalog_rides->array_ages_M;
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

/*
  for (uint i = 0; i < catalog_rides->array_ages_F_length; i++)
  {
    Ride_Ages *aux = catalog_rides->array_ages_F[i];
    //free(aux->id_user);
    //free(aux);
  }
  for (uint i = 0; i < catalog_rides->array_ages_M_length; i++)
  {
    Ride_Ages *aux = catalog_rides->array_ages_M[i];
    //free(aux->id_user);
    //free(aux);
  }



  // Fazer estes frees aqui ou nas suas próprias funções?
  free(catalog_rides->array_ages_F);
  free(catalog_rides->array_ages_M);
*/


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


uint get_array_genders_F_length (Catalog_Rides* catalog_rides) {
  return catalog_rides->array_ages_F_length;
}

uint get_array_genders_M_length (Catalog_Rides* catalog_rides) {
  return catalog_rides->array_ages_M_length;
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
