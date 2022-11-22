#include <stdio.h>

#include "../includes/dates.h"

unsigned short int convert_to_day(char * date) {
  unsigned short int day;
  unsigned short int month;
  unsigned short int year;
  unsigned short int total_days = 0;
  sscanf(date, "%hu/%hu/%hu", & day, & month, & year);
  //int meses [12] = {0,31,59,90,120,151,181,212,243,273,304,334};
  //  total_days += meses [month-1];

  switch (month) {
  case 2:
    total_days += 31;
    break;

  case 3:
    total_days += 59;; //assumindo que fevereiro tem 28 dias
    break;

  case 4:
    total_days += 90;
    break;

  case 5:
    total_days += 120;
    break;

  case 6:
    total_days += 151;
    break;

  case 7:
    total_days += 181;
    break;

  case 8:
    total_days += 212;
    break;

  case 9:
    total_days += 243;
    break;

  case 10:
    total_days += 273;
    break;

  case 11:
    total_days += 304;
    break;

  case 12:
    total_days += 334;
    break;
  }
  if (month >= 2) {
    if (year % 4 == 0) total_days++;
  }

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
