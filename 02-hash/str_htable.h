#ifndef STR_HTABLE_H_INCLUDED
#define STR_HTABLE_H_INCLUDED

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define LPHASHTABLE_INITIAL_CAPACITY 5003
#define MAX_STRING 31

int hash_str(const char *v, int M)
{
  int hash_result, a = 31415, b = 27183;

  for (hash_result = 0; *v != '\0'; v++)
  {
    a = a * b % (M - 1);
    hash_result = (a * hash_result + *v) % M;
  }

  return hash_result;
}

typedef struct LPHashTable
{
  int capacity;
  int size;
  char strings[LPHASHTABLE_INITIAL_CAPACITY][MAX_STRING];
} LPHashTable;

LPHashTable *LPHashTable_create()
{
  LPHashTable *ht = (LPHashTable *)
      calloc(1, sizeof(LPHashTable));

  ht->size = 0;
  ht->capacity = LPHASHTABLE_INITIAL_CAPACITY;

  return ht;
}

void LPHashTable_destroy(LPHashTable *ht)
{
  free(ht);
}

void LPHashTable_print(LPHashTable *ht)
{
  if (ht == NULL)
    printf("HT is null");

  int i = 0;
  printf("[\n");
  for (; i < ht->capacity; i++)
  {
    if (ht->strings[i][0] != '\0')
      printf("  %4d <- %s\n", i, ht->strings[i]);
  }
  printf("]\n");
}

int LPHashTable_set(LPHashTable *ht, const char *key)
{
  int capacity = ht->capacity;
  unsigned hash = hash_str(key, capacity);
  int probe;
  char k[MAX_STRING];

  for (probe = 0; probe < capacity; probe++)
  {
    k[0] = '\0';
    strcpy(k, ht->strings[hash]);

    if (k[0] == '\0' || strcmp(k, key) == 0)
      break;

    hash = (hash + 1) % capacity;
  }

  ht->size++;
  strcpy(ht->strings[hash], key);
  return hash;
}

int LPHashTable_search(LPHashTable *ht, const char *key) {
  int capacity = ht->capacity, probe, iterations = 0;
  unsigned hash = hash_str(key, capacity);
  char k[MAX_STRING];

  while (ht->strings[hash][0] != '\0') {
    if (iterations >= capacity)
      return -1;
    
    if (strcmp(ht->strings[hash], key) == 0)
      return hash;
    else {
      hash = (hash+1) % capacity;
      iterations++;
    }
  }
}

#endif // STR_HTABLE_H_INCLUDED