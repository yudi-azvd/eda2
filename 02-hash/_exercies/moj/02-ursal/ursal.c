// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-hash
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-hash/eleicao-ursal-big.html
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-hash/eleicao-ursal-big.pdf

// outra hash function pra dar uma olhada
// http://www.azillionmonkeys.com/qed/hash.html

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRESIDENT_INITIAL_CAPACITY 17477
#define SENATOR_INITIAL_CAPACITY 17477
#define DEPFED_INITIAL_CAPACITY 17477
#define DEPEST_INITIAL_CAPACITY 17477
#define CANDIDATES_CAPACITY 17477

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

void print_winners(candidate_t* v, int n_eligible_winners) {
  int i = 0;
  for (; i < n_eligible_winners-1; i++)
    printf("%d ", v[i].code);
  printf("%d\n", v[i].code);
}

// stack size para o problema: 204800
//        stack size original: 8192
int main() {
  candidate_t presidents[PRESIDENT_INITIAL_CAPACITY] 
    = {[0 ... CANDIDATES_CAPACITY-1] = {0, 0}};
  candidate_t senators[SENATOR_INITIAL_CAPACITY] 
    = {[0 ... CANDIDATES_CAPACITY-1] = {0, 0}};
  candidate_t depfeds[DEPFED_INITIAL_CAPACITY] 
    = {[0 ... CANDIDATES_CAPACITY-1] = {0, 0}};
  candidate_t depests[DEPEST_INITIAL_CAPACITY] 
    = {[0 ... CANDIDATES_CAPACITY-1] = {0, 0}};
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
    increment_candidate_votes(candidates[type], candidate_code);
  }

  
  printf("%d %d\n",
    valid_votes[0]+valid_votes[1]+valid_votes[2]+valid_votes[3],
    invalid_votes);
  print_president_winner(presidents, CANDIDATES_CAPACITY, valid_votes[0]);

  quickselect(senators, n_eligible_senators, 0, CANDIDATES_CAPACITY-1);
  quicksort(senators, 0, n_eligible_senators-1);
  print_winners(senators, n_eligible_senators);

  quickselect(depfeds, n_eligible_depfeds, 0, CANDIDATES_CAPACITY-1);
  quicksort(depfeds, 0, n_eligible_depfeds-1);
  print_winners(depfeds, n_eligible_depfeds);

  quickselect(depests, n_eligible_depests, 0, CANDIDATES_CAPACITY-1);
  quicksort(depests, 0, n_eligible_depests-1);
  print_winners(depests, n_eligible_depests);



  // print_votes(presidents, CANDIDATES_CAPACITY);
  // print_votes(senators, CANDIDATES_CAPACITY);
  // print_votes(depfeds, CANDIDATES_CAPACITY);
  // print_votes(depests, CANDIDATES_CAPACITY);
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


/**
### Solução B - provavelmente vai para o ursal-big

- todos os candidatos ficam no mesmo vetor

- guardar contador de votos válidos para cada tipo de candidato
- guardar contador da qtd de cada tipo de candidato
- quando ler a entrada, atribua o voto para o tipo certo de candidato e
  incremente o respectivo contador de votos válidos,
  incremente o respectivo contador de tipo de candidato

- ordenar em ordem descendente estavelmente pelo código do candidato
- ordenar em ordem descendente estavelmente pela qtd de votos
  (ou ao contrário. o resultado que eu quero é que o vetor fique em partes, 
(ou ao contrário. o resultado que eu quero é que o vetor fique em partes, 
  (ou ao contrário. o resultado que eu quero é que o vetor fique em partes, 
  cada parte para um tipo de candidato, cada parte ordenada pela qtd de votos)

// com os contadores de qtd de cada tipo de candidato, eu posso saber 
//   onde cada tipo de candidato começa

- selecionar o presidente com mais votos e determinar se é necessário um segundo turno
- selecionar os S Senadores com mais votos (já estão ordenados)
- selecionar os F DepFed com mais votos (já estão ordenados)
- selecionar os E DepEst com mais votos (já estão ordenados)

*/