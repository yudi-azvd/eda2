#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://www.ime.usp.br/~pf/algoritmos/aulas/hash.html

int* tb;

void contabiliza(int ch) {
  tb[ch]++;  
}

void print_count(int size) {
  int i;
  for (i = 0; i < size; i++) {
    printf("%3d: %d\n", i, tb[i]);
  }
}

#define MAX_SIZE 10000

int main(int argc, char** argv) {
  int i, N = MAX_SIZE, ch;
  tb = calloc(N, sizeof(int));

  for (i = 0; i < N; i++) {
    scanf("%d", &ch);
    contabiliza(ch);
  }

  print_count(N);
}