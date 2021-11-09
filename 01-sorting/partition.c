#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define less(A,B) ((A) < (B))
#define exch(A,B) { int t; t=A;A=B;B=t; }

void my_exch(int* v, int i, int j) {
  int t = v[i];
  v[i] = v[j];
  v[j] = t;
}


int separaCORMEM(int *v,int l,int r) {
  int pivot = v[r];
  int j = l;
  for(int i = l; i < r; i++)
    if(less(v[i], pivot)) {
      exch(v[i],v[j]);
      j++;
    }
  exch(v[j], v[r]);
  return j;
}


int partition(int *v,int lo, int hi) {
  int i = lo, pivot = v[hi], j = hi;
  while (i < j) {
    if (v[i] > pivot) {
      // --j;
      // exch(v[j], v[i]);
      my_exch(v, i, --j);
    }
    else {
      ++i;
    }
  }
  exch(v[j], v[hi]);
  return j;
}

void print_arr(int* arr, int size) {
  int i;
  for (i = 0; i < size-1; i++) 
    printf("%d ", arr[i]);
  printf("%d\n", arr[i]);
}


int main(int argc, char** argv) {
  int size = argc-1, i;
  int* numbers = calloc(size, sizeof(int));

  for (i = 0; i < size; i++) {
    numbers[i] = atoi(argv[i+1]);
  }

  print_arr(numbers, size);
  // int pivot_i = separaCORMEM(numbers, 0, size-1);
  int pivot_i = partition(numbers, 0, size-1);
  print_arr(numbers, size);
  printf("pivot %d at [%d]\n", numbers[pivot_i], pivot_i);

  free(numbers);
}