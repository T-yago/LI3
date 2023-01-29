#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <string.h>

#include <ctype.h>

#include <glib.h>

#include "../includes/queries_handler.h"


/**
 * @brief Função principal que comanda o programa-principal
 * 
 * @param argc número de argumentos do programa
 * @param argv argumentos em string 
 * @return 0 se funcionar corretamente 
 */
//1ºarg = Dataset, 2ºarg = input
int main(int argc, char ** argv) {
  if (argc == 3) {
    queries_handler(argv[1], argv[2]);
  }
 return 0;
}
