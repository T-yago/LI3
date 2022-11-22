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

#include "../includes/users.h"

#include "../includes/drivers.h"

#include "../includes/rides.h"

#include "../includes/parser.h"

#include "../includes/query1.h"


int main(int argc, char ** argv) {
  if (argc == 3) {
    parser_input(argv[1], argv[2]);
  }
 return 0;
}
