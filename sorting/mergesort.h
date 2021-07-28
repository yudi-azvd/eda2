#ifndef MERGESORT_H_INCLUDED
#define MERGESORT_H_INCLUDED

#include <stdlib.h>
#include "convention.h"

// [lo .. hi1-1] [hi1 .. hi2]
void merge(Item* v, int lo, int hi1, int hi2) {
  int k = 0, i = lo, j = hi1+1;
  Item* aux = (Item*) calloc(hi2-lo+1, sizeof(Item));

  // while (i <= hi1 || j <= hi2) {
  while (i <= hi1 && j <= hi2) {
    // if (i > hi1)         // 1o vetor esgotou
    //   aux[k++] = v[j++]; // copiar o restinho do 2o vetor
    // else if (j > hi2)    // 2o vetor esgotou
    //   aux[k++] = v[i++]; // copiar o restinho do 1o vetor

    // else
     if (less(v[i], v[j])) // less(v[i], v[j])
      aux[k++] = v[i++];
    else
      aux[k++] = v[j++];
  }

  while (i <= hi1) {
    aux[k++] = v[i++];
  }

  while (j <= hi2) {
    aux[k++] = v[j++];
  }

  // copiar para o vetor original
  k = 0;
  for (i = lo; i <= hi2; ++i)
    v[i] = aux[k++];

  free(aux);  
}


void mergesort(Item* v, int lo, int hi) {
  if (lo >= hi) return;

  int mid = (lo+hi)/2;

  mergesort(v, lo, mid);
  mergesort(v, mid+1, hi);
  merge(v, lo, mid, hi);
}


#endif // MERGESORT_H_INCLUDED