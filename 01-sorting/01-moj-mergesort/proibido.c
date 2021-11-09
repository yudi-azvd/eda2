#include <stdio.h>
#include <stdlib.h>

#define V_SIZE 140000


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
  int i, n, to_find;
  int v[V_SIZE];

  scanf("%d", &n);

  while (i < n) {
    scanf("%d", &v[i++]);
  }

  mergesort(v, 0, n-1);

  while (scanf("%d", &to_find) != EOF) 
    printf("%s\n", 
      binarysearch(to_find, v, 0, n-1) == -1 ? "nao" : "sim");
    
  return 0;
}