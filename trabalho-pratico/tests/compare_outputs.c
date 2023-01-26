#include <stdio.h>

#include <stdbool.h>

#include <dirent.h>

#include <ncurses.h>

#include <stdlib.h>

#include <string.h>

#include "../includes/compare_outputs.h"



/*Struct dirent da libraria dirent.h :

struct dirent {
    ino_t          d_ino;         
    off_t          d_off;         
    unsigned short d_reclen;      
    unsigned char  d_type;       
                                 
    char           d_name[256];  //Nome do ficheiro
};

*/



//Funcoes auxiliares
int fillter(const struct dirent *entry) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        return 0;
    else
        return 1;
}

int compare_filenames(const struct dirent **a, const struct dirent **b) {
    int num1, num2; 

    sscanf((*a)->d_name, "command%d_output.txt", &num1);  
    sscanf((*b)->d_name, "command%d_output.txt", &num2);
    return num1 - num2;
}


struct dirent** organize_dir(char* path_to_folder){
    struct dirent ** files;
    int n;

    n = scandir(path_to_folder, &files, fillter, compare_filenames);
    
    if (n < 0) printf("\033[0;31mError: Could not open folders.\033[0;31m\n");

    return files;
}


//O primeiro é o caminho para o ficheiro com os inputs, no segundo argumento o caminho para a pasta com os valores de referencia e no 3 argumento o caminho para a pasta Resultados
void compare_outputs(char* path_to_input_file, char* path_to_reference_folder, char* path_to_results_folder){

    struct dirent** reference_files_array = organize_dir(path_to_reference_folder);

    uint identical_lines_query[9] = {0};
    uint total_lines_query[9] = {0}; 
    uint total_lines[9] = {0};
    uint identical_files_query[9] = {0};
    uint total_files_query[9] = {0};
    uint numb_query = 0;
    uint n_instruction = 1; //numero da instrucao

    char input_line[1024];
    FILE* input_file = fopen(path_to_input_file, "r");

    if (input_file == NULL) {
        printf("\033[0;31mError: Could not open input file %s.\033[0;31m\n", path_to_input_file);
    }

    for (uint i = 0; reference_files_array[i]; i++) {

        if (fgets(input_line, 1024, input_file) != NULL){
            numb_query = input_line[0] - '0' - 1;

            char reference_path[1024];
            sprintf(reference_path, "%s%s", path_to_reference_folder, reference_files_array[i]->d_name);
            char results_path[1024];
            sprintf(results_path, "%s%s", path_to_results_folder, reference_files_array[i]->d_name);

            FILE* reference_file = fopen(reference_path, "r");
            FILE* results_file = fopen(results_path, "r");

            if (reference_file == NULL || results_file == NULL) {
                printf("\033[0;31mError: Could not open files %s or %s.\033[0;31m\n", reference_path, results_path);
                continue;
            }

            total_files_query[numb_query]++;

            char reference_line[1024];
            char results_line[1024];

            while (fgets(reference_line, 1024, reference_file) != NULL) {
                total_lines[numb_query]++;
                if (fgets(results_line, 1024, results_file) != NULL) {
                    total_lines_query[numb_query]++;
                    if (strcmp(reference_line, results_line) == 0) {
                        identical_lines_query[numb_query]++;
                    }
                }
            }
            if (total_lines[numb_query] == total_lines_query[numb_query] && total_lines_query[numb_query] == identical_lines_query[numb_query]) identical_files_query[numb_query]++;
            else{
                printf("\033[0;31mError: Error in Command%d_output.\033[0;31m\n", n_instruction);
            }
        }
        if(feof(input_file)) break;
        n_instruction++;
    }


    for (uint i = 0; i < 9; i++) {
        double identical_line_percentage = ((double) identical_lines_query[i] / total_lines_query[i]) * 100;
        double identical_file_percentage = ((double) identical_files_query[i] / total_files_query[i]) * 100;
        printf("\033[0;36mPercentagem de linhas identicas Query%d : %.2f%%\nPercentagem de ficheiros identicos Query%d : %.2f%%\033[0;36m\n", i+1, identical_line_percentage, i+1, identical_file_percentage);
    }

    printf("\033[0;32mTests_1 done.\033[0m\n");

    //free
    uint i = 0;
    while (reference_files_array[i] != NULL) {
        free(reference_files_array[i]);
        i++;
    }
    free(reference_files_array);    
}


