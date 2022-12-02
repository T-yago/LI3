#ifndef QUERY2_H
#define QUERY2_H

#include <stdio.h>
#include <glib.h>
#include <stdbool.h>
#include "../includes/drivers.h"

typedef struct query2 Query2;

void query2 (Catalog_Drivers * catalog_drivers, char* info, int n);

#endif 