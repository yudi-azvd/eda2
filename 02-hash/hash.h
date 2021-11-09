#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include <stdlib.h>

#define hash(v, M) (v % M)
#define hash(v, M) (16161 * (unsigned) v % M)


typedef struct HashTable_item {
  int key;
  long addr1, addr2;
  long element;  
} HashTable_item;


static const HashTable_item HashTable_null = {0, 0, 0, 0};

#define hash_key(x) (x.key)
#define hash_less(a, b) (hash_key(a) < hash_key(b))
#define hash_is_null(a) (hash_key(ht[a]) == hash_key(HashTable_null))

static int N, M;

static HashTable_item* ht;


void HashTable_create(int max) {
  int i;
  N = 0; M = 2*max;
  ht = (HashTable_item*) calloc(M, sizeof(HashTable_item));
}


int HashTable_count() {
  return N;
}

void HashTable_insert(HashTable_item ht_item) {
  int k = hash_key(ht_item);
  int i = hash(k, M);

  while (!hash_is_null(i))
    i = (i+1) % M;
  ht[i] = ht_item;
  N++;  
}


HashTable_item HashTable_search(int key) {
  // int i = hash(key, M);

  // while (!hash_is_null(i))
  //   if (eq(key, hash_key(ht[i])))
  //     return ht[i];
  //   else
  //     i = (i+1) % M;
  
  // return HashTable_null;
}

// v: string, M: tamanho máximo da tabela
// int uhash_str(char* v, int M) {
//   int hash_result, a = 31415, b = 27183;

//   for ( hash_result = 0; *v != '\0'; v++) {
//     a = a*b % (M-1);
//     hash_result = (a*hash_result + *v) % M;
//   }
//   return hash_result;
// }

#endif