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

    // Chama a função que cria a estrutura desejada e a insere na hashtable
    create_fn(tokens, catalog);

    free(tokens);
  }

  free(line);

  fclose(file);
}

