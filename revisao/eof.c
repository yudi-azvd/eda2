#include <stdio.h>

int main() {
  int numbers_count = 0;

  while (scanf("%*d") != EOF) {
    ++numbers_count;
  }
  
  printf("%d\n", numbers_count);
  return 0;
}