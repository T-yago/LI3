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

char* convert_to_date(unsigned short int days) {
  int day = 1;
  int month = 1;
  int year = 2000;
  day += days;
  while (1) {
      if (month == 2) {
          if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
              if (day > 29) {
                  day -= 29;
                  month++;
              } else {
                  break;
              }
          } else {
              if (day > 28) {
                  day -= 28;
                  month++;
              } else {
                  break;
              }
          }
      } else if (month == 4 || month == 6 || month == 9 || month == 11) {
          if (day > 30) {
              day -= 30;
              month++;
          } else {
              break;
          }
      } else {
          if (month == 12) {
              if (day > 31) {
                  day -= 31;
                  month = 1;
                  year++;
              } else {
                  break;
              }
          } else {
              if (day > 31) {
                  day -= 31;
                  month++;
              } else {
                  break;
              }
          }
      }
  }
  char* buffer = malloc(256);
  snprintf(buffer, 256, "%02d/%02d/%02d", day, month, year);
  return buffer;
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
