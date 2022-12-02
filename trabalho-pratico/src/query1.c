#include <stdio.h>

#include <string.h>

#include <stdbool.h>

#include <ctype.h>

#include <glib.h>

#include "../includes/parser.h"

#include "../includes/drivers.h"

#include "../includes/users.h"

#include "../includes/query1.h"

#define DATE "09/10/2022"


double calcula_total_gasto(char * car_class, short int distance, double tip) {
  double total = 0.000;
  if (!(strcmp(car_class, "basic"))) {
    total = total + 3.250 + (0.620 * distance) + tip;
  } else if (!(strcmp(car_class, "green"))) {
    total = total + 4.000 + (0.790 * distance) + tip;
  } else {
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

void update_valor(Catalog_Drivers * hash_drivers) {
  uint size = get_hash_drivers_size(hash_drivers);
 gpointer *  keys = get_keys_as_array_drivers(hash_drivers, size);
  for (uint i = 0; i < size; i++) {
    //d -> avaliacao_media_driver = (float) d -> avaliacao_total_driver / (float) d -> numero_viagens_driver;
    double r = (float) getAvaliacaoTotalDriver(hash_drivers, keys[i]) / (float) getNviagensDriver(hash_drivers, keys[i]);
    avaliacaoMediaDriver(hash_drivers, keys[i], r);
  }
}

void query1_driver(char * id, Catalog_Drivers * hash_drivers, int n) {

  char buffer[256];
  snprintf(buffer, 256, "Resultados/command%d_output.txt", n);

  if (getAccountStatus(hash_drivers, id)) {
    FILE * output = fopen(buffer, "w");
    fclose(output);
  } else {
    //d -> avaliacao_media_driver = (float) d -> avaliacao_total_driver / (float) d -> numero_viagens_driver;
    double r = (float) getAvaliacaoTotalDriver(hash_drivers, id) / (float) getNviagensDriver(hash_drivers, id);
    avaliacaoMediaDriver(hash_drivers, id, r);

    short int age = calcula_idade(getBirthDayDriver(hash_drivers, id));

    FILE * output = fopen(buffer, "w");
    fprintf(output, "%s;"
      "%c;"
      "%d;"
      "%.3f;"
      "%d;"
      "%.3f\n", getNameaDriver(hash_drivers, id), getGenderDriver(hash_drivers, id), age, getAvaliacaoMediaDriver(hash_drivers, id), getNviagensDriver(hash_drivers, id), getTotalAuferidoDriver(hash_drivers, id));
    fclose(output);
  }
}

void query1_user(char * id, Catalog_Users * hash_users, int n) {
  char buffer[256];
  snprintf(buffer, 256, "Resultados/command%d_output.txt", n);
  if ( getAccountStatusUser(hash_users, id)) {
    FILE * output = fopen(buffer, "w");
    if (output == NULL) {
      printf("Error opening output.\n");
    }
    fclose(output);
  } else {
    double r = (float) getAvaliacaoTotalUser(hash_users, id) / (float) getNviagensUser(hash_users, id);
    avaliacaoMediaUser(hash_users, id, r);

    short int age = calcula_idade(getBirthDateUser(hash_users, id));
    FILE * output = fopen(buffer, "w");
    fprintf(output, "%s;"
      "%c;"
      "%d;"
      "%.3f;"
      "%d;"
      "%.3f\n", getNameUser(hash_users, id), getGenderUser(hash_users, id), age, getAvaliacaoMediaUser(hash_users, id), getNviagensUser(hash_users, id), getTotalGastoUser(hash_users, id));
    fclose(output);
  }
}

void query1_main(char * id, Catalog_Users * hash_users, Catalog_Drivers * hash_drivers, int n) {
  if (isdigit(id[0]) == 0) {
    query1_user(id, hash_users, n);
  } else {
    query1_driver(id, hash_drivers, n);
  }
  update_valor(hash_drivers);
}