#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/rides.h"
#include "../includes/parser.h"



// Parses a csv file using the provided function pointer to create objects from the data


void parse_csv(const char* filename, create_fn create_fn, void* catalog) {
  FILE* file = fopen(filename, "r");
  if (!file) {
    perror("Error opening file");
    return;
  }

  char* line = NULL;
  size_t len = 0;
  getline(&line, &len, file); // Ignores first line of input

  while (getline(&line, &len, file) != -1) {
    // Tokenized by ';'
    char* token;
    char* line_aux = line;
    char** tokens = malloc(5 * sizeof(char*));
    int num_colunas = 0;
    while ((token = strsep(&line_aux, ";\n"))) {
      tokens[num_colunas] = token;
      num_colunas++;
      if (num_colunas % 5 == 0) tokens = realloc(tokens, (num_colunas + 5) * sizeof(char*));
    }
  // Checks if entry is valid
  int is_valid = 0;
  for (int j = 0; j < num_colunas -2; j++) {
    if (strlen(tokens[j]) == 0 || tokens[j][0] == '<' || tokens [j][0] == '/' || tokens [j][0] == '?') {
      //printf ("Invalid: j = %d\n",j);
    is_valid = 1;
    }
  }

// If the entry is valid, call the function that creates the desired structure and inserts it into the hashtable
create_fn(tokens, catalog, is_valid);

    free(tokens);
  }

  free(line);

  fclose(file);
}

