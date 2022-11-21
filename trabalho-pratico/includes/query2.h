#ifndef QUERY2_H
#define QUERY2_H

typedef struct query2 Query2;

int compare (const void *a, const void *b);
void query2 (GHashTable * hash_drivers, char* info, int n);

#endif 