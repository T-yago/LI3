//usar static functions para ocultar funções
//fazer a declaração da main na stack
//No .h colocar apenas declaraçoes de structs e de funções
//gcc main.c -Wall -o main `pkg-config --cflags --libs glib-2.0`

#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <string.h>

#include <ctype.h>

#include <glib.h>

#include "../includes/queries_handler.h"

#include "../includes/interactmode.h"



int main(int argc, char ** argv) {
  if (argc == 3) {
    queries_handler(argv[1], argv[2]);
  }
  if (argc == 1) interactmode();
 return 0;
}
