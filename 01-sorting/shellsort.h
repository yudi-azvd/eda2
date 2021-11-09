#ifndef SHELLSORT_H_INCLUDED
#define SHELLSORT_H_INCLUDED

#include "convention.h"

void insertionsort_gap(Item *v, int lo, int hi, int gap_size) {
  int i, j;
  for (i = lo+gap_size; i <= hi; ++i) {
    j = i; Item tmp = v[i];
    while (j >= lo+gap_size && less(tmp, v[j-gap_size])) {
      v[j] = v[j-gap_size]; j -= gap_size;
    }
    v[j] = tmp;
  }
}

void shellshort(Item* v, int lo, int hi) {
  int gap_size;
  for (gap_size = 1; gap_size <= (hi-lo)/9; gap_size = 3*gap_size+1)
    for (; gap_size > 0; gap_size = gap_size / 3)
      insertionsort_gap(v, lo, hi, gap_size);
}


#endif // SHELLSORT_H_INCLUDED