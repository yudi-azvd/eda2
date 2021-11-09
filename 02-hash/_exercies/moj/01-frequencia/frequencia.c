#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-hash
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-hash/digafrequencia.html
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-hash/digafrequencia.pdf

// Uma palavra não tem mais que 1000 caracteres
#define HT_LETTERS_SIZE 1009
#define WORD_SIZE 1001

int hash(int x) {
  return x % HT_LETTERS_SIZE;
}

typedef struct char_t {
  int ascii_code;
  int count;
} char_t;

void increment_letter_count(char_t* ht_letters, int letter) {
  int hashed_letter = hash(letter),
    probe, code;

  for (probe = 0; probe < HT_LETTERS_SIZE; probe++) {
    code = ht_letters[hashed_letter].ascii_code;

    if (ht_letters[hashed_letter].ascii_code == 0 || code == letter)
      break;

    hashed_letter = (hashed_letter+1) % HT_LETTERS_SIZE;
  }

  if (probe >= HT_LETTERS_SIZE) {
    printf("colors is full\n");
    exit(1);
  }

  ht_letters[hashed_letter].ascii_code = letter;
  ht_letters[hashed_letter].count++;
}


void find_letters_frequency(char_t* ht_letters, char* word) {
  int i = 0;

  for (; word[i] != '\0'; ++i) {
    increment_letter_count(ht_letters, word[i]);
  }
}


int cmpchar_t(const void* a, const void* b) {
  return (*(char_t*) a).count - (*(char_t*) b).count;
}


void print_letters_frequency_and_reset(char_t* ht_letters) {
  int i = 0;

  qsort(ht_letters, HT_LETTERS_SIZE, sizeof(char_t), cmpchar_t);

  for (; i < HT_LETTERS_SIZE; ++i) {
    if (ht_letters[i].ascii_code != 0) {
      printf("%d %d\n", ht_letters[i].ascii_code, ht_letters[i].count);
    }

    ht_letters[i].ascii_code = 0;
    ht_letters[i].count = 0;
  }
}


int main() {
  int i, nducks = -1, color_code, max_freq_color_code;
  char word[WORD_SIZE];
  int word_len;
  char_t ht_letters[HT_LETTERS_SIZE] = {[0 ... HT_LETTERS_SIZE-1] = 0};
  
  while (fgets(word, WORD_SIZE, stdin) != NULL) {
    word_len = strlen(word);
    word[word_len-1] = '\0'; // remove o '\n' no final

    find_letters_frequency(ht_letters, word);
    print_letters_frequency_and_reset(ht_letters);
    printf("\n");
  }

  return 0;
}