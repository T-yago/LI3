#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <glib.h>
#include "../includes/dates.h"
#include "../includes/query1.h"
#include "../includes/query4.h"
#include "../includes/rides.h"

struct catalog_rides {
  Ride ** array_rides;
  uint array_length;
  Ride_Ages** array_ages_M;
  uint array_ages_M_length;
  Ride_Ages** array_ages_F;
  uint array_ages_F_length;
  Q9 **array_q9;
  uint array_q9_length;
};

struct ride {
  unsigned int id;
  unsigned short int date;
  char* datestr;
  char * driver;
  char * user;
  char * city;
  unsigned short int distance;
  unsigned short int score_user;
  unsigned short int score_driver;
  double tip;
  char * comment;
};

int compare_rides(const void* a, const void* b) {
  const Ride* ride1 = *(Ride**) a;
  const Ride* ride2 = *(Ride**) b;
  return (int)(ride1->date - ride2->date);
}

void sort_rides_by_date(Ride** rides, size_t num_rides) {
  qsort((void*)rides, num_rides, sizeof(Ride*), compare_rides);
}

Catalog_Rides* rides_catalog(char * pathfiles) {
  Ride ** array_rides = malloc(100 * sizeof(Ride*));  
  uint num_rides = 0;
  
  // abertura do ficheiro
  char ridesfile[256];
  strcpy(ridesfile, pathfiles);
  char * filename = strcat(ridesfile, "/rides.csv");
  FILE * file = fopen(filename, "r");
  
  //parsing
  char * line = NULL;
  size_t len;
  getline (&line,&len,file);
  do {
    while (getline( & line, & len, file) != -1) {
      Ride * ride = malloc(sizeof(struct ride));
      char * token;
      int i = 0;
      char * line_aux = line;
      while ((token = strsep( & line_aux, ";\n"))) {
        switch (i) {
        case 0:
          ride -> id = atoi (token);
          break;
        case 1:
          ride -> date = convert_to_day(token);
          ride->datestr = strdup(token);
          break;
        case 2:
          ride -> driver = strdup(token);
          break;
        case 3:
          ride -> user = strdup(token);
          break;
        case 4:
          ride -> city = strdup(token);
          break;
        case 5:
          ride -> distance = atoi (token);
          break;
        case 6:
          ride -> score_user = atoi (token);
          break;
        case 7:
          ride -> score_driver = atoi (token);
          break;
        case 8:
          ride -> tip = atof(token);
          break;
        case 9:
          //ride -> comment = strdup(token);
          break;
        }
        i++;
      }
        // Insere a ride no array e realoca espaço se necessário
        array_rides[num_rides] = ride;
        num_rides++;    
        if (num_rides % 100 == 0) array_rides = realloc(array_rides, sizeof(Ride*) * (num_rides + 100)); 
        free (line_aux);
    }
  free (line);  
  } while (!feof(file));
 
 // Adiciona o array e o seu comprimento ao catálogo
 Catalog_Rides * catalog_rides = malloc (sizeof (struct catalog_rides));
 catalog_rides->array_rides = array_rides; 
 catalog_rides->array_length = num_rides;
 // Ordena o catálogo por datas
 //sort_rides_by_date (catalog_rides->array_rides,catalog_rides->array_length);
fclose(file);
return catalog_rides;
}

struct ride_ages {
  char* id_driver;
  char* id_user;
  unsigned short int data_creation_user;
  unsigned short int data_creation_driver;
  unsigned int id_ride;
};

void init_array_genders (Catalog_Rides* catalog_rides) {
  Ride_Ages** array_ages_M = malloc (100 *sizeof (Ride_Ages*));
  catalog_rides->array_ages_M = array_ages_M;
  catalog_rides->array_ages_M_length = 0;
  Ride_Ages** array_ages_F = malloc (100 * (sizeof (Ride_Ages*)));
  catalog_rides->array_ages_F = array_ages_F;
  catalog_rides->array_ages_F_length = 0;
}

