
#ifndef PQ_H_INCLUDED
#define PQ_H_INCLUDED

#include <stdlib.h>

#define less(a, b) (a < b)

#define exch(a, b) { int t = a; a = b; b = t; }

typedef struct PQ {
  int size;
  int* arr;
} PQ;


PQ* PQ_create(int max_N) {
  PQ* pq = (PQ*) calloc(1, sizeof(PQ));
  pq->arr = (int*) calloc(max_N+1, sizeof(int));
  pq->size = 0;
  return pq;
}

void PQ_destroy(PQ* pq) {
  free(pq->arr);
  free(pq);
}

int PQ_empty(PQ* pq) {
  return pq->size == 0;
}


void PQ_fix_up(PQ* pq, int k) {
  int* v = pq->arr;
  while (k > 1 && less(v[k/2], v[k])) {
    exch(v[k/2], v[k]);
    k = k/2;
  }
}

void PQ_fix_down(PQ* pq, int k) {
  int j;
  int* v = pq->arr;
  int size = pq->size;
  while (k*2 <= size) {
    j = k*2;
    if (j < size && less(v[j], v[j+1])) j++;
    if (!less(v[k], v[j])) break;
    exch(v[k], v[j]);
    k = j;
  }
}

void PQ_insert(PQ* pq, int item) {
  pq->arr[++pq->size] = item;
  PQ_fix_up(pq, pq->size);
}

int PQ_del_max(PQ* pq) {
  int item = pq->arr[1];
  pq->arr[1] = pq->arr[pq->size--];
  PQ_fix_down(pq, 1);
  return item;
  // exch(pq->arr[1], pq->arr[--pq->size]);
  // PQ_fix_down(pq, 1);
  // return pq->arr[pq->size+1];
}


#endif // PQ_H_INCLUDED