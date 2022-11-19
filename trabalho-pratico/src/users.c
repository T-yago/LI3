#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <glib.h>
#include "../includes/users.h"

struct users {
  char * username;
  char * name;
  char gender;
  unsigned short int date;
  int distance;
  char * birth_date;
  char * account_creation;
  char * pay_method;
  bool account_status;
  double total_gasto;
  short int numero_viagens_user;
  short int avaliacao_total_user;
  double avaliacao_media_user;
};
//campo gasto -> incrementar

GHashTable * users_catalog() {
  char * line = NULL;
  ssize_t read;
  size_t len;
  GHashTable * hash_users = g_hash_table_new_full(g_str_hash, g_str_equal,g_free,g_free);
  FILE * file = fopen("../../Dataset/users.csv", "r");
  if (file == NULL) {
    printf("Error opening file.\n");
  }
 // int records = 0;
  int i = 0;
  do {
    while ((read = getline( & line, & len, file)) != -1) {
      struct users * u = malloc(sizeof(struct users));
      char * token;
      int i = 0;
      while ((token = strsep( & line, ";\n"))) {
        switch (i) {
        case 0:
          u -> username = strdup(token);
          break;
        case 1:
          u -> name = strdup(token);
          break;
        case 2:
          u -> gender = *(token);
          break;
        case 3:
          u -> birth_date = strdup(token);
          break;
        case 4:
          u -> account_creation = strdup(token);
          break;
        case 5:
          u -> pay_method = strdup(token);
          break;
        case 6:
        if (strcmp(token,"active")) {
          u->account_status = true;
        }
        else {
          u->account_status = false;
        }
          //u -> account_status = strdup(token);
          //break;
        }
        i++;
      }
      //char *line_copy = strdup(line);
      g_hash_table_insert(hash_users, u -> username, u);
    }
    i++;
  } while (!feof(file));
  
  //printf("%d", g_hash_table_size(hash_users));
  //struct users * user_pretendido = g_hash_table_lookup(hash_users, id);
  //printf("%s", user_pretendido->name);
  fclose(file);
 // g_hash_table_destroy(hash);

  /*printf("\n%d records read.\n\n", records);
  FILE * output = fopen("output.txt", "w+");
  fprintf(output, "%s;"
    "%s;"
    "%s;"
    "%s;"
    "%s;"
    "%s"
    "%s", user_pretendido-> username, user_pretendido-> name, user_pretendido-> gender, user_pretendido-> birth_date, user_pretendido-> account_creation, user_pretendido-> pay_method, user_pretendido-> account_status);
*/
GHashTable * v =  hash_users;
return v;
}

/*
void get_age (char * v) {
printf ("%s",*v);
age ()
}

void age(int present_date, int present_month, int present_year, int birth_date, int birth_month, int birth_year) {//09/10/2022
int month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
   if (birth_date > present_date) {
      present_date = present_date + month[birth_month - 1];
      present_month = present_month - 1;
   }
   if (birth_month > present_month) {
      present_year = present_year - 1;
      present_month = present_month + 12;
   }
   int final_date = present_date - birth_date;
   int final_month = present_month - birth_month;
   int final_year = present_year - birth_year;
   printf("Present Age Years: %d Months: %d Days: %d", final_year, final_month, final_date);
}
*/

//int main() {
  //users_catalog("PeBaptista3");

  //struct users** p = catalog;
  //printf("%p",p);
  //return 0;
//}