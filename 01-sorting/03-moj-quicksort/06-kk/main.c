#include <stdio.h>

#define SIZE 1000

int main() {
  int n, p, x, i = 0;
  int v[SIZE] = {[0 ... SIZE-1] = 0};

  scanf("%d %d %d", &n, &p, &x);

  while (i < n) {
    scanf("%d", v[i++]);
  }
  
  return 0;
}