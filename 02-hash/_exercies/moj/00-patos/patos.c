#include <stdio.h>
#include <stdlib.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-hash
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-hash/desfile.html
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-hash/desfile.pdf

#define COLORS_SIZE 5003

int hash(int x) {
  return x % COLORS_SIZE;
}

typedef struct color_t {
  int code;
  int count;
} color_t;

void increment_color_count(color_t* colors, int color_code) {
  int hashed_color = hash(color_code),
    probe, code;

  for (probe = 0; probe < COLORS_SIZE; probe++) {
    code = colors[hashed_color].code;

    if (colors[hashed_color].code == 0 || code == color_code)
      break;

    hashed_color = (hashed_color+1) % COLORS_SIZE;
  }

  if (probe >= COLORS_SIZE) {
    printf("colors is full\n");
    exit(1);
  }

  colors[hashed_color].code = color_code;
  colors[hashed_color].count++;
}


int find_max_freq_color_and_reset(color_t* colors) {
  int i = 0, curr_max_count = 0, max_freq_color_code = -1;
  for (; i < COLORS_SIZE; ++i) {
    if (colors[i].count > curr_max_count) {
      curr_max_count = colors[i].count;
      max_freq_color_code = colors[i].code;
    }

    colors[i].code = 0;
    colors[i].count = 0;
  }
  
  return max_freq_color_code;
}


int main() {
  int i, nducks = -1, color_code, max_freq_color_code;
  color_t colors[COLORS_SIZE] = {[0 ... COLORS_SIZE-1] = 0};

  while (scanf("%d", &nducks) && nducks != 0) {
    for (i = 0; i < nducks; ++i) {
      scanf("%d", &color_code);
      increment_color_count(colors, color_code);
    }

    // é necessário resetar colors para o prox caso de teste!!!
    max_freq_color_code = find_max_freq_color_and_reset(colors);
    printf("%d\n", max_freq_color_code);
  }

  return 0;
}