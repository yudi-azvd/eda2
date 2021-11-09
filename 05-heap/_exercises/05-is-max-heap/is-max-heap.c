#include <stdio.h>
#include <stdlib.h>

int is_max_heap(int* array, int array_size) {
  int i = 2;
  for (; i <= array_size; i++) {
    if (array[i/2] < array[i])
      return 0;
  }
  
  return 1;
}

int main() {
  int i, array_size = 0;
  char c;
  int* array = NULL;

  scanf("%d\n", &array_size);
  array = calloc(array_size+1, sizeof(int));

  for (i = 1; i < array_size+1; i++) {
    scanf("%c ", &c);
    array[i] = c;
  }
  
  printf("is max heap = %d\n", is_max_heap(array, array_size));  
  free(array);

  return 0;
}