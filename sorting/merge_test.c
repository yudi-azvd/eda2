#include <stdio.h>

#include "mergesort.h"

void print_arr(int* v, int size) {
  for (size_t i = 0; i < size; i++)
    printf("%d ", v[i]);
  printf("\n");
}

int main() {
  // int v[] = {0, 3, 18, 4, 14, 20};
  int v[] = {0, 3, 18, 20, 14, 16, 30};
  // int v[] = {0, 3, 18, 20, 40, 14, 20, 30};
  int size = sizeof(v)/sizeof(int);

  print_arr(v, size);
  merge(v, 0, size/2, size-1);
  print_arr(v, size);

  return 0;
}