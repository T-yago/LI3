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

#include "../includes/rides.h"

struct rides {
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

void rides_catalog(GHashTable * users_hash, GHashTable * drivers_hash, char * pathfiles) {
  char * line = NULL;
  size_t len;
  //GHashTable * hash_rides = g_hash_table_new(g_str_hash, g_str_equal);
  char ridesfile[256];
  strcpy(ridesfile, pathfiles);
  char * filename = strcat(ridesfile, "/rides.csv");
  FILE * file = fopen(filename, "r");
  int i = 0;
  int j = 0;

  do {

    while (getline( & line, & len, file) != -1) {
      Rides * ride = malloc(sizeof(struct rides));

      char * token;
      int i = 0;
      while ((token = strsep( & line, ";\n"))) {
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
        
       // g_hash_table_insert(hash_rides, ride -> id, ride);
      } //escrever aqui o que colocar a cada iteracao de user
      if (j == 0) {
        j++;
      } else {
        double tg = 0, ta = 0;
        
        //u -> total_gasto += calcula_total_gasto(d -> car_class, ride -> distance, ride -> tip);
        tg = calcula_total_gasto (getCarClassDriver(drivers_hash, ride->driver), ride -> distance, ride -> tip);
        totalGastoUser(users_hash, ride->user, tg);

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


        //d -> total_auferido += calcula_total_gasto(getCarClassDriver(drivers_hash, d), ride -> distance, ride -> tip);
        ta = calcula_total_gasto(getCarClassDriver(drivers_hash, ride->driver), ride -> distance, ride -> tip);
        totalAuferidoDriver(drivers_hash, ride->driver, ta);

        //d -> avaliacao_total_driver += ride -> score_driver;
        avaliacaoTotalDriver(drivers_hash, ride->driver, ride -> score_driver);

        //d -> numero_viagens_driver++;
        numeroViagensDriver(drivers_hash, ride->driver);

        /*
        if (ride -> date > d -> date) {
          d -> date = ride -> date;
        }*/
        dateDriver(drivers_hash, ride->driver, ride -> date);

        free (ride);
        //printf ("%s\n",u->username);
      }

      //char *line_copy = strdup(line);
      //g_hash_table_insert(hash_rides, ride -> id, ride);
    }
    i++;
  } while (!feof(file));
 fclose(file);
 //GHashTable * v = hash_rides;
  //return v;
}