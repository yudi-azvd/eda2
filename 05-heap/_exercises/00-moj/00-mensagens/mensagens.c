#include <stdio.h>
#include <stdlib.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-pq
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-pq/mensagens.html

#define HT_MAX_CAPACITY 2147483648

typedef struct packet_t {
  int id;
  char letter;
} packet_t;


#define item_t packet_t
#define key(a) (a.id)
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

#define ABSENT '\0'
#define PRESENT '1'

// original stack size = 8192
int main() {
  int max_size = 400;
  // char pkt_ids_ht[HT_MAX_CAPACITY] = {[0 ... HT_MAX_CAPACITY-1] = ABSENT};
  // char pkt_ids_ht[HT_MAX_CAPACITY];
  char* pkt_ids_ht = calloc(HT_MAX_CAPACITY, sizeof(char));
  PQ* pq = MinPQ_create(max_size);
  packet_t pkt, last_pkt = {-1, '\0'};

  while (scanf("%d %c", &pkt.id, &pkt.letter) != EOF) {
    if (pkt_ids_ht[pkt.id] == ABSENT) {
      pkt_ids_ht[pkt.id] = PRESENT;
      MinPQ_insert(pq, pkt);
    }
  }

  int approx_message_size = MinPQ_size(pq);
  char* message = calloc(approx_message_size+1, sizeof(char));
  char letter;

  int i = 0;
  while (MinPQ_size(pq) > 0) {
    pkt = MinPQ_del_min(pq);

    if (pkt.id != last_pkt.id) {
      message[i++] = pkt.letter;
      last_pkt = pkt;
    }
  }
  message[i] = '\0';
  printf("%s\n", message);
  free(message);

  MinPQ_destroy(pq);
  return 0;
}
