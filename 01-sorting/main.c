#include <stdio.h>
#include <stdlib.h>

#include "convention.h"
#include "selectionsort.h"
#include "shellsort.h"
#include "mergesort.h"

int main() {
  int t;
  
  scanf("%d",&t);
  Item *v = malloc(t*sizeof(Item));

  for(int i = 0; i < t; i++)
    scanf("%d", &v[i]);

  // selectionsort_r(v,0,t-1);
  // selectionsort(v,0,t-1);
  // shellshort(v,0,t-1);
  mergesort(v, 0, t-1);

  // for(int i=0;i<t;i++)
  //   r = printf("%d\n",v[i]);
  printf("is sorted: %d\n", issorted(v, t));
  return 0;
}
