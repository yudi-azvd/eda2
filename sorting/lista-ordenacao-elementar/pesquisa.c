#include <stdio.h>
#include <string.h>

typedef struct instruction {
  int code;
  char keyword[16];
} instruction;


void improvedinsertionsort(instruction *v, int l, int h) {
  int i = 0, j, min = l;
  instruction tmp;

  // o menor elemento fica em [0]
  for (i = h; i > l; --i) {
    if (v[i].code < v[i-1].code) {
      tmp = v[i];
      v[i] = v[i-1];
      v[i-1] = tmp;
    }
  }

  for (i = l+2; i <= h; ++i) {
    j = i; tmp = v[i];

    while (tmp.code < v[j-1].code) {
      v[j] = v[j-1]; --j;
    }
    v[j] = tmp;
  }
}


// Retorna o índice se encontrado. Caso contrário retorna -1.
int binarysearch(int code, instruction* v, int lo, int hi) {
  int mid = (lo + hi)/2;

  while (lo <= hi) {
    if (v[mid].code < code)
      lo = mid+1;
    else if (code < v[mid].code)
      hi = mid-1;
    else
      return mid;

    mid = (lo + hi)/2;
  }

  return v[mid].code == code ? mid : -1;
}


int main() {
  int number_of_instructions, i = 0, code;
  instruction instructions[1000000];

  scanf("%d\n", &number_of_instructions);

  while (i < number_of_instructions) {
    scanf("%d %s\n", &instructions[i].code, instructions[i].keyword);
    i++;
  }

  improvedinsertionsort(instructions, 0, number_of_instructions-1);

  int index;
  while (scanf("%d", &code) != EOF) {
    index = binarysearch(code, instructions, 0, number_of_instructions-1);
    if (index == -1)
      printf("undefined\n");
    else
      printf("%s\n", instructions[index].keyword);
  }

  return 0;
}