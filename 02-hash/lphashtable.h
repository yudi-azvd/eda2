#ifndef LPHASHTABLE_H_INCLUDED
#define LPHASHTABLE_H_INCLUDED

// Linear Probing HashTable

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define LPHASHTABLE_INITIAL_CAPACITY 11

typedef struct LPHashTable_item {
  unsigned key;
  int value;
  int8_t is_defined; // not null
} LPHashTable_item;

static const LPHashTable_item LPHashTable_null = {0, 0, 0};

typedef struct LPHashTable {
  int capacity;
  int size;
  LPHashTable_item* items;
} LPHashTable;

// Não usar com números negativos kkkk
#define LPHashTable_hash(n, capacity) (n % capacity)
#define LPHashTable_is_null(lpht_item) (lpht_item.is_defined == 0)

int LPHashTable_size(LPHashTable* ht) {
  return ht->size;
}

LPHashTable* LPHashTable_create() {
  LPHashTable* ht = (LPHashTable*) 
    calloc(1, sizeof(LPHashTable));

  ht->size = 0;
  ht->capacity = LPHASHTABLE_INITIAL_CAPACITY;
  ht->items = (LPHashTable_item*)
    calloc(LPHASHTABLE_INITIAL_CAPACITY, sizeof(LPHashTable_item));

  return ht;
}

void LPHashTable_destroy(LPHashTable* ht) {
  free(ht->items);
  free(ht);
}


void LPHashTable_print(LPHashTable* ht) {
  if (ht == NULL)
    printf("HT is null");

  int i = 0;
  printf("[\n");
  for (; i < ht->capacity; i++) {
    if (ht->items[i].is_defined)
      printf("%3d -> %3d\n", ht->items[i].key, ht->items[i].value);
  }
  printf("[\n");
  
}


int LPHashTable_search(LPHashTable* ht, int key) {
  int capacity = ht->capacity;
  unsigned hashed_key = LPHashTable_hash(key, capacity);
  int iterations = 0, value = 0;

  while (ht->items[hashed_key].is_defined) {
    if (iterations == ht->capacity) {
      return 0;
    }

    if (ht->items[hashed_key].key == key)
      return ht->items[hashed_key].value;
    else  {
      hashed_key = (hashed_key+1) % capacity;
      ++iterations;
    }
  }

  return 0;
}

void LPHashTable_set(LPHashTable* ht, int key, int value) {
  int capacity = ht->capacity;
  unsigned hashed_key = LPHashTable_hash(key, capacity);
  int probe, k;

  for (probe = 0; probe < capacity; probe++) {
    k = ht->items[hashed_key].key;

    // se a posição está vaga ou se a chave foi encontrada
    if (!ht->items[hashed_key].is_defined || k == key)
      // encontramos a posição
      break;

    hashed_key = (hashed_key+1) % capacity;
  }

  if (probe >= capacity) {
    printf("table is full\n");
    exit(1);
  }

  // if (!ht->itens[hashed_key].is_defined)
    ht->items[hashed_key].key = key;
  ht->size++;
  ht->items[hashed_key].value = value;
  ht->items[hashed_key].is_defined = 1;
}

void LPHashTable_unset(LPHashTable* ht, int key) {
  int capacity = ht->capacity;
  unsigned hashed_key = LPHashTable_hash(key, capacity);

  // unset a key cujo valor é G
  // ... D G P A _ T ...
  // ... D _ P A _ T ...
  // ... D P A _ _ T ...
  // Tem que ir arrastando pra esquerda todos os valores
  // à direita da chave removida, pois todas as suas chaves
  // possuem a mesma hash.
}


#endif // LPHASHTABLE