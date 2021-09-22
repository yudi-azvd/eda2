#include <stdio.h>
#include <stdlib.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-quicksort
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-quicksort/classificado-agronomia.html


typedef struct seed_t {
  long long unsigned code;
  int qlty_score;
} seed_t;


void exch(seed_t* v, int i, int j) {
  seed_t t = v[i];
  v[i] = v[j];
  v[j] = t;
}

void improvedinsertionsort(seed_t *v, int l, int h) {
  int i = 0, j, min = l;
  seed_t tmp;

  // o menor elemento fica em [0]
  for (i = h; i > l; --i) {
    if (v[i].code < v[i-1].code) {
      tmp = v[i];
      v[i] = v[i-1];
      v[i-1] = tmp;
    }
  }

  for (i = l+2; i <= h; ++i) {
    j = i; tmp = v[i];

    while (tmp.code < v[j-1].code) {
      v[j] = v[j-1]; --j;
    }
    v[j] = tmp;
  }
}



void cmp_by_code_exch(seed_t* v, int i, int j) {
  if (v[i].code < v[j].code)
    exch(v, i,  j);
}


int partition_by_score(seed_t *v, int lo, int hi) {
  int i, j = lo, pivot = v[hi].qlty_score;

  for ( i = lo; i < hi; ++i) {
    if (v[i].qlty_score < pivot || (v[i].qlty_score == pivot && v[i].code < v[hi].code)) {
      exch(v, i, j++);
    }
  }
  exch(v, hi, j);
  return j;
}


int quickselect_r(seed_t* v, int n, int lo, int hi) {
  int pivot = partition_by_score(v, lo, hi);

  if (pivot == n) 
    return pivot;

  if (pivot < n)
    return quickselect_r(v, n, pivot+1, hi);
  else
    return quickselect_r(v, n, lo, pivot-1);
}


int quickselect_i(seed_t* v, int n, int lo, int hi) {

  int pivot = -1;
  while (pivot != n) {
    pivot = partition_by_score(v, lo, hi);
    
    if (pivot < n)
      lo = pivot + 1;
    else
      hi = pivot - 1;
  }

  return pivot;

  // int pivot_index;
  // while (lo <= hi) {
  //   pivot_index = partition_by_score(v, lo, hi);

  //   if (pivot_index == n)
  //     return pivot_index;
  //   if (pivot_index > n)
  //     hi = pivot_index - 1;
  //   else
  //     lo = pivot_index + 1;
  // }

  // return -1;  
}


int partition_by_code(seed_t *v, int lo, int hi) {
  int i = lo, j = lo, pivot = v[hi].code;

  for (; i < hi; ++i)
    if (v[i].code < pivot)
      exch(v, i, j++);
  exch(v, hi, j);
  return j;
}


void quicksort_m3(seed_t *v, int lo, int hi) {
  if (hi - lo <= 32) return;

  exch(v, (lo+hi)/2, hi-1);
  cmp_by_code_exch(v, lo, hi-1);
  cmp_by_code_exch(v, lo, hi);
  cmp_by_code_exch(v, hi-1, hi); 
  
  int pivot = partition_by_code(v, lo, hi);
  quicksort_m3(v, lo, pivot-1);
  quicksort_m3(v, pivot+1, hi);
}

void quicksort_m3_insertion(seed_t *v, int lo, int hi) {
  quicksort_m3(v, lo, hi);
  improvedinsertionsort(v, lo, hi);
}



void print_arr(seed_t *v, int lo, int hi) {
  int i = lo;
  for (; i <= hi; ++i)
    printf("%lld %d\n", v[i].code, v[i].qlty_score);
}

#define less(a, b) (a.code < b.code)

// #define max_size 10000000

// Restaurar o limite da pilha original:
// ulimit -s 8192

// Gerar arquivo de resposta. 
// IMPORTANTE: o número para o comando head está na primeira linha do arquivo de entrada
// cat samples/0.in | tail -n +2 | sort -k 2 -g | head -n 4 | sort -g
int main() {
  int select_how_many_seeds, i = 0;
  int capacity = 1000;
  seed_t* seeds = malloc(capacity*sizeof(seed_t));

  scanf("%d\n", &select_how_many_seeds);

  while (scanf("%lld %d\n", &seeds[i].code, &seeds[i].qlty_score) != EOF) {
    if (i+1 >= capacity) {
      capacity *= 2;
      seeds = realloc(seeds, capacity*sizeof(seed_t));
    }

    ++i;
  }

  int seeds_len = i;
  int index = quickselect_i(seeds, select_how_many_seeds-1, 0, seeds_len-1);
  quicksort_m3_insertion(seeds, 0, index);
  print_arr(seeds, 0, select_how_many_seeds-1);

  free(seeds);

  return 0;
}
