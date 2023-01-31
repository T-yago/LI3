#include "../includes/query1.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <glib.h>
#include  "../includes/drivers.h"
#include  "../includes/users.h"

/**
 * @brief Calcula o total gasto numa viagem
 * 
 * @param car_class Classe do carro 
 * @param distance Distância perorrida
 * @param tip Gorjeta dada pelo user
 * @return total gasto numa viagem
 */
double calcula_total_gasto(char car_class, unsigned short int distance, double tip) {
  double total = 0.000;
  if (car_class =='b' || car_class == 'B') {
    total = total + 3.250 + (0.620 * distance) + tip;
  } else if (car_class == 'g'|| car_class == 'G') {
    total = total + 4.000 + (0.790 * distance) + tip;
  } else if (car_class == 'p' || car_class  == 'P') {
    total = total + 5.200 + (0.94 * distance) + tip;
    }
  return total;
}



/**
 * @brief Devolve um driver 
 * 
 * @param driver Driver pedido
 * @param catalog_drivers Catálogo dos drivers
 * @param n número do ficheiro de output a gerar
 */

void query1_driver (int driver, Catalog_Drivers * catalog_drivers, int n) {
  char buffer[256];
  snprintf(buffer, 256, "Resultados/command%d_output.txt", n);

  int index_driver = driver - 1;
  if (!get_driver_acc_Status(catalog_drivers, index_driver)) {
    FILE * output = fopen(buffer, "w");
    fclose(output);
  } else {

    short int age = get_driver_age (catalog_drivers, index_driver) ;
    char * name = get_driver_name (catalog_drivers, index_driver);
    char gender = get_driver_gender(catalog_drivers, index_driver) ;
    double aval_media = get_driver_avalMedia(catalog_drivers, index_driver) ;
    int N_viagens = get_driver_Nviagens (catalog_drivers, index_driver) ;
    double total_auferido = get_driver_total_auferido (catalog_drivers, index_driver) ;

    FILE * output = fopen(buffer, "w");
    fprintf(output, "%s;"
      "%c;"
      "%d;"
      "%.3f;"
      "%d;"
      "%.3f\n", name, gender, age, aval_media, N_viagens, total_auferido);
    fclose(output);
    free (name);
  }
}

/**
 * @brief Devolve um driver 
 * 
 * @param  id id do user pedido
 * @param catalog_users Catálogo dos users
 * @param n Número do ficheiro de output a gerar
 */
void query1_user(char * id, Catalog_Users * catalog_users, int n) {
  char buffer[256];
  snprintf(buffer, 256, "Resultados/command%d_output.txt", n);
  
  if  (!getAccountStatusUser(catalog_users, id)) {
    FILE * output = fopen(buffer, "w");
    fclose(output);
  }
   
  else 
  {
    double avaliacao_media = get_aval_media_user (catalog_users, id);

    char * name = getNameUser(catalog_users, id);
    short int age = get_age_user(catalog_users,id);
    char gender = getGenderUser(catalog_users, id);
    short int N_viagens = getNviagensUser(catalog_users, id);
    double total_gasto = getTotalGastoUser(catalog_users, id);

    FILE * output = fopen(buffer, "w");
    fprintf(output, "%s;"
      "%c;"
      "%d;"
      "%.3f;"
      "%d;"
      "%.3f\n", name, gender, age, avaliacao_media, N_viagens, total_gasto);
    fclose(output);
    free (name);
  }
}

/**
 * @brief Chama a query1 para user ou para drivers dependendo do input
 * 
 * @param id id do user pedido
 * @param catalog_users Catálogo dos users
 * @param catalog_drivers Catálogo dos drivers
 * @param n Número do ficheiro de output a gerar 
 */

void query1_main(char * id, Catalog_Users * catalog_users, Catalog_Drivers * catalog_drivers, int n) {
  if (isdigit(id[0]) == 0) {
    query1_user(id, catalog_users, n);
  } else {
    int driver = atoi(id);
    query1_driver(driver, catalog_drivers, n);
  }
}