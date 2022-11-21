#include <stdio.h>

#include <stdbool.h>

#include <stdlib.h>

#include <string.h>

#include <glib.h>

#include "../includes/parser.h"

#include "../includes/users.h"

#include "../includes/drivers.h"

#include "../includes/query1.h"

#include "../includes/query2.h"

#include "../includes/rides.h"

#include "../includes/query3.h"

void parser_input(char * pathfiles, char * input) {
  printf("entrou na função do parser\n");
  GHashTable * hash_users = users_catalog(pathfiles);
  initHash_users(hash_users);
  printf("fez a hash dos users\n");
  GHashTable * hash_drivers = drivers_catalog(pathfiles);
  initHash_drivers(hash_drivers);
  printf("fez a hash dos drivers\n");
  rides_catalog(hash_users, hash_drivers, pathfiles);
  printf("fez a hash dos rides\n");
  FILE * file;
  char * aux;
  char * info;
  int numb_query, n = 1;
  ssize_t read;
  size_t len;
  char * line = NULL;
  file = fopen(input, "r");
  if (file == NULL) {
    printf("Error opening input file.\n");
  }
  do {
    while ((read = getline( & line, & len, file)) != -1) {
      aux = strsep( & line, " ");
      numb_query = atoi(aux);
      info = strsep( & line, " \n");
      switch (numb_query) {
      case 1:
        query1_main(info, hash_users, hash_drivers, n);
        break;
      case 2:
        query2(hash_drivers, info, n);
        break;
      case 3:
        query3(hash_users, info, n);
        break;
      case 4:
        break;
      case 5:
        break;
      case 6:
        break;
      case 7:
        break;
      case 8:
        break;
      case 9:
        break;
      }
      n++;
    }
  } while (!feof(file));
  fclose(file);
  //   free (line);
  //g_hash_table_destroy (hash_users);
  // g_hash_table_destroy (hash_drivers);
}