void insert_arrays_genders (Catalog_Users* catalog_users,Catalog_Drivers* catalog_drivers, Catalog_Rides* catalog_rides,  char *user, char* driver, unsigned int id) {
  char gender_user = getGenderUser (catalog_users, user);
  char gender_driver = getGenderDriver (catalog_drivers, driver);
  
  if (gender_driver == gender_user) 
  {
    if (gender_driver == 'M') {
      Ride_Ages * ride = malloc (sizeof (Ride_Ages));
      ride->id_driver = strdup (driver);
      ride->data_creation_driver = get_data_creation_days_driver (catalog_drivers,driver);
      ride->data_creation_user = get_data_creation_days_user (catalog_users, user);
      ride->id_user = strdup (user);
      ride->id_ride = id;
      catalog_rides->array_ages_M [catalog_rides->array_ages_M_length] = ride;
      catalog_rides->array_ages_M_length++;
      if (catalog_rides->array_ages_M_length % 100 == 0) catalog_rides->array_ages_M = realloc(catalog_rides->array_ages_M, sizeof(Ride_Ages*) * (catalog_rides->array_ages_M_length + 100)); 
    }
    else {
      Ride_Ages * ride = malloc (sizeof (Ride_Ages));
      ride->id_driver = strdup (driver);
      ride->data_creation_driver = get_data_creation_days_driver (catalog_drivers,driver);
      ride->data_creation_user = get_data_creation_days_user (catalog_users, user);
      ride->id_user = strdup (user);
      ride->id_ride = id;
      catalog_rides->array_ages_F [catalog_rides->array_ages_F_length] = ride;
      catalog_rides->array_ages_F_length++;
      if (catalog_rides->array_ages_F_length % 100 == 0) catalog_rides->array_ages_F = realloc(catalog_rides->array_ages_F, sizeof(Ride_Ages*) * (catalog_rides->array_ages_F_length + 100)); 
    }
  }
}

int compare_rides_ages (const void* a, const void* b) {
  const Ride_Ages* ride1 = *(Ride_Ages**) a;
  const Ride_Ages* ride2 = *(Ride_Ages**) b;
  if (ride1->data_creation_driver < ride2->data_creation_driver) return -1;
  else if (ride1->data_creation_driver > ride2->data_creation_driver) return 1;
  else if (ride1->data_creation_driver == ride2->data_creation_driver) {
    if (ride1->data_creation_user > ride2->data_creation_user) return 1;
    else if (ride1->data_creation_user < ride2->data_creation_user) return -1;
    else if (ride1->data_creation_user == ride2->data_creation_user) {
      return ride2->id_ride - ride1->id_ride;
    }
  }
  return 0;
}

void sort_array_genders (Catalog_Rides* catalog_rides) {
  Ride_Ages** aux = catalog_rides->array_ages_F;
  uint length = catalog_rides->array_ages_F_length;
  qsort((void*)aux, length, sizeof(Ride_Ages*), compare_rides_ages);
  aux = catalog_rides->array_ages_M;
  length = catalog_rides->array_ages_M_length;
  qsort((void*)aux, length, sizeof(Ride_Ages*), compare_rides_ages);
}

unsigned int * check_gender_in_rides (Catalog_Rides* catalog_rides, char gender, unsigned short int age_in_days) {
  unsigned int * array_ids = malloc (10 * sizeof (unsigned int));
  unsigned int cont = 0;
  if (gender == 'M') {
    for (unsigned int i = 0; i < catalog_rides->array_ages_M_length; i++) {
      Ride_Ages * ride = catalog_rides->array_ages_M [i];
     
      if(ride->data_creation_driver <= age_in_days && ride->data_creation_user <= age_in_days) {
        array_ids [cont] = ride->id_ride;
        cont++;
      if (cont % 10 == 0) array_ids = realloc (array_ids, sizeof (unsigned int) * (cont + 10));
      }
    }
  }
  else {
    for (unsigned int i = 0; i < catalog_rides->array_ages_F_length; i++) {
      Ride_Ages * ride = catalog_rides->array_ages_F [i];
      if (ride->data_creation_driver <= age_in_days && ride->data_creation_user <= age_in_days){
        array_ids [cont] = ride->id_ride;
        cont++;
        if (cont % 10 == 0) array_ids = realloc (array_ids, sizeof (unsigned int) * (cont + 10));
      } 
    }
  }  
  array_ids [cont] = 0; // O último elemento é zero para ser possível iterar sem saber o tamanho
  return array_ids;  
}

struct q9
{
  int ride_id;
  unsigned short int ride_dateint;
  char *ride_date;
  char *city;
  unsigned short int distance;
  double tip;
};

void init_array_q9(Catalog_Rides *catalog_rides)
{
  Q9 **array_q9 = malloc(100000 * sizeof(Q9 *));
  catalog_rides->array_q9 = array_q9;
  catalog_rides->array_q9_length = 0;
}

void insert_array_q9(Catalog_Rides *catalog_rides, int id, unsigned short int ride_distance, char *ride_city, double ride_tip, unsigned short int ride_dateint, int index)
{
  Q9 *q9 = malloc(sizeof(Q9));
  q9->ride_id = id;
  q9->ride_dateint = ride_dateint;
  q9->ride_date = get_ride_datestr(catalog_rides, index);
  q9->distance = ride_distance;
  q9->city = strdup(ride_city);
  q9->tip = ride_tip;
  catalog_rides->array_q9[catalog_rides->array_q9_length] = q9;
  catalog_rides->array_q9_length++;
  if (catalog_rides->array_q9_length % 100000 == 0)
    catalog_rides->array_q9 = realloc(catalog_rides->array_q9, sizeof(Q9 *) * (catalog_rides->array_q9_length + 100000));
}

