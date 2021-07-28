#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N 100
#define T 100

int main() {
  int n, n_original;
  int str_index = 0, counter_index = 0;
  int counters[N];
  char string[T];
  char c;

  scanf("%d", &n_original);
  n = n_original;

  while (n--) {
    scanf("%s", string);
    counters[counter_index] = 0;      
    
    for (str_index = 0; string[str_index] != '\0'; str_index++) {
      c = string[str_index];
      if (isdigit(c))
        counters[counter_index] += c - '0';
    }

    ++counter_index;
  }

  int i;
  for (i = 0; i < n_original; i++) {
    printf("%d\n", counters[i]);
  }
  
  return 0;
}