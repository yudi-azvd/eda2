#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define CANDIDATES_CAPACITY 22307

typedef struct candidate_t {
  int code;
  int votes;
} candidate_t;

#define item_t candidate_t

int less(candidate_t a, candidate_t b) {
  if (a.votes == b.votes)
    return a.code < b.code;
  return a.votes < b.votes;
}

void improvedinsertionsort(item_t *v, int l, int h) {
  int i = 0, j, min = l;
  item_t tmp;

  // o menor elemento fica em [0]
  for (i = h; i > l; --i) {
    // if (v[i] < v[i-1]) {
    if (less(v[i], v[i-1])) {
      tmp = v[i];
      v[i] = v[i-1];
      v[i-1] = tmp;
    }
  }

  for (i = l+2; i <= h; ++i) {
    j = i; tmp = v[i];

    while (less(tmp, v[j-1])) {
      v[j] = v[j-1]; --j;
    }
    v[j] = tmp;
  }
}

void exch(item_t* v, int i, int j) {
  item_t t = v[i];
  v[i] = v[j];
  v[j] = t;
}

void cmpexch(item_t* v, int i, int j) {
  if (less(v[j], v[i]))
    exch(v, i,  j);
}


int partition(item_t *v, int lo, int hi) {
  int i = lo, j = lo;
  item_t piv = v[hi];

  for (; i < hi; ++i)
    if (less(v[i], piv))
      exch(v, i, j++);
  exch(v, hi, j);
  return j;
}

void quickselect(item_t *v, int n_smallest, int lo, int hi) {
  if (lo >= hi) return;

  int piv = partition(v, lo, hi);
  if (piv > n_smallest)
    quickselect(v, n_smallest, lo, piv-1);
  if (piv < n_smallest)
    quickselect(v, n_smallest, piv+1, hi);
}


void quicksort_m3(item_t v[], int lo, int hi) {
  if (hi - lo <= 32) return;

  exch(v, (lo+hi)/2, hi-1);
  cmpexch(v, lo, hi-1);
  cmpexch(v, lo, hi);
  cmpexch(v, hi-1, hi);

  int piv = partition(v, lo, hi);
  quicksort_m3(v, lo, piv-1);
  quicksort_m3(v, piv+1, hi);
}


void quicksort_m3_insertion(item_t *v, int lo, int hi) {
  quicksort_m3(v, lo, hi);
  improvedinsertionsort(v, lo, hi);
}

int type_of_candidate(int candidate_code) {
  // existe um função matemática que faz isso sem esse tanto if, cara
  // log10(code)+1
  if (1 <= candidate_code && candidate_code <= 99)
    return 0; // president
  if (100 <= candidate_code && candidate_code <= 999)
    return 1; // senator
  if (1000 <= candidate_code && candidate_code <= 9999)
    return 2; // depfed
  if (10000 <= candidate_code && candidate_code <= 99999)
    return 3; // depest
  return -1;
}


int main() {
  candidate_t candidates[CANDIDATES_CAPACITY] 
    = {[0 ... CANDIDATES_CAPACITY-1] = {0, 0}};
  int cands[CANDIDATES_CAPACITY] 
    = {[0 ... CANDIDATES_CAPACITY-1] = 0};
  int n_eligible_senators, n_eligible_depfeds, n_eligible_depests;
  int candidate_code, type, i;
  int invalid_votes = 0;
  int valid_votes[4] = { // diz o tamanho de cada subarray de votos
    0, // [0] president
    0, // [1] senator
    0, // [2] depfed
    0, // [3] depest
  };

  scanf("%d %d %d", 
    &n_eligible_senators, 
    &n_eligible_depfeds, 
    &n_eligible_depests);

  i = 0;
  while (scanf("%d", &candidate_code) != EOF) {
    type = type_of_candidate(candidate_code);
    if (type == -1) {
      invalid_votes++;
      continue;
    }

    valid_votes[type]++;
    cands[i++] = candidate_code;
  }

  int total_votes = valid_votes[0]+valid_votes[1]+valid_votes[2]+valid_votes[3];
  printf("%d %d\n", total_votes, invalid_votes);

  quicksort_m3_insertion(candidates, 0, total_votes-1);
}