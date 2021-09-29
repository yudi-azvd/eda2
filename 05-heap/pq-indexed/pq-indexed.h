
#ifndef PQINDEXED_INDEXED_H_INCLUDED
#define PQINDEXED_INDEXED_H_INCLUDED

#include <stdlib.h>

typedef struct PQIndexed {
  int size, capacity;
  item_t* items;
  int *pq; // Fila de prioridades que armazena aos índice de um conj de item_t
           // item_t define a prioridade.
  int *qp; // Mantém a posição da heap para o elemento de índice k do conj de item_t,
           // funciona como uma hash.
} PQIndexed;
  
void exch(PQIndexed* pq, int i, int j) {
  int t = pq->qp[i];
  pq->qp[i] = pq->qp[j];
  pq->qp[j] = t;

  pq->pq[pq->qp[i]] = i;
  pq->pq[pq->qp[j]] = j;
}

PQIndexed* PQIndexed_create(item_t* items, int max_size) {
  PQIndexed* pq = (PQIndexed*) calloc(1, sizeof(PQIndexed));
  pq->size = 0;
  pq->capacity = max_size;
  pq->items = items;
  pq->pq = (int*) calloc(max_size+1, sizeof(int));
  pq->qp = (int*) calloc(max_size+1, sizeof(int));
  return pq;
}

void PQIndexed_destroy(PQIndexed* pq) {
  free(pq->pq);
  free(pq->qp);
  free(pq);
}

int PQIndexed_empty(PQIndexed* pq) {
  return pq->size == 0;
}

void PQIndexed_fix_up(PQIndexed* pq, int k) {
  int* v = pq->pq;
  item_t* items = pq->items;
  while (k > 1 && less(items[pq->pq[k/2]], items[pq->pq[k]])) {
    exch(pq, v[k], v[k/2]);
    k = k/2;
  }
}

void PQIndexed_insert(PQIndexed* pq, int k) {
  pq->qp[k] = ++pq->size;
  pq->pq[pq->size] = k;
  PQIndexed_fix_up(pq, pq->size);
}

void PQIndexed_fix_down(PQIndexed* pq, int k) {
  int j;
  int* v = pq->pq;
  item_t* items = pq->items;
  int size = pq->size;
  while (k*2 <= size) {
    j = k*2;
    if (j < size && less(items[pq->pq[j]], items[pq->pq[j+1]])) j++;
    if (!less(items[pq->pq[k]], items[pq->pq[j]])) break;
    exch(pq, v[k], v[j]);
    k = j;
  }
}

int PQIndexed_del_max(PQIndexed* pq) {
  int index = pq->pq[1];
  pq->pq[1] = pq->pq[pq->size--];
  pq->pq[pq->size+1] = 0;
  PQIndexed_fix_down(pq, pq->pq[1]);
  // PQIndexed_fix_down(pq, 1);
  return index;
}

void PQIndexed_change(PQIndexed* pq, int k) {
  PQIndexed_fix_up(pq, pq->qp[k]);
  PQIndexed_fix_down(pq, pq->qp[k]);
}

#endif // PQINDEXED_INDEXED_H_INCLUDED