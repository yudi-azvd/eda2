#ifndef SELECTIONSORT_H_INCLUDED
#define SELECTIONSORT_H_INCLUDED

#include "convention.h"

// Selection sort recursivo.
void selectionsort_r(Item* v, int l, int h) {
  if (l >= h) return;
  
  int j, min = l;

  for (j = l+1; j <= h; ++j)
    if (less(v[j], v[min]))
      min = j;

  exch(v[min], v[l]);
  selectionsort_r(v, l+1, h);
}


// Selection sort normal.
void selectionsort(Item* v, int l, int h) {
  int i, j, min;

  for (i = l; i <= h; ++i) {
    min = i;
    for (j = i+1; j <= h; ++j)
      if (less(v[j], v[min]))
        min = j;

    exch(v[min], v[i]);
  }
}

#endif // SELECTIONSORT_H_INCLUDED