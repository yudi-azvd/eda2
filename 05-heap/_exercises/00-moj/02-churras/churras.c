#include <stdlib.h>
#include <stdio.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-pq
// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-pq

#define MAX_RESTAURANTS 100000
#define MAX_GRADE 1000000001

// #region
#define item_t int
#define key(a) (a)
#define less(a, b) (key(a) < key(b))
#define exch(a, b) \
  {                \
    item_t t = a;  \
    a = b;         \
    b = t;         \
  }

typedef struct PQ
{
  int size;
  int capacity;
  item_t *arr;
} PQ;

PQ *MinPQ_create(int max_N)
{
  PQ *pq = (PQ *)calloc(1, sizeof(PQ));
  pq->arr = (item_t *)calloc(max_N + 1, sizeof(item_t));
  pq->size = 0;
  pq->capacity = max_N;
  return pq;
}

void MinPQ_destroy(PQ *pq)
{
  free(pq->arr);
  free(pq);
}

void MinPQ_fix_up(PQ *pq, int k)
{
  item_t *v = pq->arr;
  while (k > 1 && less(v[k], v[k / 2]))
  {
    exch(v[k / 2], v[k]);
    k = k / 2;
  }
}

void MinPQ_fix_down(PQ *pq, int k)
{
  int j;
  item_t *v = pq->arr;
  int size = pq->size;
  while (k * 2 <= size)
  {
    j = k * 2;
    if (j < size && less(v[j + 1], v[j]))
      j++;
    if (!less(v[j], v[k]))
      break;
    exch(v[k], v[j]);
    k = j;
  }
}

void MinPQ_insert(PQ *pq, item_t item)
{
  if (pq->size + 1 >= pq->capacity)
  {
    pq->capacity *= 2;
    pq->arr = realloc(pq->arr, pq->capacity * sizeof(item_t));
  }

  pq->arr[++pq->size] = item;
  MinPQ_fix_up(pq, pq->size);
}

item_t MinPQ_del_min(PQ *pq)
{
  item_t item = pq->arr[1];
  pq->arr[1] = pq->arr[pq->size--];
  MinPQ_fix_down(pq, 1);
  return item;
}

int MinPQ_size(PQ *pq)
{
  return pq->size;
}

// #endregion

void print_mins(PQ* pq, int* grades, int n_restaurants, int n_friends) {
  int i, pq_size = MinPQ_size(pq);
  int interval_start = 0, interval_end = n_friends-1;

  while (interval_end < n_restaurants) {
    for (i = 0; i < n_friends; i++) {
      MinPQ_insert(pq, grades[interval_start+i]);
    }

    printf("%d ", MinPQ_del_min(pq));
    fflush(stdout);

    while (MinPQ_size(pq) > 0)
      MinPQ_del_min(pq);

    interval_end++;
    interval_start++;
  }
  

  printf("\n");
  
  /*
  min = PQ_peek_min()
  PQ_change_to(1, MAX_GRADE)
    fix_down(pq, 1)
  PQ_insert(next grade)

  if (deleted not in the end of interval)
    reinsert deleted
  
  */
}

int main() {
  PQ* pq = MinPQ_create(MAX_RESTAURANTS);
  int grades[MAX_RESTAURANTS] = {[0 ... MAX_RESTAURANTS-1] = 0};
  int i, n_restaurants, n_friends, grade;

  while (1) {
    scanf("%d %d", &n_restaurants, &n_friends);

    if (n_restaurants == 0 && n_friends == 0)
      break;

    for (i = 0; i < n_restaurants; i++) {
      scanf("%d", &grades[i]);
    }

    print_mins(pq, grades, n_restaurants, n_friends);
  }

  MinPQ_destroy(pq);
  return 0;
}
