#include <stdio.h>


void selectionsort_r(int *v, int l, int h) {
  if (l >= h) return;

  int i, j, tmp, min = l;

  for (j = l+1; j <= h; ++j) {
    if (v[j] < v[min]) {
      min = j;
    }
  }

  tmp = v[min];
  v[min] = v[l];
  v[l] = tmp;

  selectionsort_r(v, l+1, h);
}


void selectionsort(int *v, int l, int h) {
  int i, j, tmp, min = l;

  for (i = l; i <= h; ++i) {
    min = i;
    for (j = i; j <= h; ++j) {
      if (v[j] < v[min]) {
        min = j;
      }
    }

    tmp = v[min];
    v[min] = v[i];
    v[i] = tmp;
  }
}


int main() {
  int v[1000], i = 0, n, size;

  while (scanf("%d", &n) != EOF) {
    v[i++] = n;
  }

  size = i;
  selectionsort(v, 0, size-1);

  for (i = 0; i < size-1; ++i)
    printf("%d ", v[i]);
  printf("%d\n", v[i]);

  return 0;
}