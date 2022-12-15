#include <stdio.h>

#include <stdbool.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>

#include <glib.h>

#include "../includes/dates.h"

#include "../includes/query1.h"

#include "../includes/users.h"

#include "../includes/drivers.h"

#include "../includes/query4.h"

#include "../includes/rides.h"

struct catalog_rides {
  GHashTable * hash_rides;
};

struct ride {
  char * id;
  //char * date;
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

Catalog_Rides* rides_catalog(Catalog_Users * users_hash, Catalog_Drivers * drivers_hash, Catalog_Cities * catalog_cities, char * pathfiles) {
  char * line = NULL;
  size_t len;
  GHashTable * hash_rides = g_hash_table_new (g_str_hash, g_str_equal);
  char ridesfile[256];
  strcpy(ridesfile, pathfiles);
  char * filename = strcat(ridesfile, "/rides.csv");
  FILE * file = fopen(filename, "r");
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
          ride -> id = strdup(token);
          break;
        case 1:
          //ride -> date = strdup(token);
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
          ride -> distance = atof(token);
          break;
        case 6:
          ride -> score_user = atof(token);
          break;
        case 7:
          ride -> score_driver = atof(token);
          break;
        case 8:
          ride -> tip = atof(token);
          break;
        case 9:
          ride -> comment = strdup(token);
          break;
        }
        i++;
        
        g_hash_table_insert(hash_rides, ride -> id, ride);
      }
              free (line_aux);

        double total_gasto = 0, total_auferido = 0;
        
        char * driver = strdup (ride->driver);
        char * user = strdup (ride->user);   
        char * city = strdup (ride->city);     
        
        char * car_class = getCarClassDriver(drivers_hash, driver);

        total_gasto = calcula_total_gasto (car_class, ride -> distance, ride -> tip);
        totalGastoUser(users_hash, user, total_gasto);

        //u -> avaliacao_total_user += ride -> score_user;
        avaliacaoTotalUser(users_hash, user, ride -> score_user);

        //u -> numero_viagens_user++;
        incUserNumeroViagens(users_hash,user);

        //u -> distance += ride -> distance;
        totalDistanceUser(users_hash, user, ride -> distance);

        /*
        if (ride -> date > u -> date) {
          u -> date = ride -> date;
        }*/
        dateUser(users_hash, user, ride -> date);

        double total_gasto_sem_tips = calcula_total_gasto (car_class, ride -> distance, 0);
       
        insert_cities_hash (catalog_cities, city, total_gasto_sem_tips);
        
        total_auferido = calcula_total_gasto(car_class, ride -> distance, ride -> tip);
        totalAuferidoDriver(drivers_hash, driver, total_auferido);

        avaliacaoTotalDriver(drivers_hash, driver, ride -> score_driver);

        numeroViagensDriver(drivers_hash, driver);

        dateDriver(drivers_hash, driver, ride -> date);

        free (city);
        free (user);
        free (driver);

  
       free (car_class);
          
 }
  free (line);  
  } while (!feof(file));
 fclose(file);
 Catalog_Rides * catalog_rides = malloc (sizeof (struct catalog_rides));
 catalog_rides->hash_rides = hash_rides; 
  return catalog_rides;
}


void free_hash_rides (Catalog_Rides * catalog_rides) {
 uint size = g_hash_table_size ( catalog_rides->hash_rides);
  Ride *ride ;
  gpointer * keys = g_hash_table_get_keys_as_array (catalog_rides->hash_rides, &size);
  for (uint i = 0; i < size; i++) {
    ride = g_hash_table_lookup(catalog_rides->hash_rides, keys[i]);
    free (ride->id);
    free (ride ->city);
    free (ride-> driver);
    free (ride->user);
    free (ride->comment);
    free (ride);
  }
  free (keys);
   g_hash_table_destroy (catalog_rides->hash_rides);
}


unsigned short int get_ride_date (Catalog_Rides * catalog_rides, char * id) {
  Ride* aux  = g_hash_table_lookup (catalog_rides->hash_rides,id);
return aux->date;
}

unsigned short int get_ride_distance (Catalog_Rides * catalog_rides, char * id) {
  Ride * aux  = g_hash_table_lookup (catalog_rides->hash_rides,id);
  return aux->distance;
}

uint get_hash_rides_size (Catalog_Rides * catalog_rides) {
  uint size = g_hash_table_size (catalog_rides->hash_rides);
  return size;
}

gpointer * get_hash_keys_as_array_rides (Catalog_Rides * catalog_rides, uint size) {
  gpointer * aux = g_hash_table_get_keys_as_array (catalog_rides->hash_rides, &size);
return aux;
}

char * get_ride_driver (Catalog_Rides * catalog_rides, char* id) {
  Ride* aux = g_hash_table_lookup (catalog_rides->hash_rides,id);
  return strdup (aux->driver);
}