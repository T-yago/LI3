#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <string.h>

#include <ctype.h>

#include <glib.h>

#include "../includes/drivers.h"

struct drivers {
  char * id;
  char * name;
  char * birth_day;
  char gender;
  char*  car_class;
  char * license_plate;
  unsigned short int date;
  char * city;
  char * account_creation;
  bool account_status;
  double total_auferido;
  int avaliacao_total_driver; // short int nao chegou 
  int numero_viagens_driver;
  double avaliacao_media_driver;
};


GHashTable * drivers_catalog () {
  char * line = NULL;
  ssize_t read;
  size_t len;

  GHashTable * hash_drivers = g_hash_table_new_full(g_str_hash, g_str_equal,g_free,g_free); // FAZER DESTROY NO FIM 
  FILE * file = fopen("../../Dataset/drivers.csv", "r");
  if (file == NULL) {
    printf("Error opening file.\n");
  }
  //int records = 0;
  int i = 0;
  do {
    while ((read = getline( & line, & len, file)) != -1) {
      struct drivers * d = malloc(sizeof(struct drivers));
      char * token;
      int i = 0;
      while ((token = strsep( & line, ";\n"))) {
        switch (i) {
        case 0:
          d -> id = strdup(token);
          break;
        case 1:
          d -> name = strdup(token);
          break;  
        case 2:
          d -> birth_day = strdup(token);
          break;
        case 3:
          d -> gender = *(token);
          break;
        case 4:
          d -> car_class = strdup(token);
          break;
        case 5:
          d -> license_plate = strdup(token);
          break;
        case 6:
          d -> city = strdup(token);
          break;
        case 7:
          d -> account_creation = strdup(token);
          break;
        case 8:
        if (strcmp(token,"active")) {
          d->account_status = true;
        }
        else {
          d->account_status = false;
        }
        }
        i++;
      }
      //char *line_copy = strdup(line);
      g_hash_table_insert(hash_drivers, d -> id, d);
    }
    i++;
  } while (!feof(file));
  //printf("Tamanho da hash table: %d\n", g_hash_table_size(hash_drivers));
  //struct drivers * user_pretendido = g_hash_table_lookup(hash_drivers, id);
  //printf("%s", user_pretendido->license_plate);

  fclose(file);
//  g_hash_table_destroy(hash);
/*
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
    "%s", user_pretendido-> id, user_pretendido-> name, user_pretendido-> birth_day, user_pretendido-> gender, user_pretendido-> car_class, user_pretendido-> license_plate, user_pretendido-> city, user_pretendido-> account_creation, user_pretendido->account_status);
*/
GHashTable * v = hash_drivers;
return v;
}

//int main() {
 // drivers_catalog("9246");

  //struct drivers** p = catalog;
  //printf("%p",p);
 // return 0;
//}
