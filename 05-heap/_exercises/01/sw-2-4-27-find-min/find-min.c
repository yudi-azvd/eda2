#include <stdio.h>

#define MAX_STUDENTS 10

// https://www.ime.usp.br/~pf/estruturas-de-dados/aulas/priority.html

#include "pq.h"

int PQ_find_min(PQ* pq) {
  int size = pq->size;
  if (size == 1)
    return pq->arr[1];
  
  int min = pq->arr[size] < pq->arr[size-1] 
    ? pq->arr[size]
    : pq->arr[size-1];
  return min;
}

int main() {
  int n, min;
  PQ* pq = PQ_create(MAX_STUDENTS);

  while (scanf("%d", &n) != EOF) {
    PQ_insert(pq, n);
  }

  printf("%d\n", PQ_find_min(pq));

  PQ_destroy(pq);
  return 0;
}