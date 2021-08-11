#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <stdio.h>

#include "convention.h"

void print_arr(Item *v, int lo, int hi) {
  int i = lo;
  for (; i < hi; ++i)
    printf("%d ", v[i]);
  printf("%d\n", v[i]);
}


#endif // UTIL_H_INCLUDED