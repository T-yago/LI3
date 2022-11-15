#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>

#include <glib.h>

#include "query1.c"
#include "query2.c"

struct rides {
  char * id;
  char * date;
  char * driver;
  char * user;
  char * city;
  short int distance;
  short int score_user;
  short int score_driver;
  double tip;
  char * comment;
};

/*
char* rides_catalog(char* id) {
  char * line = NULL;
  ssize_t read;
  size_t len;
  GHashTable * hash_rides = g_hash_table_new(g_str_hash, g_str_equal);
  FILE * file = fopen("rides.csv", "r");
  if (file == NULL) {
    printf("Error opening file.\n");
  }
  int records = 0;
  int i = 0;
  do {
    while ((read = getline( & line, & len, file)) != -1) {
      struct rides * r = malloc(sizeof(struct rides));
      char * token;
      int i = 0;
      while ((token = strsep( & line, ",\n"))) {
        switch (i) {
        case 0:
          r -> id = strdup(token);
          break;
        case 1:
          r -> date = strdup(token);
          break;  
        case 2:
          r -> driver = strdup(token);
          break;
        case 3:
          r -> user = strdup(token);
          break;
        case 4:
          r -> city = strdup(token);
          break;
        case 5:
          r -> distance = strdup(token);
          break;
        case 6:
          r -> score_user = strdup(token);
          break;
        case 7:
          r -> score_driver = strdup(token);
          break;
        case 8:
          r -> tip = strdup(token);
          break;
        case 9:
          r -> comment = strdup(token);
          break;
        }
      i++;
      }
      //char *line_copy = strdup(line);
      g_hash_table_insert(hash_rides, r -> id, r);
    }
    if (read == 7) printf("%d",i);
    if (read != 7 && !feof(file)) {
      printf("File format incorrect.\n");
    }
    i++;
  } while (!feof(file));
  printf("Tamanho da hash table: %d\n", g_hash_table_size(hash_rides));
  struct rides * user_pretendido = g_hash_table_lookup(hash_rides, id);
  printf("%s", user_pretendido->distance);

  fclose(file);
 // g_hash_table_destroy(hash);

  printf("\n%d records read.\n\n", records);
  FILE * output = fopen("output.txt", "w+");
  fprintf(output, "%s;"
    "%s;"
    "%s;"
    "%s;"
    "%s;"
    "%s;"
    "%s;"
    "%s;"
    "%s", user_pretendido-> id, user_pretendido-> date, user_pretendido-> driver, user_pretendido-> user, user_pretendido-> score_user, user_pretendido-> distance, user_pretendido-> score_user, user_pretendido-> score_driver, user_pretendido->tip);

char* v = hash_rides;
return v;
}

*/

void rides_catalog(GHashTable * users_hash, GHashTable * drivers_hash) {
  char * line = NULL;
  ssize_t read;
  size_t len;
 // GHashTable * hash_rides = g_hash_table_new(g_str_hash, g_str_equal);
  FILE * file = fopen("rides.csv", "r");
  if (file == NULL) {
    printf("Error opening file.\n");
  }
  //int records = 0;
  int i = 0;
        int j= 0;

  do {
    while ((read = getline( & line, & len, file)) != -1) {
      struct rides * ride = malloc(sizeof(struct rides));
      char * token;
      int i = 0;
      while ((token = strsep( & line, ";\n"))) {
        switch (i) {
        case 0:
          ride -> id = strdup(token);
          break;
        case 1:
          ride -> date = strdup(token);
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

      }      //escrever aqui o que colocar a cada iteracao de user
      if (j== 0) {;} else {

      // estou a fazer malloc de algo que já tinha sido previamente alocado na mem
         struct users * u = malloc(sizeof(struct users));
         struct drivers * d = malloc(sizeof(struct drivers));
         u = g_hash_table_lookup (users_hash,ride->user);
         d = g_hash_table_lookup (drivers_hash,ride->driver);
        
        u->total_gasto += calcula_total_gasto(d->car_class,ride->distance,ride->tip);
        u->avaliacao_total_user += ride->score_user;
        u->numero_viagens_user++;

        d->total_auferido += calcula_total_gasto (d->car_class,ride->distance,ride->tip);
        d->avaliacao_total_driver += ride->score_driver;
        d->numero_viagens_driver++;
        //printf ("%d\n",u->total_gasto);
      }     j++;

      //char *line_copy = strdup(line);
      //g_hash_table_insert(hash_rides, ride -> id, ride);
    }
    i++;
  } while (!feof(file));

 // printf("Tamanho da hash table: %d\n", g_hash_table_size(hash_rides));
 // struct rides * user_pretendido = g_hash_table_lookup(hash_rides, id);
 // printf("%s", user_pretendido->distance);

  fclose(file);
 // g_hash_table_destroy(hash);

  //printf("\n%d records read.\n\n", records);
  //FILE * output = fopen("output.txt", "w+");
  //fprintf(output, "%s;"
   // "%s;"
   //"%s;"
   // "%s;"
   // "%s;"
   // "%s;"
   // "%s;"
   // "%s;"
   // "%s", user_pretendido-> id, user_pretendido-> date, user_pretendido-> driver, user_pretendido-> user, user_pretendido-> score_user, user_pretendido-> distance, user_pretendido-> score_user, user_pretendido-> score_driver, user_pretendido->tip);

//char* v = hash_rides;
//return v;
}