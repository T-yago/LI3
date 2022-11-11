#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>

#include <glib.h>

struct rides {
  char * id;
  char * date;
  char * driver;
  char * user;
  char * city;
  char * distance;
  char * score_user;
  char * score_driver;
  char * tip;
  char * comment;
};

char* rides_catalog(char* id) {
  char * line = NULL;
  ssize_t read;
  size_t len;
  GHashTable * hash = g_hash_table_new(g_str_hash, g_str_equal);
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
      g_hash_table_insert(hash, r -> id, r);
    }
    if (read == 7) printf("%d",i);
    if (read != 7 && !feof(file)) {
      printf("File format incorrect.\n");
    }
    i++;
  } while (!feof(file));
  printf("Tamanho da hash table: %d\n", g_hash_table_size(hash));
  struct rides * user_pretendido = g_hash_table_lookup(hash, id);
  printf("%s", user_pretendido->distance);

  fclose(file);
  g_hash_table_destroy(hash);

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

char* v = user_pretendido->driver;
  free  (user_pretendido);
return v;
}

int main() {
  rides_catalog("1000000");

  //struct drivers** p = catalog;
  //printf("%p",p);
  return 0;
}

