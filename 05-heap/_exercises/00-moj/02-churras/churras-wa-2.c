#include <stdlib.h>
#include <stdio.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-pq
// https://br.spoj.com/problems/CHURRASC.pdf

#define MAX_RESTAURANTS 100000
#define MAX_GRADE 1000000001

// Essa PQIndexed é orientada a mínimo
// #region
#define item_t int
#define key(a) (a)
#define less(a, b) (key(a) < key(b))

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
  while (k > 1 && less(items[pq->pq[k]], items[pq->pq[k/2]])) {
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
    if (j < size && less(items[pq->pq[j+1]], items[pq->pq[j]])) j++;
    if (!less(items[pq->pq[j]], items[pq->pq[k]])) break;
    exch(pq, v[k], v[j]);
    k = j;
  }
}

int PQIndexed_del_min(PQIndexed* pq) {
  int index = pq->pq[1];
  exch(pq, pq->pq[1], pq->pq[pq->size--]);
  PQIndexed_fix_down(pq, 1);
  return index;
}

int PQIndexed_peek_min(PQIndexed* pq) {
  return pq->pq[1];
}

void PQIndexed_change(PQIndexed* pq, int k) {
  PQIndexed_fix_up(pq, pq->qp[k]);
  PQIndexed_fix_down(pq, pq->qp[k]);
}
// #endregion

// Essa PQIndexed é orientada a mínimo

void print_mins(int* grades, int n_restaurants, int n_friends) {
  PQIndexed* pq = PQIndexed_create(grades, n_restaurants+1);
  int i, min_grade_index;
  int interval_start = 0, interval_end = n_friends-1;

  for (i = 0; i < n_friends; i++) {
    PQIndexed_insert(pq, i);
  }

  while (interval_end < n_restaurants) {
    min_grade_index = PQIndexed_peek_min(pq);

    if (interval_end+1 == n_restaurants)
      printf("%d", grades[min_grade_index]);
    else
      printf("%d ", grades[min_grade_index]);

    grades[interval_start] = MAX_GRADE;
    PQIndexed_change(pq, interval_start);
    PQIndexed_insert(pq, ++interval_end);
    ++interval_start;
  }
  
  printf("\n");
  PQIndexed_destroy(pq);
}

int main() {
  // Essa PQIndexed é orientada a mínimo
  int i, n_restaurants, n_friends, grade;
  int grades[MAX_RESTAURANTS] = {[0 ... MAX_RESTAURANTS-1] = 0};

  while (1) {
    scanf("%d %d", &n_restaurants, &n_friends);

    if (n_restaurants == 0 && n_friends == 0)
      break;

    for (i = 0; i < n_restaurants; i++) {
      scanf("%d", &grades[i]);
    }

    print_mins(grades, n_restaurants, n_friends);
  }

  return 0;
}
