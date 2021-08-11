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
  return i;
}

void quicksort_naive(Item *v, int lo, int hi) {
  if (lo >= hi) return;

  int pivot = partition(v, lo, hi);
  quicksort_naive(v, lo, pivot-1);
  quicksort_naive(v, pivot+1, hi);
}


#endif // QUICKSORT_H_INCLUDED