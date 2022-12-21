#ifndef PARSER_H
#define PARSER_H

#include <glib.h>

typedef void* (*create_fn)(char** tokens, void* catalog);

void parse_csv(const char* filename, create_fn create_fn, void* catalog);


#endif