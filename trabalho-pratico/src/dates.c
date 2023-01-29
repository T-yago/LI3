#include <stdio.h>
#define DATE "09/10/2022"

#include "../includes/dates.h"

/**
 * @brief Calcula a idade baseado numa string da data de nascimento
 * 
 * @param birthdate string da data de nascimento 
 * @return idade em dias
 * 
 */
short int calcula_idade(char * birthdate) {
  short int birth_year, birth_month, birth_day;
  short int year, month, day;
  sscanf(birthdate, "%hd/%hd/%hd", &birth_day, &birth_month, &birth_year);
  sscanf(DATE, "%hd/%hd/%hd", &day, &month, &year);

  if (month > birth_month || (month == birth_month && day >= birth_day)) {
    return year - birth_year;
  } else {
    return year - birth_year - 1;
  }
}

/**
 * @brief Converte uma string contendo uma data válida "XX/XX/XX" num unsigned short int
 * 
 * @param date string com a data a converter
 * @return número de dias que passaram desde 2000 até essa data se for válida
 * @return 65535 caso a data seja inválida
 * @return 0 se a data a tentar converter seja antes de 2000
 */

unsigned short int convert_to_day(char * date) {
  unsigned short int day;
  unsigned short int month;
  unsigned short int year;
  unsigned short int total_days = 0;
  int fields = sscanf(date, "%hu/%hu/%hu", & day, & month, & year);
  if (fields != 3 || day > 31 || month > 12) return 65535; // returns USHRT_MAX    
  if (year<2000) return 0; // para não devolver falso no caso de averiguarmos a validade de datas de nascimento
  
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

/**
 * @brief Converte uma data de unsigned short int para string 
 * 
 * @param days data convertida em dias
 * @return data em formato de string
 */
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

