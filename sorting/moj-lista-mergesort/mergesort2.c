#include <stdio.h>
#include <stdlib.h>

void merge(int* v, int lo, int hi1, int hi2) {
  int k = 0, i = lo, j = hi1+1;
  int* aux = (int*) calloc(hi2-lo+1, sizeof(int));

  // while (i <= hi1 || j <= hi2) {
  while (i <= hi1 && j <= hi2) {
    // if (i > hi1)         // 1o vetor esgotou
    //   aux[k++] = v[j++]; // copiar o restinho do 2o vetor
    // else if (j > hi2)    // 2o vetor esgotou
    //   aux[k++] = v[i++]; // copiar o restinho do 1o vetor

    // else
     if (v[i] < v[j]) // less(v[i], v[j])
      aux[k++] = v[i++];
    else
      aux[k++] = v[j++];
  }

  // copiar o restinho do 1o vetor
  while (i <= hi1) {
    aux[k++] = v[i++];
  }

  // copiar o restinho do 2o vetor
  while (j <= hi2) {
    aux[k++] = v[j++];
  }

  // copiar para o vetor original
  k = 0;
  for (i = lo; i <= hi2; ++i)
    v[i] = aux[k++];

  free(aux);  
}


void mergesort(int* v, int lo, int hi) {
  if (lo >= hi) return;

  int mid = (lo+hi)/2;

  mergesort(v, lo, mid);
  mergesort(v, mid+1, hi);
  merge(v, lo, mid, hi);
}


void print_arr(int* a, int size) {
  int i = 0;
  for (; i < size-1; i++)
    printf("%d ", a[i]);
  printf("%d\n", a[i]);
}


int main() {
  int v[100000], i=0, n;

  while (scanf("%d", &v[i]) != EOF)
    i++;

  n = i;
  mergesort(v, 0, n-1);

  print_arr(v, n);

  return 0;
}