// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-hash
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-hash/eleicao-ursal-big.html
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-hash/eleicao-ursal-big.pdf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define CADIDATES_CAPACITY 1001


int hash(int x, int capacity) {
  return x % capacity;
}


typedef struct candidate_t {
  int code;
  int vote_count;
} candidate_t;


void increment_candidate_vote_count(candidate_t* candidates, int candidate_code, int candidates_size) {
  int hashed_candidate_code = hash(candidate_code, candidates_size),
    probe, code;

  for (probe = 0; probe < candidates_size; probe++) {
    code = candidates[hashed_candidate_code].code;

    if (candidates[hashed_candidate_code].code == 0 || code == candidate_code)
      break;

    hashed_candidate_code = (hashed_candidate_code+1) % candidates_size;
  }

  if (probe >= candidates_size) {
    printf("candidates is full\n");
    exit(1);
  }

  candidates[hashed_candidate_code].code = candidate_code;
  candidates[hashed_candidate_code].vote_count++;
}


int is_president(int candidate_code) {
  return 1 <= candidate_code && candidate_code < 100;
}

int is_senator(int candidate_code) {
  return 100 <= candidate_code && candidate_code < 999;
}


void calc_election_result_and_print(candidate_t* candidates) {
  int i = 0;
  int possible_president_winner_code = 0;
  int possible_senator_winner_code = 0;
  for (i = 0; i < CADIDATES_CAPACITY; i++) {
    if (candidates[i].code == 0)
      continue;

    if (is_president(candidates[i].code)) {
      if (candidates[i].vote_count > candidates[possible_president_winner_code].vote_count) {
        possible_president_winner_code = candidates[i].code;
      }      
    }
    else if (is_senator(candidates[i].code)) {
      if (candidates[i].vote_count > candidates[possible_senator_winner_code].vote_count) {
        possible_senator_winner_code = candidates[i].code;
      }      
    }
  }

  printf("%d\n", possible_president_winner_code);
  printf("%d\n", possible_senator_winner_code);
}



int main() {
  int n_eligible_senators, n_eligible_depfed, n_eligible_depest;
  int candidate_code, valid_votes_count = 0, invalid_votes_count = 0;
  candidate_t presidents[1000], senators[1000], depfeds[1000], depests[1000];
  candidate_t candidates[1001] = { [0 ... CADIDATES_CAPACITY-1] = 0 };

  scanf("%d %d %d", &n_eligible_senators, &n_eligible_depfed, &n_eligible_depest);

  // assumindo que não vai ocorrer voto == 0
  while (scanf("%d", &candidate_code) != EOF) {
    if (candidate_code < 0) 
      ++invalid_votes_count;
    else {
      // decidir que tipo de candidato para escolher o vetor necessário?
      ++valid_votes_count;
      increment_candidate_vote_count(candidates, candidate_code, 1001);
    }
  
  }

  printf("%d %d\n", valid_votes_count, invalid_votes_count);
  calc_election_result_and_print(candidates);

  return 0;
}

/**
### Solução A

vários arrays de candidatos (presidente, senador etc)
guardar contador de votos válidos para cada tipo de candidato
quando ler a entrada, atribua o voto para o tipo certo de candidato e incremente o contador de votos válidos

busca linear pelo presidente com mais votos
  determinar se é necessário segundo turno

quickselect para os S Senadores com maiores votos
  quicksort os S senadores

quickselect para os F DepFed com maiores votos
  quicksort os F DepFed

quickselect para os E DepEst com maiores votos
  quicksort os E DepEst
*/

/**
### Solução B - provavelmente vai para o ursal-big

todos os candidatos ficam no mesmo vetor

guardar contador de votos válidos para cada tipo de candidato
guardar contador da qtd de cada tipo de candidato
quando ler a entrada, atribua o voto para o tipo certo de candidato e
  incremente o respectivo contador de votos válidos,
  incremente o respectivo contador de tipo de candidato

ordenar em ordem descendente estavelmente pelo código do candidato
ordenar em ordem descendente estavelmente pela qtd de votos
(ou ao contrário. o resultado que eu quero é que o vetor fique em partes, 
  cada parte para um tipo de candidato, cada parte ordenada pela qtd de votos)

// com os contadores de qtd de cada tipo de candidato, eu posso saber 
//   onde cada tipo de candidato começa

selecionar o presidente com mais votos e determinar se é necessário um segundo turno
selecionar os S Senadores com mais votos (já estão ordenados)
selecionar os F DepFed com mais votos (já estão ordenados)
selecionar os E DepEst com mais votos (já estão ordenados)

*/