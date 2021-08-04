#include <stdio.h>


void bubblesort(int *v, int size) {
  int i, j, tmp;

  for (i = 0; i < size; i++) {
    for (j = 1; j < size; ++j) {
      if (v[j] < v[j-1]) {
        tmp = v[j];
        v[j] = v[j-1];
        v[j-1] = tmp;
      }
    }
  }
}

int main() {
  int v[1000], i = 0, n, size;

  while (scanf("%d", &n) != EOF) {
    v[i++] = n;
  }

  size = i;
  bubblesort(v, size);

  for (i = 0; i < size; ++i)
    printf("%d ", v[i]);

  return 0;
}