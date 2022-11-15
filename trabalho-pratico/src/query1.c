#define DATE "09/10/2022"

double calcula_total_gasto (char* car_class, short int distance, double tip ) {
  double total = 0.000;  
    if (!(strcmp(car_class,"basic"))) {
        total = total + 3.250 + (0.620 * distance) + tip;
    }
    else if (!(strcmp(car_class,"green"))) {
        total = total + 4.000 + (0.790 * distance) + tip;
    }
    else {
        total = total + 5.200 + (0.94 * distance) + tip;
    }
    return total;
}
/*
double calcula_avaliacao_media (GHashTable * hash, char* id) {
    int avaliacao_media;
    struct users * u = malloc(sizeof(struct users));
    u = g_hash_table_lookup (hash,id);
    avaliacao_media = u->avaliacao_total_user / u->numero_viagens_user;
    free(u);
    return avaliacao_media;
}
*/

short int calcula_idade (char* birthdate) {
  short int aux[4];
  short int age, birth_year, birth_month, birth_day, i = 0;
  char* tmp;
  tmp = strtok(birthdate, "/");
  
  while(tmp != NULL) {
    aux[i] = atoi(tmp);
    tmp = strtok(NULL, "/");
    i++;
  }

  birth_day = aux[0];
  birth_month = aux[1];
  birth_year = aux[2];

  short int aux2[3];
  short int year, month, day, m = 0;
  char* tmp2;
  char dateaux[15] = DATE;
  tmp2 = strtok(dateaux, "/");
  
  while(tmp2 != NULL) {
    aux2[m] = atoi(tmp2);
    tmp2 = strtok(NULL, "/");
    m++;
  }

  day = aux2[0];
  month = aux2[1];
  year = aux2[2];

if (month > birth_month || (month == birth_month && day >= birth_day)) {
     age = year - birth_year;
}
else  age = year - birth_year - 1;

 return age;
}

void update_valor (GHashTable * hash_drivers) {
  uint size = g_hash_table_size (hash_drivers);
char ** keys = g_hash_table_get_keys_as_array (hash_drivers,&size);
struct drivers * d = malloc(sizeof(struct drivers));
for (int i=0; i < size; i++) {
  d = g_hash_table_lookup (hash_drivers,keys[i]);
  d->avaliacao_media_driver = (float)d->avaliacao_total_driver / (float)d->numero_viagens_driver;
  }
 // d = g_hash_table_lookup (hash_drivers,"000000004780");
  //printf ("AVAL:%f\n", d->avaliacao_media_driver);
   // d = g_hash_table_lookup (hash_drivers,"000000007141");
  //printf ("AVAL:%f\n", d->avaliacao_media_driver);  ESTÁ A FUNCIONAR, OU SEJA, AS AVALIACOES ESTAO A SER COLOCADAS NOS STRUCTS


}
void query1_driver (char*id, GHashTable * hash_drivers) {
        struct drivers * d = g_hash_table_lookup (hash_drivers,id);
        if (!(strcmp(d->account_status,"inactive"))) {
                    FILE * output = fopen("output.txt", "w");
                    fclose (output);
        }
        else {
        d-> avaliacao_media_driver = (float)d->avaliacao_total_driver / (float)d->numero_viagens_driver;
          printf ("%f\n",d->avaliacao_media_driver);

        short int age = calcula_idade (d->birth_day);
        
        FILE * output = fopen("output.txt", "w");
        fprintf (output,"%s;" "%c;" "%d;" "%.3f;" "%d;" "%.3f\n",d->name, d->gender,age, d->avaliacao_media_driver,d->numero_viagens_driver, d->total_auferido); 
        fclose (output); 
        }
}



void query1_user (char*id, GHashTable * hash_users) {
    //decidir se é user ou driver
    struct users * u = g_hash_table_lookup (hash_users,id);
    if (!(strcmp(u->account_status,"inactive"))) {
                    FILE * output = fopen("output.txt", "w");
                    fclose (output);
        }
        else {
    u-> avaliacao_media_user = (float)u->avaliacao_total_user / (float)u->numero_viagens_user;
    short int age = calcula_idade (u->birth_date);
    FILE * output = fopen("output.txt", "w");
    fprintf (output,"%s;" "%c;" "%d;" "%.3f;" "%d;" "%.3f\n",u->name, u->gender,age, u-> avaliacao_media_user,u->numero_viagens_user, u->total_gasto); 
    fclose (output);
    } 
}

void query1_main (char*id, GHashTable * hash_users, GHashTable * hash_drivers) {
        if (isdigit(id[0]) == 0) {
        query1_user (id, hash_users);
         }
    else {
        query1_driver (id,hash_drivers);
        }
        update_valor(hash_drivers);
}