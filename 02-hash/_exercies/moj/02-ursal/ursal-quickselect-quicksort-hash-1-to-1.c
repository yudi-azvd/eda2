// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-hash
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-hash/eleicao-ursal-big.html
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-hash/eleicao-ursal-big.pdf

// outra hash function pra dar uma olhada
// http://www.azillionmonkeys.com/qed/hash.html
// http://burtleburtle.net/bob/hash/doobs.html

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRESIDENTS_CAPACITY 100
#define SENATORS_CAPACITY 1000
#define DEPFEDS_CAPACITY 10000
#define DEPESTS_CAPACITY 100000

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

int partition(candidate_t *v, int lo, int hi) {
  candidate_t c = v[hi];
  int j = lo;
  for (int k = lo; k < hi; k++) {
    if (!less(v[k], c)) {
      exch(v[k], v[j]);
      j++;
    }
  }

  exch(v[j], v[hi]);
  return j;
}

void quicksort(candidate_t* v, int lo, int hi) {
  if (lo >= hi) return;
  int piv = partition(v, lo, hi);
  quicksort(v, lo, piv-1);
  quicksort(v, piv+1, hi);
}

void quickselect(candidate_t *v, int n_smallest, int lo, int hi) {
  if (lo >= hi) return;

  int piv = partition(v, lo, hi);
  if (piv > n_smallest)
    quickselect(v, n_smallest, lo, piv-1);
  if (piv < n_smallest)
    quickselect(v, n_smallest, piv+1, hi);
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
    // increment_candidate_votes(candidates[type], candidate_code, capacities[type]);
    increment_candidate_votes_v2(candidates[type], candidate_code);
  }

  
  printf("%d %d\n",
    valid_votes[0]+valid_votes[1]+valid_votes[2]+valid_votes[3],
    invalid_votes);
  // print_president_winner(presidents, PRESIDENTS_CAPACITY, valid_votes[0]);
  print_president_winner(presidents, 99, valid_votes[0]);

  quickselect(senators, n_eligible_senators, 0, SENATORS_CAPACITY-1);
  quicksort(senators, 0, n_eligible_senators-1);
  print_winners(senators, n_eligible_senators);
  // free(aux);

  quickselect(depfeds, n_eligible_depfeds, 0, DEPFEDS_CAPACITY-1);
  quickselect(depfeds, n_eligible_depfeds, 0, 9999);
  quicksort(depfeds, 0, n_eligible_depfeds-1);
  print_winners(depfeds, n_eligible_depfeds);

  int depests_start_at = 0;
  // quickselect(depests, n_eligible_depests, depests_start_at, DEPESTS_CAPACITY-1);
  quicksort(depests, depests_start_at, DEPESTS_CAPACITY-1);
  print_winners(depests, n_eligible_depests);
}


/**
### Solução A

- vários arrays de candidatos (presidente, senador etc)
- guardar contador de votos válidos para cada tipo de candidato
- quando ler a entrada, atribua o voto para o tipo certo de candidato e 
  incremente o contador de votos válidos

- busca linear pelo presidente com mais votos
  determinar se é necessário o segundo turno

- quickselect para os S Senadores com maiores votos
  quicksort os S senadores

- quickselect para os F DepFed com maiores votos
  quicksort os F DepFed

- quickselect para os E DepEst com maiores votos
  quicksort os E DepEst
*/
