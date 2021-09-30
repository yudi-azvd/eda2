#include <stdio.h>
#include <stdlib.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-pq
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-pq/classificado-agronomia.html

typedef struct seed_t {
  long long unsigned code;
  int qlty_score;
} seed_t;


#define item_t seed_t
#define exch(a, b) { item_t t = a; a = b; b = t; }


typedef struct PQ {
  int size;
  int capacity;
  item_t* arr;
  int (*less)(item_t, item_t);
} PQ;


PQ* MinPQ_create(int max_N, int (*less)(item_t, item_t)) {
  PQ* pq = (PQ*) calloc(1, sizeof(PQ));
  pq->arr = (item_t*) calloc(max_N+1, sizeof(item_t));
  pq->size = 0;
  pq->capacity = max_N;
  pq->less = less;
  return pq;
}

void MinPQ_destroy(PQ* pq) {
  free(pq->arr);
  free(pq);
}

void MinPQ_fix_up(PQ* pq, int k) {
  item_t* v = pq->arr;
  while (k > 1 && (pq->less)(v[k], v[k/2])) {
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
    if (j < size && (pq->less)(v[j+1], v[j])) j++;
    if (!(pq->less)(v[j], v[k])) break;
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


int less_by_score(item_t a, item_t b) {
  if (a.qlty_score != b.qlty_score)
    return a.qlty_score < b.qlty_score;
  return a.code < b.code;
}

int less_by_code(item_t a, item_t b) {
  return a.code < b.code;
}

// Restaurar o limite da pilha original:
// ulimit -s 8192

// Gerar solução do problema:
// sol.py
int main() {
  int select_how_many_seeds, i = 0, tmp;
  int capacity = 1000;
  seed_t seed;
  PQ* pq_by_score = MinPQ_create(capacity, &less_by_score);

  scanf("%d\n", &select_how_many_seeds);
  PQ* pq_by_code = MinPQ_create(select_how_many_seeds, &less_by_code);

  while (scanf("%lld %d\n", &seed.code, &seed.qlty_score) != EOF) {
    MinPQ_insert(pq_by_score, seed);
    ++i;
  }

  int seeds_len = i;
  tmp = select_how_many_seeds;
  while (select_how_many_seeds--) {
    seed = MinPQ_del_min(pq_by_score);
    MinPQ_insert(pq_by_code, seed);
  }

  select_how_many_seeds = tmp;
  while (select_how_many_seeds--) {
    seed = MinPQ_del_min(pq_by_code);
    printf("%lld %d\n", seed.code, seed.qlty_score);
  }

  MinPQ_destroy(pq_by_score);
  MinPQ_destroy(pq_by_code);

  return 0;
}
