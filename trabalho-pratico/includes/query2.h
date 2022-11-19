struct query2 {
  char * id;
  double avaliacao_media;
  char* name;
  unsigned short int data;
};

int compare (const void *a, const void *b);
void query2 (GHashTable * hash_drivers, int n);