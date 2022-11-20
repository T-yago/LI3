#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../includes/parser.h"
#include "../includes/users.h"
#include "../includes/drivers.h"
#include "../includes/query1.h"
#include "../includes/rides.h"

FunctionPointer *table[1] = {
    query1_main
};

void parser_input(char* csv_path, char* input) {
    char* inputfile = strdup(input);
    printf("%s\n", inputfile);
    GHashTable * hash_users = users_catalog(csv_path);
    GHashTable * hash_drivers = drivers_catalog(csv_path);
    rides_catalog (hash_users, hash_drivers); 
    FILE* file;
    char* aux;
    char* info;
    int numb_query, n = 1;
    ssize_t read;
    size_t len;
    char* line = NULL;
    file = fopen(inputfile, "r");
    while((read = getline(&line, &len, file)) != -1) {
        aux = strsep(&line, " ");
        numb_query = atoi(aux);
        info = strsep(&line, " \n");
        table[numb_query - 1](info, hash_users, hash_drivers, n);
        n++;
    }
    fclose(file);
    free(inputfile);
}

char* substr(const char *str, int m, int n) {
    int len = n - m;
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
    for (int i = m; i < n && (*(str + i) != '\0'); i++) {
        *dest = *(str + i);
        dest++;
    }
    *dest = '\0';

    return dest - len;
}

char* fixstring(char* info) {
    int len = strlen(info);
    char* id = substr(info, 0, len - 1);

    return id;
}

