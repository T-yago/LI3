#ifndef PARSER_H
#define PARSER_H

#include "users.h"
#include "drivers.h"

typedef void FunctionPointer(char* string, GHashTable* hash_users, GHashTable* hash_drivers, int n);

void parser_input();
char* substr(const char *str, int m, int n);
char* fixstring(char* info);

#endif