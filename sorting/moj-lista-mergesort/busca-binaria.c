#include <stdio.h>

#include <stdlib.h>

void merge(int* v, int lo, int hi1, int hi2) {
  int k = 0, i = lo, j = hi1+1;
  int* aux = (int*) calloc(hi2-lo+1, sizeof(int));

  while (i <= hi1 && j <= hi2) {
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


int binarysearch(int to_find, int* v, int lo, int hi) {
  int mid = (lo + hi)/2;

  while (lo <= hi) {
    if (v[mid] < to_find)
      lo = mid+1;
    else if (to_find < v[mid])
      hi = mid-1;
    else
      return mid;

    mid = (lo + hi)/2;
  }

  return v[mid] == to_find ? mid : -1;
}

int main() {
  int i = 0, N, M, v[100000];

  scanf("%d %d\n", &N, &M);

  while (i < N) {
    scanf("%d\n", &v[i++]);
  }

  mergesort(v, 0, N-1);
  print_arr(v, N);

  int to_find;
  i = 0;
  while (i++ < M) {
    scanf("%d\n", &to_find);
    // NÃO É PRA USA R BUSCA BINARIA
    printf("%d\n", binarysearch(to_find, v, 0, N-1));
  }
  
  return 0;
}