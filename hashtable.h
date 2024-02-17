#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

// Define hashtable structure
struct hashtable
{
    char **keys;      // url set with key
    int *documentIDs; // id for each url
    bool *occupied;   // mark if its existed
    size_t capacity;  // capacity of hashtable
    size_t size;      // size of hashtable
};

typedef struct hashtable hashtable_t;

size_t hash_function(const char *key, size_t capacity);

struct hashtable *hashtable_new(size_t capacity);

bool hashtable_insert_with_id(struct hashtable *ht, const char *key, int documentID);

int hashtable_get_document_id(struct hashtable *ht, const char *key);

void hashtable_delete(struct hashtable *ht);

#endif

