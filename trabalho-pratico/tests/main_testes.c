#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <string.h>

#include <ctype.h>

#include <time.h>

#include "../includes/compare_outputs.h"

#include "../includes/queries_handler_testes.h"


//1ºarg Dataset, 2ºarg input, 3ºarg Outputs de referencia
int main(int argc, char ** argv) {
  if (argc == 4) {
    clock_t start, end;
    double cpu_time_used;
    double times_query[9] = {0};
    start = clock();
  
    queries_handler_testes(argv[1], argv[2], times_query);
  
    compare_outputs_and_print_times(argv[2], argv[3], "Resultados/", times_query);
  
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; 
    printf("\nTotal time: %f", cpu_time_used);
    printf("\033[0;32m\nDone✅\033[0m\n");
  }
  return 0;
}
