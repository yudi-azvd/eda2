// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-hash
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-hash/eleicao-ursal-big.html
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-hash/eleicao-ursal-big.pdf

// outra hash function pra dar uma olhada
// http://www.azillionmonkeys.com/qed/hash.html
// http://burtleburtle.net/bob/hash/doobs.html

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define CANDIDATES_CAPACITY 22307
// #define CANDIDATES_CAPACITY 17

typedef struct candidate_t {
  int code;
  int votes;
} candidate_t;

int less(candidate_t a, candidate_t b) {
  if (a.votes == b.votes)
    return a.code < b.code;
  return a.votes < b.votes;
}

#define exch(A, B) \
  {                \
    candidate_t tmp = A;  \
    A = B;         \
    B = tmp;       \
  }

#define cmpexch(A, B) \
  {                   \
    if (less(B, A))   \
      exch(A, B);     \
  }

void insertionsort(candidate_t *v,int l,int r) {
  for(int i = r; i > l; i--)
    cmpexch(v[i-i], v[i]);

  int j, tmp;
  for(int i = l + 2; i <= r; i++) {
    int j = i; candidate_t tmp = v[j];
    while(!less(tmp, v[j-1])) {
      v[j] = v[j-1];
      j--;
    }
    v[j] = tmp;
  }
}

void merge(
  candidate_t* aux, 
  candidate_t* v, 
  int lo, 
  int mid, 
  int hi,
  int (*cmp)(const void *, const void *)
) {
  int k = 0, i = lo, j = mid+1;
  // candidate_t* aux = (candidate_t*) calloc(hi2-lo+1, sizeof(candidate_t));
  aux = (candidate_t*) calloc(hi-lo+1, sizeof(candidate_t));

  while (i <= mid && j <= hi) {
    if ((*cmp)(&v[i], &v[j]) <= 0)
      aux[k++] = v[i++];
    else
      aux[k++] = v[j++];
  }

  while (i <= mid) {
    aux[k++] = v[i++];
  }

  while (j <= hi) {
    aux[k++] = v[j++];
  }

  // copiar para o vetor original
  k = 0;
  for (i = lo; i <= hi; ++i)
    v[i] = aux[k++];

  free(aux);  
}

void mergesort(
  candidate_t* aux,
  candidate_t* v, 
  int lo,
  int hi, 
  int (*cmp)(const void *, const void *)
) {
  if (lo >= hi) return;

  int mid = (lo+hi)/2;

  mergesort(aux, v, lo, mid, cmp);
  mergesort(aux, v, mid+1, hi, cmp);
  merge(aux, v, lo, mid, hi, cmp);
}


int cmpbyvotes_desc(const void* a, const void* b) {
  candidate_t* cand_a = (candidate_t*) a;
  candidate_t* cand_b = (candidate_t*) b;

  if (cand_a->votes == cand_b->votes)
    return cand_b->code - cand_a->code;
  return cand_b->votes - cand_a->votes;  
}

int cmpbycode(const void* a, const void* b) {
  candidate_t* cand_a = (candidate_t*) a;
  candidate_t* cand_b = (candidate_t*) b;

  // itens zerados têm os maiores valores
  if (cand_a->code == 0)
    return INT_MAX - cand_b->code;
  if (cand_b->code == 0)
    return cand_a->code - INT_MAX;
  return cand_a->code - cand_b->code;
}

