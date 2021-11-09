#include <stdio.h>

int count_seven(char *number, int index, int current_seven_count);


int main() {
  int i = 0, sevens;
  char number[15];

  scanf("%s", number);

  printf("%d\n", count_seven(number, 0, 0));

  return 0;
}


int count_seven(char *number, int index, int current_seven_count) {
  if (number[index] == '\0')
    return current_seven_count;
  current_seven_count += number[index++] == '7';
  return count_seven(number, index, current_seven_count);
}