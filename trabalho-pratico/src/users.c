#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <glib.h>

struct users
{
    char* username;
    char* name;
    char* gender;
    char* birth_date;
    char* account_creation;
    char* pay_method;
    char* account_status;
};   


void catalog () {
    char* line = NULL;
  ssize_t read;
    size_t len;
    GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
    FILE *file = fopen ("users.csv","r");
    if (file == NULL) {
        printf ("Error opening file.\n");
    }
  //struct users* *users = malloc (100100 * sizeof (struct users));
  int read_h = 0;
  int records = 0;  
  int i=0;
  do { 
      /*        char* username = malloc (sizeof (char) * 100);
              char* name = malloc (sizeof (char) * 100);
              char* gender = malloc (sizeof (char) * 100);
              char* birth_date = malloc (sizeof (char) * 100);
              char* account_creation = malloc (sizeof (char) * 100);
              char* pay_method = malloc (sizeof (char) * 100);
              char* account_status = malloc (sizeof (char) * 100);
        */    
  //fscanf (file,
    //        "%20[^,],%40[^,],%25[^,],%25[^,],%25[^,],%25[^,],%25[^\n]",
      //     read = readline (strsep (file, ",")
      while ((read = getline(&line, &len, file)) != -1) {
        struct users * u = malloc (sizeof(struct users));
          char *token;
          int i=0;
          while ((token=strsep(&line,",\n"))) {
          switch (i) {
            case 0:
             u->username=strdup (token); 
             break;
            case 1:
             u->name=strdup (token); 
             break;            
          }  
       //   printf ("%s",u->username);
          i++;
          }
          //char *line_copy = strdup(line);
        g_hash_table_insert(hash, u->username, u);

      }
/*
            username,
            name,
            gender,
            birth_date,
            account_creation,
            pay_method,
            account_status;
            u->username = strdup (username);
            u->name = strdup(name);
            u->gender=strdup(gender);
            u->birth_date=strdup(birth_date);
            u->account_creation = strdup(account_creation);
            char* id = u->username;
   */
        // printf ("%s",u->name);
        //if (!strcmp(id,"MiTeixeira\n")) printf ("ola");

  if (read_h == 7) records++;
  if (read_h != 7 && !feof(file))
    {
     // printf("File format incorrect.\n");
    }
    i++;
  } while (!feof(file));
  printf ("%d",g_hash_table_size(hash)); 
 struct users* u = g_hash_table_lookup(hash, "MiTeixeira");
  printf ("%s",u->username);

  fclose(file);
  g_hash_table_destroy(hash);


  printf("\n%d records read.\n\n", records);

//for (int i=0;i<100001;i++) {
  //  printf ("%s\n %s\n %s\n %s\n %s\n %s\n %s\n" ,
    //        users[i].username,users[i].name,users[i].gender, users[i].birth_date, users[i].account_creation, users[i].pay_method, users[i].account_status);
//} 
    FILE * output = fopen("output.txt","w+");

    //fprintf (output,"%s;" "%s;" "%s;" "%s;" "%s;" "%s",users[5]->username,users[5]->name,users[5]->gender,users[5]->birth_date,users[5]->account_creation,users[5]->pay_method,users[5]->account_status);

 //free (u);
}

void get_data (struct users **username, char* id) {

   // for (i=0; i < 100001; i++) {
     //   if (strcmp ((*username->username,id))) {
       //     printf("%c",*username[i]->username);
        }

int main () {
    catalog();
    printf ("Endereço:%p\n",catalog);
    
   
    //struct users** p = catalog;
    //printf("%p",p);
    return 0;
}