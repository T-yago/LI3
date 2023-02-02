#include "../includes/query8.h"
#define DATE_REFERENCE "09/10/2022"

/**
 * @brief Listar todas as viagens nas quais o utilizador e o condutor são do género passado como pa-
râmetro
 * 
 * @param gender Género a apresentar 
 * @param age Idade
 * @param catalog_rides Catálogo das rides
 * @param catalog_users Catálogo dos users
 * @param catalog_drivers Catálogo dos drivers
 * @param n Número do ficheiro de output a gerar
 */

void query8 (char gender, int age, Catalog_Rides* catalog_rides, Catalog_Users* catalog_users, Catalog_Drivers* catalog_drivers, int n) {
    
    char buffer[256];
    snprintf(buffer, 256, "Resultados/command%d_output.txt", n);
    FILE * output = fopen(buffer, "w");
    
    int id_driver;
    char* id_user;
    char* name_driver;
    char* name_user;
    unsigned int id_ride = 0;
    unsigned short int age_in_days = convert_to_day (DATE_REFERENCE) - (age * 365) - 3; // Calcular o dia a partir do qual a idade é maior à pedida
    unsigned int * array_ids =  check_gender_in_rides (catalog_rides, gender, age_in_days); //recebe o array de ids que correspondem às viagens válidas

    for (int i = 0; array_ids[i]!=0; i++) {

        id_ride = array_ids [i];
        id_driver = get_ride_driver (catalog_rides, id_ride); // tem que se subtrair 1 para aceder ao array mas não quando se for imprimir ---> tratar disto
        id_user = get_ride_user (catalog_rides, id_ride);
        name_driver = get_driver_name (catalog_drivers, id_driver - 1);
        name_user = getNameUser (catalog_users, id_user);
        if (get_driver_acc_Status (catalog_drivers,id_driver - 1) && getAccountStatusUser(catalog_users,id_user))
        fprintf(output, "%012d;" "%s;" "%s;" "%s\n", id_driver, name_driver, id_user, name_user);
        free (id_user);
        free (name_driver);
        free(name_user);
    }
    free (array_ids);
}