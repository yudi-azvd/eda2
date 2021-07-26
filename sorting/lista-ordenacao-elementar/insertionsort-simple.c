#include <stdio.h>


void insertionsort(int *v, int l, int h) {
  int i=0, j, tmp, min = l;

  for (i = l+1; i <= h; ++i) {
    for (j = i; v[j] < v[j-1] && j > 0; --j) {
      tmp = v[j];
      v[j] = v[j-1];
      v[j-1] = tmp;
    }
  }
}


int main() {
  int v[1000], i = 0, n, size;

  while (scanf("%d", &n) != EOF) {
    v[i++] = n;
  }

  size = i;
  insertionsort(v, 0, size-1);

  for (i = 0; i < size-1; ++i)
    printf("%d ", v[i]);
  printf("%d\n", v[i]);

  return 0;
}