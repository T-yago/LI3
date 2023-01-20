#include <stdio.h>

#include <string.h>

#include <stdbool.h>

#include <ctype.h>

#include <glib.h>

#include "../includes/drivers.h"

#include "../includes/users.h"

#include "../includes/query1.h"

#define DATE "09/10/2022"


double calcula_total_gasto(char* car_class, unsigned short int distance, double tip) {
  double total = 0.000;
  if (car_class[0] =='b' || car_class[0] == 'B') {
    total = total + 3.250 + (0.620 * distance) + tip;
  } else if (car_class[0] == 'g'|| car_class[0] == 'G') {
    total = total + 4.000 + (0.790 * distance) + tip;
  } else if (car_class[0] == 'p' || car_class [0] == 'P') {
    total = total + 5.200 + (0.94 * distance) + tip;
    }
  return total;
}


short int calcula_idade(char * birthdate) {
  short int aux[4];
  short int age, birth_year, birth_month, birth_day, i = 0;
  char * tmp;
  tmp = strtok(birthdate, "/");

  while (tmp != NULL) {
    aux[i] = atoi(tmp);
    tmp = strtok(NULL, "/");
    i++;
  }

  birth_day = aux[0];
  birth_month = aux[1];
  birth_year = aux[2];

  short int aux2[3];
  short int year, month, day, m = 0;
  char * tmp2;
  char dateaux[15] = DATE;
  tmp2 = strtok(dateaux, "/");

  while (tmp2 != NULL) {
    aux2[m] = atoi(tmp2);
    tmp2 = strtok(NULL, "/");
    m++;
  }

  day = aux2[0];
  month = aux2[1];
  year = aux2[2];

  if (month > birth_month || (month == birth_month && day >= birth_day)) {
    age = year - birth_year;
  } else age = year - birth_year - 1;

  return age;
}



void query1_driver (int index, Catalog_Drivers * catalog_drivers, int n) {
  char buffer[256];
  snprintf(buffer, 256, "Resultados/command%d_output.txt", n);

  if (!get_driver_acc_Status(catalog_drivers, index - 1)) {
    FILE * output = fopen(buffer, "w");
    fclose(output);
  } else {
    //double r = (float) getAvaliacaoMediaDriver(catalog_drivers, id) / (float) getNviagensDriver(catalog_drivers, id);
    //avaliacaoMediaDriver(catalog_drivers, id, r);

    short int age = get_driver_age (catalog_drivers, index - 1);
    char * name = get_driver_name (catalog_drivers, index -1 );

    FILE * output = fopen(buffer, "w");
    fprintf(output, "%s;"
      "%c;"
      "%d;"
      "%.3f;"
      "%d;"
      "%.3f\n", name, get_driver_gender(catalog_drivers, index - 1), age, get_driver_avalMedia(catalog_drivers, index - 1), get_driver_Nviagens (catalog_drivers, index - 1), get_driver_total_auferido (catalog_drivers, index - 1));
    fclose(output);
    free (name);
  }
}

void query1_user(char * id, Catalog_Users * catalog_users, int n) {
  char buffer[256];
  snprintf(buffer, 256, "Resultados/command%d_output.txt", n);
  if  (!getAccountStatusUser(catalog_users, id)) {
    FILE * output = fopen(buffer, "w");
    fclose(output);
  } else {
    double avaliacao_media = (float) getAvaliacaoTotalUser(catalog_users, id) / (float) getNviagensUser(catalog_users, id);

    char * name = getNameUser(catalog_users, id);
    short int age = get_age_user(catalog_users,id);
    FILE * output = fopen(buffer, "w");
    fprintf(output, "%s;"
      "%c;"
      "%d;"
      "%.3f;"
      "%d;"
      "%.3f\n", name, getGenderUser(catalog_users, id), age, avaliacao_media, getNviagensUser(catalog_users, id), getTotalGastoUser(catalog_users, id));
    fclose(output);
    free (name);
  }
}

void query1_main(char * id, Catalog_Users * catalog_users, Catalog_Drivers * catalog_drivers, int n) {
  //printf ("%d\n",n);
  if (isdigit(id[0]) == 0) {
    query1_user(id, catalog_users, n);
  } else {
    int index = atoi(id);
    query1_driver(index, catalog_drivers, n);
  }
}