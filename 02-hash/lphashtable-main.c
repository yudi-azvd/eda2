#include <stdio.h>

#include "lphashtable.h"

int main() {
  LPHashTable* ht = LPHashTable_create();

  LPHashTable_set(ht, 1, 1);
  LPHashTable_set(ht, 12, 144);
  LPHashTable_set(ht, 5, 25);
  LPHashTable_set(ht, 10, 100);
  LPHashTable_set(ht, 11, 121);
  LPHashTable_set(ht, 15, 225);
  LPHashTable_set(ht, 14, 266);
  LPHashTable_set(ht, 23, 400);
  LPHashTable_set(ht, 45, 500);
  LPHashTable_set(ht, 60, 666);
  LPHashTable_set(ht, 70, 777);
  LPHashTable_set(ht, 99, 9191);

  printf("%d\n", LPHashTable_search(ht, 1));
  printf("%d\n", LPHashTable_search(ht, 5));
  printf("%d\n", LPHashTable_search(ht, 11));
  printf("%d\n", LPHashTable_search(ht, 15));
  printf("%d\n", LPHashTable_search(ht, 45));
  printf("%d\n", LPHashTable_search(ht, 60));
  printf("%d\n", LPHashTable_search(ht, 70));

  printf("\n");
  LPHashTable_print(ht);
  printf("size = %d\n", LPHashTable_size(ht));

  LPHashTable_destroy(ht);
}