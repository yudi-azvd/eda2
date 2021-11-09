#include <stdio.h>
#include <stdlib.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-pq
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-pq/menores-placas.html

#define item_t int
#define key(a) (a)
#define less(a, b) (key(a) < key(b))
#define exch(a, b) { item_t t = a; a = b; b = t; }

typedef struct PQ {
  int size;
  int capacity;
  item_t* arr;
} PQ;


PQ* MinPQ_create(int max_N) {
  PQ* pq = (PQ*) calloc(1, sizeof(PQ));
  pq->arr = (item_t*) calloc(max_N+1, sizeof(item_t));
  pq->size = 0;
  pq->capacity = max_N;
  return pq;
}

void MinPQ_destroy(PQ* pq) {
  free(pq->arr);
  free(pq);
}

void MinPQ_fix_up(PQ* pq, int k) {
  item_t* v = pq->arr;
  while (k > 1 && less(v[k], v[k/2])) {
    exch(v[k/2], v[k]);
    k = k/2;
  }
}

void MinPQ_fix_down(PQ* pq, int k) {
  int j;
  item_t* v = pq->arr;
  int size = pq->size;
  while (k*2 <= size) {
    j = k*2;
    if (j < size && less(v[j+1], v[j])) j++;
    if (!less(v[j], v[k])) break;
    exch(v[k], v[j]);
    k = j;
  }
}

void MinPQ_insert(PQ* pq, item_t item) {
  if (pq->size+1 >= pq->capacity) {
    pq->capacity *= 2;
    pq->arr = realloc(pq->arr, pq->capacity*sizeof(item_t));
  }
  
  pq->arr[++pq->size] = item;
  MinPQ_fix_up(pq, pq->size);
}

item_t MinPQ_del_min(PQ* pq) {
  item_t item = pq->arr[1];
  pq->arr[1] = pq->arr[pq->size--];
  MinPQ_fix_down(pq, 1);
  return item;
}

int MinPQ_size(PQ* pq) {
  return pq->size;
}


void del_nsmallest_print_reinsert(PQ* pq, int n_smallest) {
  int i = 0;
  // o problema fala que n_smallest <= 100
  static int plaques[100];

  for (; i < n_smallest-1; i++) {
    plaques[i] = MinPQ_del_min(pq);
    printf("%d ", plaques[i]);
  }
  plaques[i] = MinPQ_del_min(pq);
  printf("%d\n", plaques[i]);

  for (i = 0; i < n_smallest; i++) {
    MinPQ_insert(pq, plaques[i]);
  }
}


int main() {
  int op, number, plaque, n_smallest;
  int pq_size = 0;
  const int INSERT = 1;
  PQ* pq = MinPQ_create(400);

  while (scanf("%d %d", &op, &number) != EOF) {
    if (op == INSERT) {
      plaque = number;
      MinPQ_insert(pq, plaque);
    }
    else {
      pq_size = MinPQ_size(pq);
      n_smallest = number > pq_size 
        ? pq_size
        : number;
      del_nsmallest_print_reinsert(pq, n_smallest);
    }
  }
  
  MinPQ_destroy(pq);
}
