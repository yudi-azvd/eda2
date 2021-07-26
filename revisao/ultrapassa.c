#include <stdio.h>
#include <stdint.h>

#define SIZE 1000000


typedef struct item_t {
  int number;
  uint8_t is_sum_remanescent;
} item_t;


int get_sum_remanescent_index(int numbers[], int start, int size, int sum_limit) {
  int i, partial_sum = 0;

  for (i = start; i < size; ++i) {
    if (partial_sum < sum_limit)
      partial_sum += numbers[i];
    else
      return i-1;
  }

  return i;
}


void print_remanescents_backwards(int* remanescents, int size) {
  int i;
  for (i = size-1; i >= 0; --i)
    printf("%d\n", remanescents[i]);
}


int main() {
  int sum_limit, new_number;
  int numbers[SIZE], remanescents[SIZE];
  int i = 0, numbers_len;

  while (scanf("%d", &new_number)) {
    if (new_number == 0)
      break;
    
    numbers[i++] = new_number;
  }

  numbers_len = i;

  scanf("%d\n", &sum_limit);

  int start = 0, rem_index, remanescents_len = 0; 
  while (1) {
    rem_index = get_sum_remanescent_index(numbers, start, numbers_len, sum_limit);
    start = rem_index + 1;

    if (start >= numbers_len)
      break;

    remanescents[remanescents_len] = numbers[rem_index];
    ++remanescents_len;
  }

  print_remanescents_backwards(remanescents, remanescents_len);

  return 0;
}