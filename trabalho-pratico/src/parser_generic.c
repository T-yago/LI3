#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/rides.h"
#include "../includes/parser_generic.h"



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
    char** tokens = malloc(sizeof(char*));
    int i = 0;
    while ((token = strsep(&line_aux, ";\n"))) {
      tokens[i++] = token;
      tokens = realloc(tokens, (i + 1) * sizeof(char*));
    }
  // Checks if entry is valid
  int is_valid = 1;
  for (int j = 0; j < i; j++) {
    if (strlen(tokens[j]) == 0) {
    is_valid = 0;
    }
  }

// If the entry is valid, call the function that creates the desired structure and inserts it into the hashtable
 if (is_valid == 0) create_fn(tokens, catalog);

    free(tokens);
  }

  free(line);

  fclose(file);
}

