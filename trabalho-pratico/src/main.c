#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <string.h>

#include <ctype.h>

#include <glib.h>

#include "../includes/queries_handler.h"

#include "../includes/interactmode.h"

#include "../includes/catalogs.h"


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
    create_catalogs (argv[1], argv[2]);
  }
  if (argc == 1) interactmode();
 return 0;
}
