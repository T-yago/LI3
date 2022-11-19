#ifndef QUERY3_H
#define QUERY3_H

#include "../includes/rides.h" 

struct query3 {
  char * id;
  int distance;
  char* name;
  unsigned short int data;
};
void initHash_users (GHashTable * hash_users);
int compare_users (const void *a, const void *b);
void query3 (GHashTable * hash_users, int n);

#endif