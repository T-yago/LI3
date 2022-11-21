#ifndef QUERY3_H
#define QUERY3_H

typedef struct query3 Query3;

int compare_users (const void *a, const void *b);
void query3 (GHashTable * hash_users,char* info, int n);

#endif
