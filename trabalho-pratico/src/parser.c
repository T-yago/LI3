#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>/*
int main(int argc, char *argv[]) {

   File *users = fopen("users.csv","r");
    char flag;
    int ipint;
    char ipchar;
    float ipfloat;
    int exitStatus = fscanf(input.txt, "%c", &flag);

    while (exitStatus != EOF)
    {

        if (flag == I)
        {
            fscanf(input.txt, "%i", &ipint);
            fprintf(ints.txt, ipint);
        }
        if (flag == C)
        {
            fscanf(input.txt, "%c", &ipchar);
            fprintf(chars.txt, ipchar);
        }
        if (flag == F)
        {
            fscanf(input.txt, "%f", &ipfloat);
            fprintf(floats.txt, ipfloat);
        }
    }
    fclose(input.txt);
    fclose(ints.txt);
} */ 


void parser_queries () {
    FILE *input;
    int numb_query;
    char* string;
    input = fopen("input.txt","r");
    while (fgets(line,BUFSIZ,input)) {
        numb_query = strtok(line," ");
        string = line;
    }
    if (numb_query==1) {
        query_1(string);
    }
    else {
        printf ("não fizemos");
    }
}

/*
int main () {
    FILE *input;
    char* token;
    input = fopen("input.txt","r");
    int query_number;
    char* string = malloc(sizeof(char) * BUFSIZ);
    char* id = malloc(sizeof(char) * BUFSIZ);
    char* line = malloc(sizeof(char) * BUFSIZ);
    while (fgets(line, BUFSIZ, input)){
       token = strtok (line," ");
       input = line;
       }
                if(query_number=1) {
                    char* query1 = malloc(sizeof(struct Query1));
                                    
                }
    return 0;
}
*/
/*
while (pch != NULL) {
    printf( "%s;", pch );
    pch = strtok (NULL, " ");
    //printf ("%s\n",pch);
    //printf ("%s;",v[i][20]);
       }*/


