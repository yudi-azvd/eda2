// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-arvorebinaria
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-arvorebinaria/arvore-binaria-pos.html
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-arvorebinaria/arvore-binaria-pos.pdf

// start-copy
#include <stdio.h>
#include <stdlib.h>

typedef struct no {
  int dado;
  struct no* esq;
  struct no* dir;
} no;

//  imprimir em ordem: esq, raiz, dir
// imprimir pos ordem: esq, dir, raiz
void pos_ordem(no* raiz) {
  if (raiz == NULL) {
    printf("\n");
    return;
  }

  no *stack[100] = {[0 ... 99] = NULL};
  no *aux;
  int height = 0;
  stack[height++] = raiz;
 
  while (1) {
    aux = stack[--height];

    if (aux != NULL) {
      stack[height++] = aux;
      stack[height++] = aux->dir;
      stack[height++] = aux->esq;
    }
    else {
      while ((aux = stack[--height]) == NULL);
      if (height == 0) break;
      printf("%d ", aux->dado);
      fflush(stdout);
      stack[height++] = NULL;
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

// Para a submissão no MOJ deve ser executado o script `cut-paste.sh`
// O arquivo resultante deve ser submetido.
int main() {
  int to_find, to_insert;
  char operation;
  no raiz, *raiz_ptr = NULL;
  raiz.esq = NULL;
  raiz.dir = NULL;
  
  int o = scanf("%d", &to_insert);
  if (o != EOF) {
    raiz_ptr = &raiz;
    raiz.dado = to_insert;

    while (scanf("%d %c %d", &to_insert, &operation, &to_find) != EOF) {
      procura_insere(raiz_ptr, to_insert, operation, to_find);
    }
  }

  printf("Pos-ordem: ");
  pos_ordem(raiz_ptr);

  return 0;
}