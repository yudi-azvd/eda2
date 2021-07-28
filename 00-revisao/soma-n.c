#include <stdio.h>

int main() {
  int accumulator = 0, new_int;
  int n;
  scanf("%d", &n);

  while (n--) {
    scanf("%d", &new_int);
    accumulator += new_int;
  }
  
  printf("%d\n", accumulator);
  return 0;
}