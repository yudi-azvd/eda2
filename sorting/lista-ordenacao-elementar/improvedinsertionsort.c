#include <stdio.h>


void improvedinsertionsort(int *v, int l, int h) {
  int i = 0, j, tmp, min = l;

  // o menor elemento fica em [0]
  for (i = h; i > l; --i) {
    if (v[i] < v[i-1]) {
      tmp = v[i];
      v[i] = v[i-1];
      v[i-1] = tmp;
    }
  }

  for (i = l+2; i <= h; ++i) {
    j = i; tmp = v[i];

    // não era pra precisar de "&& j>0"
    while (tmp < v[j-1] && j > 0) {
      v[j] = v[j-1]; --j;
    }
    v[j] = tmp;
  }
}


int main() {
  int v[50000], i = 0, n, size;

  while (scanf("%d", &n) != EOF) {
    v[i++] = n;
  }

  size = i;
  improvedinsertionsort(v, 0, size-1);

  for (i = 0; i < size-1; ++i)
    printf("%d ", v[i]);
  printf("%d\n", v[i]);

  return 0;
}