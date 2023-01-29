#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/rides.h"
#include "../includes/parser.h"



// Parses a csv file using the provided function pointer to create objects from the data

/**
 * @brief Realiza o parsing de um ficheiro ".csv" e chama uma para cada linha uma função "create_fn" que cria uma estrutura
 * 
 * @param filename Ficheiro a fazer parsing
 * @param create_fn Função que cria uma estrutura para cada linha parsed
 * @param catalog Catálogo onde se adiciona a estrutura criada
 */
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
    create_fn(tokens, catalog);

    free(tokens);
  }

  free(line);

  fclose(file);
}

