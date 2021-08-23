#ifndef QUICKSORT_H_INCLUDED
#define QUICKSORT_H_INCLUDED

#include "convention.h"


// Em shell é possível testar a função assim
// echo "6 30 40 80 20 10 25" | ./a.out 
int partition(Item *v, int lo, int hi) {
  int i = lo, j = lo, pivot = v[hi];

  for (; i < hi; ++i)
    if (less(v[i], pivot))
      exch(v[i], v[j++]);
  exch(v[hi], v[j]);
  return j;
}


void quicksort_naive(Item *v, int lo, int hi) {
  if (lo >= hi) return;

  int pivot = partition(v, lo, hi);
  quicksort_naive(v, lo, pivot-1);
  quicksort_naive(v, pivot+1, hi);
}


void quicksort_m3(Item *v, int lo, int hi) {
  if (lo >= hi) return;

  cmpexch(v[(lo+hi)/2], v[hi]);
    cmpexch(v[lo], v[(lo+hi)/2]);
      cmpexch(v[hi], v[(lo+hi)/2]); 

  int pivot = partition(v, lo, hi);
  quicksort_m3(v, lo, pivot-1);
  quicksort_m3(v, pivot+1, hi);
}


// seleciona o n-ésimo item menor do vetor
int quickselect(Item* v, int n, int lo, int hi) {
  int pivot = partition(v, lo, hi);

  if (pivot == n) 
    return pivot;

  if (pivot < n)
    return quickselect(v, n, pivot+1, hi);
  else
    return quickselect(v, n, lo, pivot-1);
}


#endif // QUICKSORT_H_INCLUDED