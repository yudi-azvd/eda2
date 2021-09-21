#include <stdio.h>

#include "../../pq.h"

int main() {
  int max;
  char c;
  PQ* pq = PQ_create(20);

  while (scanf("%c", &c) != EOF) {
    if (c == '*') {
      max = PQ_del_max(pq);
      printf("%c\n", max);
    }
    else
      PQ_insert(pq, c);
  }

  PQ_destroy(pq);
}