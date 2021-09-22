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


int quickselect(seed_t* v, int n, int lo, int hi) {
  int pivot = partition_by_score(v, lo, hi);

  if (pivot == n) 
    return pivot;

  if (pivot < n)
    return quickselect(v, n, pivot+1, hi);
  else
    return quickselect(v, n, lo, pivot-1);
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
  if (lo >= hi) return;

  exch(v, (lo+hi)/2, hi-1);
  cmp_by_code_exch(v, lo, hi-1);
  cmp_by_code_exch(v, lo, hi);
  cmp_by_code_exch(v, hi-1, hi); 
  
  int pivot = partition_by_code(v, lo, hi);
  quicksort_m3(v, lo, pivot-1);
  quicksort_m3(v, pivot+1, hi);
}


void print_arr(seed_t *v, int lo, int hi) {
  int i = lo;
  for (; i <= hi; ++i)
    printf("%lld %d\n", v[i].code, v[i].qlty_score);
}

#define less(a, b) (a.code < b.code)

#define max_size 10000000

// Restaurar o limite da pilha original:
// ulimit -s 8192

// Gerar arquivo de resposta. o número para o comando head está na primeira linha do arquivo de entrada
// cat 0.in | tail -n +2 | sort -k 2 -g | head -n 4 | sort -g
int main() {
  int select_how_many_seeds, i = 0;
  seed_t seeds[max_size];

  scanf("%d\n", &select_how_many_seeds);

  while (scanf("%lld %d\n", &seeds[i].code, &seeds[i].qlty_score) != EOF) {
    ++i;
  }

  int seeds_len = i;
  int index = quickselect(seeds, select_how_many_seeds-1, 0, seeds_len-1);
  quicksort_m3(seeds, 0, index);
  print_arr(seeds, 0, select_how_many_seeds-1);

  return 0;
}