int compareq9(const void *a, const void *b)
{
  const Q9 *aa = *(Q9 **)a;
  const Q9 *bb = *(Q9 **)b;

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

void sort_arrayq9(Catalog_Rides *catalog_rides)
{
  Q9 **q9 = catalog_rides->array_q9;
  uint length = catalog_rides->array_q9_length;
  qsort((void *)q9, length, sizeof(Q9 *), compareq9);
}

void free_rides_catalog (Catalog_Rides* catalog_rides) {
 uint length = catalog_rides->array_length; 
  for (uint i=0; i < length; i++) {
    Ride* aux = catalog_rides->array_rides[i];
    free (aux->city);
    //free (aux->comment);
    free (aux->driver);
    free (aux->user);
    free (aux);
  }
  for (uint i = 0; i < catalog_rides->array_ages_F_length;i++) {
   Ride_Ages * aux = catalog_rides->array_ages_F[i];
   free (aux->id_driver);
   free (aux->id_user);
  }
  for (uint i = 0; i < catalog_rides->array_ages_M_length;i++) {
    Ride_Ages* aux = catalog_rides->array_ages_M[i];
    free (aux->id_driver);
    free (aux->id_user);
  }
  for (uint i = 0; i < catalog_rides->array_q9_length; i++)
  {
    Q9 *aux = catalog_rides->array_q9[i];
    free(aux->city);
    free(aux->ride_date);
  }
  free (catalog_rides->array_ages_F);
  free (catalog_rides->array_ages_M);
  free (catalog_rides->array_rides);
  free(catalog_rides->array_q9);
  free (catalog_rides);
}

uint get_array_rides_length (Catalog_Rides * catalog_rides) {
  return catalog_rides->array_length;
}
unsigned short int get_ride_date (Catalog_Rides * catalog_rides, int index) {
  Ride* aux  = catalog_rides->array_rides[index]; 
return aux->date;
}
unsigned short int get_ride_distance (Catalog_Rides * catalog_rides, int index) {
  Ride* aux  = catalog_rides->array_rides[index]; 
  return aux->distance;
}
char * get_ride_driver (Catalog_Rides * catalog_rides, int index) {
  Ride* aux  = catalog_rides->array_rides[index]; 
  return strdup (aux->driver);
}
char * get_ride_city (Catalog_Rides * catalog_rides, int index) {
  Ride* aux  = catalog_rides->array_rides[index]; 
  return strdup (aux->city);
}
unsigned int get_ride_id (Catalog_Rides* catalog_rides, int index) {
    Ride* aux  = catalog_rides->array_rides[index]; 
return aux->id;
}
double get_ride_tip (Catalog_Rides* catalog_rides, int index) {
  Ride* aux  = catalog_rides->array_rides[index]; 
return aux->tip;
}
char* get_ride_user (Catalog_Rides* catalog_rides, int index) {
  Ride* aux  = catalog_rides->array_rides[index]; 
  return strdup (aux->user);
}

char* get_ride_datestr(Catalog_Rides* catalog_rides, int index) 
{
  Ride *aux = catalog_rides->array_rides[index];
  return strdup(aux->datestr);
}

unsigned short int get_score_user_ride (Catalog_Rides* catalog_rides, int index) {
    Ride* aux  = catalog_rides->array_rides[index]; 
  return aux->score_user;
}
unsigned short int get_score_driver_ride (Catalog_Rides* catalog_rides, int index) {
    Ride* aux  = catalog_rides->array_rides[index]; 
  return aux->score_driver;
}

int get_arrayq9_size(Catalog_Rides *catalog_rides)
{
  return catalog_rides->array_q9_length;
}

unsigned short int get_ridedateint_q9(Catalog_Rides *catalog_rides, int index) {
  Q9* aux = catalog_rides->array_q9[index];
  return aux->ride_dateint;
}

int get_ride_id_q9(Catalog_Rides *catalog_rides, int index)
{
  Q9 *aux = catalog_rides->array_q9[index];
  return aux->ride_id;
}

char *get_ride_date_q9(Catalog_Rides *catalog_rides, int index)
{
  Q9 *aux = catalog_rides->array_q9[index];
  return aux->ride_date;
}

char *get_ride_city_q9(Catalog_Rides *catalog_rides, int index)
{
  Q9 *aux = catalog_rides->array_q9[index];
  return strdup(aux->city);
}

unsigned short int get_ride_distance_q9(Catalog_Rides *catalog_rides, int index)
{
  Q9 *aux = catalog_rides->array_q9[index];
  return aux->distance;
}

double get_ride_tip_q9(Catalog_Rides *catalog_rides, int index)
{
  Q9 *aux = catalog_rides->array_q9[index];
  return aux->tip;
}