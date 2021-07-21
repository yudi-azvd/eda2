#include <stdio.h>

int main() {
  int i = 0, seven_counter = 0;
  char number[15];

  scanf("%s", number);

  while (number[i++] != '\0') {
    if (number[i] == '7') {
      ++seven_counter;
    }
  }

  /* talvez 13 if's, um pra cada caractere */

  printf("%d\n", seven_counter+1);

  return 0;
}