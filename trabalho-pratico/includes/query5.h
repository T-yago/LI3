#ifndef QUERY5_H
#define QUERY5_H

#include <stdio.h>

#include "../includes/rides.h"

#include "../includes/drivers.h"

#include "../includes/query1.h" // por causa do calcula_tt_gasto

#include "../includes/dates.h"

typedef struct query5 Query5;

void query5 (char * dateA, char * dateB, Catalog_Drivers * catalog_drivers, Catalog_Rides * catalog_rides, int n);
#endif