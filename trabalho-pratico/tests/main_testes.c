#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <string.h>

#include <ctype.h>

#include "../includes/compare_outputs.h"



int main(int argc, char ** argv) {
  if (argc == 4) {
    compare_outputs(argv[1], argv[2], argv[3]);
  }
 return 0;
}
