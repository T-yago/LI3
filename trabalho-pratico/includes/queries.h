#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

typedef struct drivers {
    int  id;
    char name[30];
    char birth_date[9];
    char gender;
    char car_class[6];
    char license_plate[5];
    char city[10];
    char account_creation[9];
    char account_status[7];
}   Drivers;