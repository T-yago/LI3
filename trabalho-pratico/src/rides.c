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
};

struct ride {
  unsigned int id;
  unsigned short int date;
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
  free (catalog_rides->array_rides);
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

unsigned short int get_score_user_ride (Catalog_Rides* catalog_rides, int index) {
    Ride* aux  = catalog_rides->array_rides[index]; 
  return aux->score_user;
}

unsigned short int get_score_driver_ride (Catalog_Rides* catalog_rides, int index) {
    Ride* aux  = catalog_rides->array_rides[index]; 
  return aux->score_driver;
}



