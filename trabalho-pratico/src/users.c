#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>

#include <glib.h>

struct users {
  char * username;
  char * name;
  char * gender;
  char * birth_date;
  char * account_creation;
  char * pay_method;
  char * account_status;
};

void catalog(char * id) {
  char * line = NULL;
  ssize_t read;
  size_t len;
  GHashTable * hash = g_hash_table_new(g_str_hash, g_str_equal);
  FILE * file = fopen("users.csv", "r");
  if (file == NULL) {
    printf("Error opening file.\n");
  }
  //struct users* *users = malloc (100100 * sizeof (struct users));
  int read_h = 0;
  int records = 0;
  int i = 0;
  do {
    while ((read = getline( & line, & len, file)) != -1) {
      struct users * u = malloc(sizeof(struct users));
      char * token;
      int i = 0;
      while ((token = strsep( & line, ",\n"))) {
        switch (i) {
        case 0:
          u -> username = strdup(token);
          break;
        case 1:
          u -> name = strdup(token);
          break;
        case 2:
          u -> gender = strdup(token);
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
          u -> account_status = strdup(token);
          break;
        }
        i++;
      }
      //char *line_copy = strdup(line);
      g_hash_table_insert(hash, u -> username, u);
    }
    if (read_h == 7) records++;
    if (read_h != 7 && !feof(file)) {
      printf("File format incorrect.\n");
    }
    i++;
  } while (!feof(file));
  printf("%d", g_hash_table_size(hash));
  struct users * u = g_hash_table_lookup(hash, id);
  printf("%s", u -> birth_date);

  fclose(file);
  g_hash_table_destroy(hash);

  printf("\n%d records read.\n\n", records);
  FILE * output = fopen("output.txt", "w+");
  fprintf(output, "%s;"
    "%s;"
    "%s;"
    "%s;"
    "%s;"
    "%s"
    "%s", u -> username, u -> name, u -> gender, u -> birth_date, u -> account_creation, u -> pay_method, u -> account_status);

  //free (u);
}

/*
void get_age (char * v) {

}

void calcular_idade (int ano, int mes, int dia) {
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
}
*/
void get_data(struct users ** username, char * id) {}

int main() {
  catalog("MiTeixeira");
  printf("Endereço:%p\n", catalog);

  //struct users** p = catalog;
  //printf("%p",p);
  return 0;
}