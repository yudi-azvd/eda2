// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-hash
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-hash/eleicao-ursal-big.html
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-hash/eleicao-ursal-big.pdf

// outra hash function pra dar uma olhada
// http://www.azillionmonkeys.com/qed/hash.html
// http://burtleburtle.net/bob/hash/doobs.html

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRESIDENTS_CAPACITY 101
#define SENATORS_CAPACITY 1013
#define DEPFEDS_CAPACITY 10177
#define DEPESTS_CAPACITY 100003
#define CANDIDATES_CAPACITY 17891

#define lessequal(A, B) (A.votes <= B.votes)
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

typedef struct candidate_t {
  int code;
  int votes;
} candidate_t;

int less(candidate_t a, candidate_t b) {
  if (a.votes == b.votes)
    return a.code < b.code;
  return a.votes < b.votes;
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

void mergesort_wrapper(
  candidate_t* v, 
  int lo, 
  int hi, 
  int (*cmp)(const void*, const void*)
) {
  candidate_t* aux = (candidate_t*) calloc(hi-lo+1, sizeof(candidate_t));
  mergesort(aux, v, lo, hi, cmp);
}

int cmpbyvotes_desc(const void* a, const void* b) {
  candidate_t* cand_a = (candidate_t*) a;
  candidate_t* cand_b = (candidate_t*) b;

  if (cand_a->votes == cand_b->votes)
    return cand_b->code - cand_a->code;
  return cand_b->votes - cand_a->votes;  
}

int type_of_candidate(int candidate_code) {
  // existe um fun????o matem??tica que faz isso sem esse tanto if, cara
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

void increment_candidate_votes_v2(candidate_t* candidates, int cand_code) {
  candidates[cand_code].code = cand_code;
  candidates[cand_code].votes++;
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

void print_winners(candidate_t* v, int n_eligible_winners) {
  int i = 0;
  for (; i < n_eligible_winners-1; i++)
    printf("%d ", v[i].code);
  printf("%d\n", v[i].code);
}

// stack size para o problema: 204800
//        stack size original: 8192
int main() {
  candidate_t presidents[PRESIDENTS_CAPACITY] 
    = {[0 ... PRESIDENTS_CAPACITY-1] = {0, 0}};
  candidate_t senators[SENATORS_CAPACITY] 
    = {[0 ... SENATORS_CAPACITY-1] = {0, 0}};
  candidate_t depfeds[DEPFEDS_CAPACITY] 
    = {[0 ... DEPFEDS_CAPACITY-1] = {0, 0}};
  candidate_t depests[DEPESTS_CAPACITY] 
    = {[0 ... DEPESTS_CAPACITY-1] = {0, 0}};
  candidate_t* candidates[4];
  candidates[0] = presidents;
  candidates[1] = senators;
  candidates[2] = depfeds;
  candidates[3] = depests;
  int n_eligible_senators, n_eligible_depfeds, n_eligible_depests;
  int candidate_code, type;
  int invalid_votes = 0;
  int valid_votes[4] = {
    0, // [0] president
    0, // [1] senator
    0, // [2] depfed
    0, // [3] depest
  };
  int sizes[4] = {
    0, // [0] president
    0, // [1] senator
    0, // [2] depfed
    0, // [3] depest
  };
  int capacities[4] = {
    PRESIDENTS_CAPACITY,
    SENATORS_CAPACITY,
    DEPFEDS_CAPACITY,
    DEPESTS_CAPACITY,
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
    increment_candidate_votes_v2(candidates[type], candidate_code);
  }

  
  printf("%d %d\n",
    valid_votes[0]+valid_votes[1]+valid_votes[2]+valid_votes[3],
    invalid_votes);
  print_president_winner(presidents, 99, valid_votes[0]);

  mergesort_wrapper(senators, 0, SENATORS_CAPACITY-1, &cmpbyvotes_desc);
  print_winners(senators, n_eligible_senators);

  mergesort_wrapper(depfeds, 0, DEPFEDS_CAPACITY-1, &cmpbyvotes_desc);
  print_winners(depfeds, n_eligible_depfeds);

  int depests_start_at = 1000;
  mergesort_wrapper(depests, 0, DEPESTS_CAPACITY-1, &cmpbyvotes_desc);
  print_winners(depests, n_eligible_depests);
}


/**
### Solu????o A

- v??rios arrays de candidatos (presidente, senador etc)
- guardar contador de votos v??lidos para cada tipo de candidato
- quando ler a entrada, atribua o voto para o tipo certo de candidato e 
  incremente o contador de votos v??lidos

- busca linear pelo presidente com mais votos
  determinar se ?? necess??rio o segundo turno

- quickselect para os S Senadores com maiores votos
  quicksort os S senadores

- quickselect para os F DepFed com maiores votos
  quicksort os F DepFed

- quickselect para os E DepEst com maiores votos
  quicksort os E DepEst
*/
