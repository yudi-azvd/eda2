#include <stdio.h>

/*
struct item {
  int number;
  bool is_sum_remanescent;
}

item itens[100] ....
if (itens[0].is_sum_remanescent)
  ...
*/

int main() {
  int subsequence_sum_limit, new_number;
  int numbers[100];
  int number_index = 0, numbers_len ;

  while (scanf("%d", &new_number)) {
    if (new_number == 0)
      break;
    
    numbers[number_index++] = new_number;
  }

  numbers_len = number_index;

  scanf("%d\n", &subsequence_sum_limit);

  // sum_remanecent = get_sum_remanescent(numbers, start, end, sum_limit);
  return 0;
}