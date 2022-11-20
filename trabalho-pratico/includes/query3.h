#ifndef QUERY3_H
#define QUERY3_H

#include "../includes/rides.h" 

struct users;


struct query3 {
  char * id;
  int distance;
  char* name;
  unsigned short int data;
};

int compare_users (const void *a, const void *b);
void query3 (GHashTable * hash_users,char* info, int n);

#endif
