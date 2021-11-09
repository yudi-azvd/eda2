#include <stdio.h>

void print_arr(int* a, int size) {
  int i = 0;
  for (; i < size-1; i++)
    printf("%d ", a[i]);
  printf("%d\n", a[i]);
}


int binarysearch_modified(int to_find, int* v, int lo, int hi) {
  int mid = (lo + hi)/2;

  while (lo <= hi) {
    if (v[mid] < to_find)
      lo = mid+1;
    else if (to_find < v[mid])
      hi = mid-1;
    else
      return mid;

    mid = (lo + hi)/2;
  }

  if (v[mid] < to_find)
    ++mid;

  return mid;
}


int main() {
  int i = 0, N, M, v[100000];

  scanf("%d %d\n", &N, &M);

  while (i < N) {
    scanf("%d\n", &v[i++]);
  }

  int to_find;
  i = 0;
  while (i++ < M) {
    scanf("%d", &to_find);
    printf("%d\n", binarysearch_modified(to_find, v, 0, N-1));
  }
  
  return 0;
}