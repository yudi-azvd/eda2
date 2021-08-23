#include <stdio.h>


#define less(a, b) (a < b)


void exch(int* v, int i, int j) {
  int t = v[i];
  v[i] = v[j];
  v[j] = t;
}

void cmpexch(int* v, int i, int j) {
  if (v[i] < v[j])
    exch(v, i,  j);
}


int partition(int *v, int lo, int hi) {
  int i = lo, j = lo, piv = v[hi];

  for (; i < hi; ++i)
    if (v[i] < piv)
      exch(v, i, j++);
  exch(v, hi, j);
  return j;
}


void quicksort_m3(int v[], int lo, int hi) {
  if (lo >= hi) return;

  exch(v, (lo+hi)/2, hi-1);
  cmpexch(v, lo, hi-1);
    cmpexch(v, lo, hi);
      cmpexch(v, hi-1, hi);

  int piv = partition(v, lo, hi);
  quicksort_m3(v, lo, piv-1);
  quicksort_m3(v, piv+1, hi);
}


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

    while (tmp < v[j-1]) {
      v[j] = v[j-1]; --j;
    }
    v[j] = tmp;
  }
}



void quicksort_m3_insertion(int *v, int lo, int hi) {
  quicksort_m3(v, lo, hi);
  improvedinsertionsort(v, lo, hi);
}



void print_arr(int *v, int lo, int hi) {
  int i = lo;
  for (; i < hi; ++i)
    printf("%d ", v[i]);
  printf("%d\n", v[i]);
}



#define size 100000

int main() {
  int v[size], i = 0, n;

  scanf("%d", &n);

  while (n--)
    scanf("%d ", &v[i++]);
  int v_size = i;

  quicksort_m3_insertion(v, 0, v_size-1);
  print_arr(v, 0, v_size-1);

  return 0;
}