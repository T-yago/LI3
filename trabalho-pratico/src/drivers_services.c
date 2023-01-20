#include "../includes/drivers_services.h"

//---------------------------------------------Estrutura auxiliar dos drivers (query2) ---------------------------------------------//

struct driver_aval_date {
  int id;
  double avaliacao_media;
  char* name;
  unsigned short int data;
};

// Função de comparação que ordena o array com os top_N_drivers
int compare(const void * a,
  const void * b) {
   Driver_Aval_Date *ia = (Driver_Aval_Date *) a;
   Driver_Aval_Date *ib = (Driver_Aval_Date*) b;

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

// Substituir por foreach
void top_N_drivers (Catalog_Drivers * catalog_drivers) {
  uint size = get_array_drivers_size (catalog_drivers);
  Driver_Aval_Date * driver_aval_date = malloc (size * (sizeof (Driver_Aval_Date)));
  
  for (uint i = 0; i < size; i++) {

    (driver_aval_date + i) -> id = i+1;
    (driver_aval_date + i) -> avaliacao_media = get_driver_avalMedia (catalog_drivers, i);
    (driver_aval_date + i) -> data = get_driver_date (catalog_drivers, i);
    (driver_aval_date + i) -> name = get_driver_name (catalog_drivers, i);

  }

  qsort((void * ) driver_aval_date, size, sizeof(Driver_Aval_Date), compare);
  set_top_N_drivers (catalog_drivers, driver_aval_date);
  
}


char * get_name_driver_top_N (Catalog_Drivers * catalog_drivers,int index) {
  Driver_Aval_Date* top_N_drivers = (Driver_Aval_Date*) get_top_N_drivers (catalog_drivers);
  Driver_Aval_Date aux = top_N_drivers [index]; 
return  strdup(aux.name);
}

int get_id_driver_top_N (Catalog_Drivers * catalog_drivers, int index) {
  Driver_Aval_Date* top_N_drivers = (Driver_Aval_Date*) get_top_N_drivers (catalog_drivers);
  Driver_Aval_Date aux = top_N_drivers [index];  
return (aux.id);
}

double get_aval_med_top_N (Catalog_Drivers * catalog_drivers, int index) {
  Driver_Aval_Date* top_N_drivers = (Driver_Aval_Date*) get_top_N_drivers (catalog_drivers);
  Driver_Aval_Date aux = top_N_drivers [index]; 
return aux.avaliacao_media;
}

void free_drivers_services (Catalog_Drivers* catalog_drivers, unsigned int size) {
  Driver_Aval_Date* top_N_drivers = (Driver_Aval_Date*) get_top_N_drivers (catalog_drivers);
  for (uint i = 0; i < size; i++) {
    Driver_Aval_Date aux = top_N_drivers [i];
    free (aux.name);
  }
}

