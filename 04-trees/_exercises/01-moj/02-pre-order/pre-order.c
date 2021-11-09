// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-arvorebinaria
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-arvorebinaria/arvore-binaria-in.html
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-arvorebinaria/arvore-binaria-in.pdf

// start-copy
#include <stdio.h>
#include <stdlib.h>

typedef struct no {
  int dado;
  struct no* esq;
  struct no* dir;
} no;

void pre_ordem(no* raiz) {
  no *nodes_stack[100] = {[0 ... 99] = NULL};
  no *aux;
  int stack_height = 0;
  nodes_stack[stack_height++] = raiz;

  while (1) {
    aux = nodes_stack[--stack_height];

    if (aux != NULL) {
      nodes_stack[stack_height++] = aux;
      nodes_stack[stack_height++] = aux->esq;
    }
    else {
      if (stack_height == 0) break;
      aux = nodes_stack[--stack_height];
      printf("%d ", aux->dado);
      nodes_stack[stack_height++] = aux->dir;
    }
  }

  printf("\n");
}
// end-copy

// assumir que dados não se repetem
void procura_insere(no* node, int to_insert, char op, int to_find) {
  if (node == NULL)
    return;
  
  if (node->dado == to_find) {
    no* new_node = calloc(1, sizeof(no));
    new_node->dado = to_insert;
    new_node->dir = NULL;
    new_node->esq = NULL;
    if (op == 'E')
      node->esq = new_node;
    else
      node->dir = new_node;
    return;
  }
  else {
    procura_insere(node->esq, to_insert, op, to_find);
    procura_insere(node->dir, to_insert, op, to_find);
  }
}


// SIM, ESSE PROGRAMA VAZA MEMÓRIA
// Para a submissão no MOJ deve ser executado o script `cut-paste.sh`
// O arquivo resultante deve ser submetido.
int main() {
  int to_find, to_insert;
  char operation;
  no raiz;
  
  scanf("%d", &to_insert);
  raiz.dado = to_insert;
  raiz.esq = NULL;
  raiz.dir = NULL;

  while (scanf("%d %c %d", &to_insert, &operation, &to_find) != EOF) {
    procura_insere(&raiz, to_insert, operation, to_find);
  }

  printf("Em ordem: ");
  pre_ordem(&raiz);

  return 0;
}