int hash(int x) {
  return x % CANDIDATES_CAPACITY;
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

int sizes[4] = {0, 0, 0, 0};

void increment_candidate_votes(candidate_t* candidates, int cand_code) {
  int hashed_candidate = hash(cand_code),
    probe, code;

  for (probe = 0; probe < CANDIDATES_CAPACITY; probe++) {
    code = candidates[hashed_candidate].code;

    if (candidates[hashed_candidate].code == 0 || code == cand_code)
      break;

    hashed_candidate = (hashed_candidate+1) % CANDIDATES_CAPACITY;
  }

  if (probe >= CANDIDATES_CAPACITY) {
    printf("colors is full\n");
    exit(1);
  }

  int type = type_of_candidate(cand_code);
  int is_new_candidate = candidates[hashed_candidate].votes == 0;
  if (is_new_candidate)
    sizes[type]++;
  candidates[hashed_candidate].code = cand_code;
  candidates[hashed_candidate].votes++;
}

void print_votes(candidate_t* cands, int size) {
  for (size_t i = 0; i < size; i++) {
    if (cands[i].code != 0) {
      printf("[%d->%d] ", cands[i].code, cands[i].votes);
    }
  }
  printf("\n");
}

void print_president_winner(candidate_t* pres, int size, int valid_votes) {
  int i_max = 0;
  for (size_t i = 0; i < size; i++) {
    if (pres[i].code != 0 && pres[i].votes > pres[i_max].votes)
      i_max = i;
  } 
  double president_percentage_votes = pres[i_max].votes*1.0/valid_votes;
  if (president_percentage_votes > .51)
    printf("%d\n", pres[i_max].code);
  else
    printf("Segundo turno\n");
}

candidate_t* aux;

void sort_print_winners(candidate_t* candidates, int start, int size, int n_eligible_winners) {
  mergesort(aux, candidates, start, size-1, cmpbyvotes_desc);

  int i = start;
  for (; i < start+n_eligible_winners-1; i++)
    printf("%d ", candidates[i].code);
  printf("%d\n", candidates[i].code);
}


// stack size para o problema: 204800
//        stack size original: 8192
int main() {
  candidate_t candidates[CANDIDATES_CAPACITY] = 
    {[0 ... CANDIDATES_CAPACITY-1] = {0, 0}};
  int n_eligible_senators, n_eligible_depfeds, n_eligible_depests;
  int candidate_code, type, invalid_votes = 0;
  int valid_votes[4] = {
    0, // [0] president
    0, // [1] senator
    0, // [2] depfed
    0, // [3] depest
  };

  scanf("%d %d %d", 
    &n_eligible_senators, 
    &n_eligible_depfeds, 
    &n_eligible_depests);

  while (scanf("%d", &candidate_code) != EOF ) {
    type = type_of_candidate(candidate_code);
    if (type == -1) {
      invalid_votes++;
      continue;
    }

    valid_votes[type]++;
    increment_candidate_votes(candidates, candidate_code);
  }

  printf("%d %d\n",
    valid_votes[0]+valid_votes[1]+valid_votes[2]+valid_votes[3],
    invalid_votes);
  
  aux = (candidate_t*) calloc(CANDIDATES_CAPACITY-1, sizeof(candidate_t));
  mergesort(aux, candidates, 0, CANDIDATES_CAPACITY-1, &cmpbycode);
  // mergesort(aux, candidates, 0, CANDIDATES_CAPACITY-1, &cmpbyvotes_desc);

  // print_winners(candidates, sizes[0]+sizes[1]+sizes[2]+sizes[3]);
  print_president_winner(candidates, sizes[0], valid_votes[0]);
  int start = sizes[0];
  sort_print_winners(candidates, start, start+sizes[1], n_eligible_senators);
  start += sizes[1];
  sort_print_winners(candidates, start, start+sizes[2], n_eligible_depfeds);
  start += sizes[2];
  sort_print_winners(candidates, start, start+sizes[3], n_eligible_depests);

  free(aux);
}

/**
### Solução B - provavelmente vai para o ursal-big

- todos os candidatos ficam no mesmo vetor

- guardar contador de votos válidos para cada tipo de candidato
- guardar contador da qtd de cada tipo de candidato
- quando ler a entrada, atribua o voto para o tipo certo de candidato e
  incremente o respectivo contador de votos válidos,
  incremente o respectivo contador de tipo de candidato

- ordenar em ordem decrescente estavelmente pelo código do candidato
- ordenar em ordem decrescente estavelmente pela qtd de votos

// com os contadores de qtd de cada tipo de candidato, eu posso saber 
//   onde cada tipo de candidato começa no vetor

- selecionar o presidente com mais votos e determinar se é necessário um segundo turno
- selecionar os S Senadores com mais votos
- selecionar os F DepFed com mais votos
- selecionar os E DepEst com mais votos

*/