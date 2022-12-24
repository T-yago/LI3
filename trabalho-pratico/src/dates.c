#include <stdio.h>

#include "../includes/dates.h"

unsigned short int convert_to_day(char * date) {
  unsigned short int day;
  unsigned short int month;
  unsigned short int year;
  unsigned short int total_days = 0;
  sscanf(date, "%hu/%hu/%hu", & day, & month, & year);
  int meses [12] = {0,31,59,90,120,151,181,212,243,273,304,334};
  total_days += meses [month-1];

  year = year - 2000;
  while (year != 0) {
    if (year % 4 == 0) {
      total_days += 366; // ano ser bissexto
    } else {
      total_days += 365;
    }
    year--;
  }
  total_days += day;
  return total_days;
}

/*
char * dataToChar (unsigned short int data) {
    int i;
    for (i=1;data > 365) {
        if (i % 4 == 0) {
            data -= 366;
        }
        else {
            data -= 365;
        }
    }
    for (i=0; data >31) {


    }
}
*/
