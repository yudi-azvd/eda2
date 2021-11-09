#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-hash
// https://br.spoj.com/problems/NOTAS14.pdf

#define HT_SCORES_MAX 211
#define UNSET_SCORE -1

int hash(int x) {
  return x % HT_SCORES_MAX;
}

typedef struct score_t {
  int score;
  int count;
} score_t;


void print_scores_counts(score_t* ht_scores) {
  int i = 0, size = 0;
  printf("[\n");
  for (; i < HT_SCORES_MAX; i++) {
    if (ht_scores[i].score != UNSET_SCORE) {
      printf("  %d %d\n", ht_scores[i].score, ht_scores[i].count);
      ++size;
    }
  }
  printf("] size = %d\n", size);
  
}

void increment_score_count(score_t* ht_scores, int score) {
  int hashed_score = hash(score),
    probe, code;

  for (probe = 0; probe < HT_SCORES_MAX; probe++) {
    code = ht_scores[hashed_score].score;

    if (ht_scores[hashed_score].score == UNSET_SCORE || code == score)
      break;

    hashed_score = (hashed_score+1) % HT_SCORES_MAX;
  }

  if (probe >= HT_SCORES_MAX) {
    printf("colors is full\n");
    exit(1);
  }

  ht_scores[hashed_score].score = score;
  ht_scores[hashed_score].count++;
}

int cmpscore_t(const void* a, const void* b) {
  return (*(score_t*) a).count - (*(score_t*) b).count;
}


int find_score_max_frequency(score_t* ht_scores) {
  int i = 1, max_score_idx = 0;

  for (; i < HT_SCORES_MAX; ++i) {
    if (ht_scores[i].score != UNSET_SCORE) {
      if (ht_scores[i].count >= ht_scores[max_score_idx].count 
        && ht_scores[i].score > ht_scores[max_score_idx].score)
      max_score_idx = i;
    }
  }

  return max_score_idx;  
}


int main() {
  int i = 0, nstudents = 0, score;
  score_t ht_scores[HT_SCORES_MAX] = {[0 ... HT_SCORES_MAX-1] = {UNSET_SCORE, 0}};

  scanf("%d", &nstudents);

  for (; i < nstudents; ++i) {
    scanf("%d", &score);
    increment_score_count(ht_scores, score);
  }

  // print_scores_counts(ht_scores);
  printf("%d\n", find_score_max_frequency(ht_scores));
  
  return 0;
}