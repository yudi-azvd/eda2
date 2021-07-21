#include <stdio.h>

int main() {
  int i = 0, seven_counter = 0, b;
  char number[15]; number[0] = '\0';

  seven_counter = scanf("%15[77777777777777777]", number);

  printf("7 counter: %d\n", seven_counter);
  printf("   number: %s\n", number);

  return 0;
}