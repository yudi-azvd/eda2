#ifndef SHELLSORT_H_INCLUDED
#define SHELLSORT_H_INCLUDED

#include "convention.h"

void insertionsort_interval(Item *v, int lo, int hi, int interval_sz) {
  int i, j;
  for (i = lo+interval_sz; i <= hi; ++i) {
    j = i; Item tmp = v[i];
    while (j >= lo+interval_sz && less(tmp, v[j-interval_sz])) {
      v[j] = v[j-interval_sz]; j -= interval_sz;
    }
    v[j-interval_sz] = tmp;
  }
}

void shellshort(Item* v, int lo, int hi) {
  int interval_sz = 0;

  for (interval_sz = 1; interval_sz <= (hi-lo)/9; interval_sz = 3*interval_sz+1)
    for (; interval_sz > 0; interval_sz = interval_sz / 3)
      insertionsort_interval(v, lo, hi, interval_sz);
}


#endif // SHELLSORT_H_INCLUDED