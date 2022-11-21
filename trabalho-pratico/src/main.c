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

//como dar include a haeders fora do folder dos .c

//#include "parser.c"
//#include "queries.h"

/*
typedef struct
{
    int  id[9998];
    char name[30];
    char birth_date[9];
    char gender;
    char car_class[6];
    char license_plate[5];
    char city[10];
    char account_creation[9];
    char account_status[7];
}   Drivers;

typedef struct
{
    int  id[999998];
    char date[9];
    char driver[3];
    char user[20];
    char city[10];
    int  distance[1];
    int  score_user;
    char score_driver;
    double tip;
}   Rides;


typedef enum dequeOp {
    PUSH,
    PUSH_FRONT,
    POP,
    POP_FRONT,
    REVERSE,
    SIZE,
    IS_EMPTY
} DequeOp;


void printInt(void* i) {
    int* i_ = i;
    printf("%d", *i_);
}


DequeOp randomOp() {
    return rand() % 7;
}


int* randomInt() {
    int* data = malloc(sizeof(int));
    *data = rand() % 100;
    return data;
}


void testDeque(int nOps) {
    Deque* deque = create();
    push(deque, randomInt());
    push(deque, randomInt());
    push(deque, randomInt());

    printf("Initial deque: ");
    printDeque(deque, &printInt);
    printf("\n");

    for (int i = 0; i < nOps; i++) {
        DequeOp op = randomOp();
        int* data = NULL;

        switch (op) {
        case PUSH:
            data = randomInt();
            printf("PUSH(%d) = ", *data);
            push(deque, data);
            break;
        
        case PUSH_FRONT:
            data = randomInt();
            printf("PUSH_FRONT(%d) = ", *data);
            pushFront(deque, data);
            break;

        case POP:
            printf("POP = ");
            data = pop(deque);
            if (data) {
                free(data);
            }
            break;

        case POP_FRONT:
            printf("POP_FRONT = ");
            data = popFront(deque);
            if (data) {
                free(data);
            }
            break;

        case REVERSE:
            printf("REVERSE = ");
            reverse(deque);
            break;

        case SIZE:
            printf("SIZE: %d ", size(deque));
            break;

        case IS_EMPTY:
            printf("IS_EMPTY: %d ", isEmpty(deque));
            break;
        }

        printDeque(deque, &printInt);
        printf("\n");
    }

    int* data = pop(deque);
    while (data) {
        free(data);
        data = pop(deque);
    }
        deque->
    destroy(deque);
}


int main() {
    FILE *file; 

    file = fopen("test.txt", "r");
    if (file == NULL) {                                 // abrir ficheiro 
        printf("Unable to open the file");
        return 1;
    }

    User test[100];
    int read = 0;
    int records = 0;

    do {
        read = fscanf(file,"%20[^,],%30[^,],%c",
                    test[records].username,
                    test[records].name,
                    &test[records].gender);

        if (read == 3) records++;

        if (read != 3 && !feof(file)) {
            printf("File format incorrect\n");
            return 1;
        }

        if (ferror(file)) {
            printf("Error reading file\n");
            return 1;
        }
    }   while (!feof(file));

    fclose(file);

    printf("%d records read.\n", records);

    for (int i = 0; i < records; i++) {
        printf("%s %s %c\n",
                test[i].username,
                test[i].name,
                test[i].gender);
    printf("\n");

    }
    return 0;
}




char* get_id (char * line) {
    char *token = strtok (line,",");
            printf("ola");

    return token;
}

int main(){
  FILE *fp;
    char row[1024];
    char *token;
    char* to_hash;
    GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
    fp = fopen("users.csv","r");
    while (feof(fp) != true)
    {
        fgets(row, 1024, fp);
        printf("Row: %s", row);
        to_hash= strdup(row);
        g_hash_table_insert(hash, key, to_hash);

        token = strtok(row, ",");

        while(token != NULL)
        {
            printf("Token: %s\n", token);
            token = strtok(NULL, ",")    get_line (users,"SaCruz");
;
        }

    }
    

    return 0;

}


char* extract_id(char *line,char* limit) {
    char *token = strtok(line, limit);

    return token;
}

void tokenize(char* line, char* limit) {
    char* v[29][2];
    int i=0;
    char *pch = strtok (line,limit);
while (pch != NULL && i<9) {
if(i==0) {i++;}
else {
  pch = strtok (NULL, limit);
    //printf ("%s\n",pch);
    v[i][20] = pch;
    //printf ("%s;",v[i][20]);
i++;
    }
}
    FILE * output = fopen("output.txt","w+");
   // if(users) //para os users há 6 informações e para os drivers há 8
   Drivers* driver = malloc (sizeof(struct drivers));
   //driver.name[0] = v[1][20];
   //driv
    fprintf (output,"%s;" "%s;" "%s;" "%s;" "%s;" "%s",v[5][20],v[5][20],v[3][20],v[4][20],v[5][20],v[6][20]);
}

int get_line(FILE* file, char* id) { //lê a tabela e procura o valor 
    char* line = malloc(sizeof(char) * BUFSIZ);
    GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);

    char *copy;
    char *key;
    char *to_hash;

    while (fgets(line, BUFSIZ, file) != NULL) {
        copy = strdup(line);
       // if (file=="users.csv") {
            key = extract_id(copy,",");
        //}
        //else if (file=="drivers.csv") {
          //  key=extract_id(copy,";");
        to_hash = strdup(line);
        g_hash_table_insert(hash, key, to_hash);
    }

    printf("driver_info: %s\n", g_hash_table_lookup(hash, id));
   // if (file=="users.csv") {
        tokenize (g_hash_table_lookup(hash, id),",");
    //} else if  (file=="riders.csv") {
      //  tokenize (g_hash_table_lookup(hash, id),",");
    free(line);
    free(copy);
    free(to_hash);
    g_hash_table_destroy(hash);

    return 0;
}

int main(int argc, char** argv) {
    char* filename = argv[1];
    FILE* users_file = fopen(filename, "r");
    if (get_line(users_file, argv[2])) {
        return 0;
}
    return 1;
}

int query_1 (char* id) {
    int flag = 0;
    FILE* input = fopen("input.txt","r");
    int i=0;
    char* query_number [20];
    char* string [20];
    char* id = malloc(sizeof(char) * BUFSIZ);
    char* line = malloc(sizeof(char) * BUFSIZ);
    while (fgets(line, BUFSIZ, input));// != NULL) //{
       char *pch = strtok (line," ");
                query_number[1] = pch;
                printf( "%s\n", query_number[1]);
                pch = strtok(NULL," ");
                string[1]=pch;
                printf( "%s\n", string[1] );
                if(query_number==1) {
                    for (int j=0;j<6;j++) {
                        if (isdigit(string[j])) {flag=1;//é um id de uma pessoa
                        }
                        if (flag==1) {
                            get_line("users.csv",string[0]);
                        }
                    }
                }
}
//i++;

while (pch != NULL) {
    printf( "%s;", pch );
    pch = strtok (NULL, " ");
    //printf ("%s\n",pch);
    //printf ("%s;",v[i][20]);
       }



void query_1 (char * string) {
    int i;
    for(i=0;i<strlen(string);i++) {
        if isalpha(string[i]) {
            FILE* users = fopen("users.csv","r");
            get_line (users,string);
    } else {
            FILE* drivers = fopen("drivers.csv","r");
                get_line (drivers,string);
            }   
    }
}
*/

int main (int argc, char** argv) {
    printf ("entrou na main\n");
   if (argc == 3) {
      parser_input(argv[1], argv[2]);
      printf ("entrou no parser\n");
   } 

    printf ("acabou\n");
}

    //query2 (hash_drivers);


  //struct drivers *d = g_hash_table_lookup (hash_drivers,"000000000003");
  //printf ("AVAL:%f\n", d->avaliacao_media_driver); ESTÁ A FUNCIONAR, OU SEJA, OS VALORES DA AVALIACAO ESTAO NA HASHTABLE 
    //printf ("%s\n",u->name);
    //printf ("Total gasto:%f\n", calcula_total_gasto ("basic",10,1.00));
    //printf ("%f\n",u->total_gasto);    
    //printf ("%d\n",u->numero_viagens_user);