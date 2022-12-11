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
  int distance;
  short int score_user;
  short int score_driver;
  double tip;
  char * comment;
};

Catalog_Rides* rides_catalog(Catalog_Users * users_hash, Catalog_Drivers * drivers_hash, Catalog_Cities * catalog_cities, char * pathfiles) {
  char * line = NULL;
  size_t len;
  GHashTable * hash_rides = g_hash_table_new(g_str_hash, g_str_equal);
  char ridesfile[256];
  strcpy(ridesfile, pathfiles);
  char * filename = strcat(ridesfile, "/rides.csv");
  FILE * file = fopen(filename, "r");
  int j = 0;

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
 //escrever aqui o que colocar a cada iteracao de user
      if (j == 0) {
        j++;
      } else {
        double total_gasto = 0, total_auferido = 0;
        char * car_class = getCarClassDriver(drivers_hash, ride->driver);
        //u -> total_gasto += calcula_total_gasto(d -> car_class, ride -> distance, ride -> tip);
        total_gasto = calcula_total_gasto (car_class, ride -> distance, ride -> tip);
        totalGastoUser(users_hash, ride->user, total_gasto);

        //u -> avaliacao_total_user += ride -> score_user;
        avaliacaoTotalUser(users_hash, ride->user, ride -> score_user);

        //u -> numero_viagens_user++;
        incUserNumeroViagens(users_hash,ride->user);

        //u -> distance += ride -> distance;
        totalDistanceUser(users_hash, ride->user, ride -> distance);

        /*
        if (ride -> date > u -> date) {
          u -> date = ride -> date;
        }*/
        dateUser(users_hash, ride->user, ride -> date);

        double total_gasto_sem_tips = calcula_total_gasto (car_class, ride -> distance, 0);
       
        insert_cities_hash (catalog_cities, ride->city, total_gasto_sem_tips);
        
        total_auferido = calcula_total_gasto(car_class, ride -> distance, ride -> tip);
        totalAuferidoDriver(drivers_hash, ride->driver, total_auferido);

        //d -> avaliacao_total_driver += ride -> score_driver;
        avaliacaoTotalDriver(drivers_hash, ride->driver, ride -> score_driver);

        //d -> numero_viagens_driver++;
        numeroViagensDriver(drivers_hash, ride->driver);

        /*
        if (ride -> date > d -> date) {
          d -> date = ride -> date;
        }*/
        dateDriver(drivers_hash, ride->driver, ride -> date);

        //double gasto_por_ride = calcula_total_gasto (car_class, ride -> distance, 0);
        //insert_cities_hash (cities_catalog,ride->city,gasto_por_ride);
  
       // free (car_class);
//printf ("%s\n",u->username);
      }      //char *line_copy = strdup(line);
   // free (ride->id);
    //free (ride->driver);
    //free (ride->user);
    //free (ride->city);
    //free (ride->comment);     
    //free (ride); //g_hash_table_insert(hash_rides, ride -> id, ride);
    }
  free (line);
    
  } while (!feof(file));
 fclose(file);
 Catalog_Rides * catalog_rides = malloc (sizeof (struct catalog_rides));
 catalog_rides->hash_rides = hash_rides; 
  return catalog_rides;
}



unsigned short int get_ride_date (Catalog_Rides * catalog_rides, char * id) {
  Ride* aux  = g_hash_table_lookup (catalog_rides->hash_rides,id);
return aux->date;
}

int get_ride_distance (Catalog_Rides * catalog_rides, char * id) {
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