#include <stdio.h>

#include <stdbool.h>

#include <ncurses.h>

#include <stdlib.h>

#include <string.h>

#include "../includes/compare_outputs.h"

#define SIZE_ARRAY 1024 


//O primeiro é o caminho para o ficheiro com os inputs, no segundo argumento o caminho para a pasta com os valores de referencia e no 3 argumento o caminho para a pasta Resultados
void compare_outputs_and_print_times(char* path_to_input_file, char* path_to_reference_folder, char* path_to_results_folder, double* times_query){

    uint identical_lines_query[9] = {0};
    uint total_lines_results[9] = {0}; 
    uint total_lines_reference[9] = {0};
    uint identical_files_query[9] = {0};
    uint total_files_query[9] = {0};
    uint numb_query = 0;
    uint n_command = 0; //number of instruction that is equal to the command number
    char input_line[SIZE_ARRAY];
    FILE* input_file = fopen(path_to_input_file, "r");

    if (input_file == NULL) {
        printf("\033[0;31mError: Could not open input file %s.\n", path_to_input_file);
    }
    else{
        char c;
        while ((c = fgetc(input_file)) != EOF) {
            if (c == '\n') {
                n_command++;
            }
        }
        fclose(input_file);
    }
    FILE* input_file2 = fopen(path_to_input_file, "r");

    for (uint i = 1; i <= n_command; i++) {
        char reference_path[SIZE_ARRAY];
        sprintf(reference_path, "%scommand%d_output.txt", path_to_reference_folder, i);
        char results_path[SIZE_ARRAY];
        sprintf(results_path, "%scommand%d_output.txt", path_to_results_folder, i);

        FILE* reference_file = fopen(reference_path, "r");
        FILE* results_file = fopen(results_path, "r");


        if (reference_file == NULL || results_file == NULL) {
            printf("\033[0;31mError: Could not open files %s or %s.\n", reference_path, results_path);
            continue;
        }

        if (fgets(input_line, SIZE_ARRAY, input_file2) != NULL){
            numb_query = input_line[0] - '0' - 1;
            total_files_query[numb_query]++;
        }

        char reference_line[SIZE_ARRAY];
        char results_line[SIZE_ARRAY];
        total_lines_reference[numb_query] = 0;
        total_lines_results[numb_query] = 0;
        identical_lines_query[numb_query] = 0;


        while (fgets(reference_line, SIZE_ARRAY, reference_file) != NULL) {
            total_lines_reference[numb_query]++;
            if (fgets(results_line, SIZE_ARRAY, results_file) != NULL) {
                total_lines_results[numb_query]++;
                if (strcmp(reference_line, results_line) == 0) {
                    identical_lines_query[numb_query]++;
                }
                else{
                    printf("\033[0;31mError in Command%d_output.txt, line %d:\n", i, total_lines_results[numb_query]);
                    printf("\033[0;33m %s\n", results_line);
                    printf("\033[0;32m %s", reference_line);
                }
            }
        }

        if (total_lines_reference[numb_query] == total_lines_results[numb_query] && total_lines_results[numb_query] == identical_lines_query[numb_query]) identical_files_query[numb_query]++;
        
        fclose(reference_file);
        fclose(results_file);
    }
    	
    fclose(input_file2);

    printf("\n");
    for (uint i = 0; i < 9; i++) {
        double identical_file_percentage = ((double) identical_files_query[i] / total_files_query[i]) * 100;
        printf("\033[0;34mQuery%d:\033[0;37m %.2f%%, %.8fs\n", i+1, identical_file_percentage, times_query[i]);
    } 
}


