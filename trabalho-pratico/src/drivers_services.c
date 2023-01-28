#include "../includes/drivers_services.h"

//---------------------------------------------Estrutura auxiliar dos drivers (query2) ---------------------------------------------//

/**
 * @brief Struct usada para ordenar os drivers em função da avaliação média, datas e ids
 * 
 */

struct driver_aval_date {
  /**
   * @brief Id do driver
   * 
   */
  int id;
  /**
   * @brief Avaliação média do driver
   * 
   */
  double avaliacao_media;

  /**
   * @brief data da viagem mais recente do driver (convertida)
   * 
   */
  unsigned short int data;
};

// Função de comparação que ordena o array com os top_N_drivers
/**
 * @brief Função de comparação usada para os top_N_drivers
 * 
 * @param a posição arbitrária "a" do array a comparar
 * @param b posição arbitrária "b" do array a comparar
 * @return escolha para ordenaçãp
 */
int compare(const void * a, const void * b) {
   Driver_Aval_Date *ia = *(Driver_Aval_Date**) a;
   Driver_Aval_Date *ib = *(Driver_Aval_Date**) b;

  if (ia -> avaliacao_media < ib -> avaliacao_media) return 1;

  if (ia -> avaliacao_media > ib -> avaliacao_media) return -1;

  if (ia -> avaliacao_media == ib -> avaliacao_media) {
    if (ia -> data < ib -> data) return 1; 
    if (ia -> data > ib -> data) return -1;
    else if (ia -> data == ib -> data) { 
      return ia->id - ib->id;
    }
  }  return 0;
}

// Função que cria um array com os top "N" users e o coloca no catálogo dos drivers


/**
 * @brief Cria um array com ordenado com os top_N_drivers presentes no catálogo e adiciona-o ao catálogo
 * 
 * @param catalog_drivers catálogo dos drivers
 */

void top_N_drivers (Catalog_Drivers * catalog_drivers) {
  
  uint size = get_array_drivers_size (catalog_drivers);
  Driver_Aval_Date ** driver_aval_date = malloc (sizeof (Driver_Aval_Date*) * 100);
  int array_length = 0;

  // Para cada driver, verifica se é válido e adiciona ao array
  for (uint i = 0; i < size; i++) {
    if (get_driver_acc_Status (catalog_drivers, i) == true) {
    Driver_Aval_Date* aux = malloc (sizeof (Driver_Aval_Date));
    aux -> id = i+1;
    aux -> avaliacao_media = get_driver_avalMedia (catalog_drivers, i);
    aux -> data = get_driver_date (catalog_drivers, i);

    driver_aval_date[array_length] = aux;
    array_length++;
    if (array_length % 100 == 0) driver_aval_date = realloc (driver_aval_date, sizeof (Driver_Aval_Date*) * (array_length + 100));
    }
  }
  qsort((void * ) driver_aval_date, array_length, sizeof(Driver_Aval_Date*), compare);

  set_top_N_drivers (catalog_drivers, driver_aval_date, array_length); 
}

/**
 * @brief Devolve o id do driver presente no array ordenado dos drivers na posição "index"
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @param index Índice do array ordenado
 * @return id do driver
 */

int get_id_driver_top_N (Catalog_Drivers * catalog_drivers, int index) {
  Driver_Aval_Date** top_N_drivers = (Driver_Aval_Date**) get_top_N_drivers (catalog_drivers);
  Driver_Aval_Date* aux = top_N_drivers [index];  
return (aux->id);
}


/**
 * @brief Devolve a avaliação média do driver presente no array ordenado dos drivers na posição "index"
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @param index Índice do array ordenado
 * @return Avaliação média do driver 
 */

double get_aval_med_top_N (Catalog_Drivers * catalog_drivers, int index) {
  Driver_Aval_Date** top_N_drivers = (Driver_Aval_Date**) get_top_N_drivers (catalog_drivers);
  Driver_Aval_Date* aux = top_N_drivers [index]; 
return aux->avaliacao_media;
}

/**
 * @brief Liberta a memória associada ao array ordenado dos drivers
 * 
 * @param catalog_drivers Catálogo dos drivers
 * @param size tamanho do array ordenado dos drivers
 */

void free_top_N_drivers (Catalog_Drivers* catalog_drivers, int size) {
  Driver_Aval_Date** top_N_drivers = (Driver_Aval_Date**) get_top_N_drivers (catalog_drivers);
  for (int i = 0; i < size; i++) {
    Driver_Aval_Date* aux = top_N_drivers [i];
  //  free (aux->name);
    free (aux);
  }
}

