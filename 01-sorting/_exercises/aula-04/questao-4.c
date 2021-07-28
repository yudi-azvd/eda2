
// questao 4
// https://www.brunoribas.com.br/eda2/2021-1/#org82d4200

#include <stdio.h>
#include <stdlib.h>

#include "../../convention.h"


void merge(int* merged_arr, int* a, int lo1, int hi1, int* b, int lo2, int hi2) {
  int total_len = (hi1-lo1+1) + (hi2-lo2+1);
  int i = lo1, j = lo2, k = 0;

  while (i <= hi1 && j <= hi2) {
    if (a[i] < b[j])
      merged_arr[k++] = a[i++];
    else
      merged_arr[k++] = b[j++];
  }

  while (i <= hi1)
    merged_arr[k++] = a[i++];
  
  while (j <= hi2)
    merged_arr[k++] = b[j++];
}

// Versão recursiva do merge
void merge_r(int* merged_arr, int k, int* a, int lo1, int hi1, int* b, int lo2, int hi2) {
  if (lo1 > hi1 && lo2 > hi2) return;

  if (lo1 > hi1)
    merged_arr[k] = b[lo2++];
  else if (lo2 > hi2)
    merged_arr[k] = a[lo1++];
  else if (a[lo1] < b[lo2])
    merged_arr[k] = a[lo1++];
  else
    merged_arr[k] = b[lo2++];

  merge_r(merged_arr, k+1, a, lo1, hi1, b, lo2, hi2);  
}



void print_arr(int* v, int size) {
  for (size_t i = 0; i < size; i++)
    printf("%d ", v[i]);
  printf("\n");
}


int main() {
  int a[] = {-100, 0, 2, 3, 4, 100};
  int len_a = sizeof(a)/sizeof(int);
  int b[] = {-2, -1, 0, 2, 4};
  int len_b = sizeof(b)/sizeof(int);
  int merged_len = len_a+len_b;

  int* m = calloc(merged_len, sizeof(int));
  // merge(m, a, 0, len_a-1, b, 0, len_b-1);
  merge_r(m, 0, a, 0, len_a-1, b, 0, len_b-1);

  print_arr(m, merged_len);
  printf("is sorted: %d\n", issorted(m, merged_len));

  free(m);

  return 0;
}