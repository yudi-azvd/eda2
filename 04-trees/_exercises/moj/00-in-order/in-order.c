#include <stdio.h>
#include <stdlib.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-arvorebinaria
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-arvorebinaria/arvore-binaria-in.html
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-arvorebinaria/arvore-binaria-in.pdf

// void insere_no(no* raiz, int number) {
//   no* aux = raiz;
//   no* new_node = (no*) calloc(1, sizeof(no));
//   new_node->esq = NULL;
//   new_node->dir = NULL;
//   new_node->dado = number;

//   while (1) {
//     if (number <= aux->dado && aux->esq == NULL) {
//       aux->esq = new_node;
//       break;
//     }

//     if (number > aux->dado && aux->dir == NULL) {
//       aux->dir = new_node;
//       break;
//     }

//     if (number <= aux->dado)
//       aux = aux->esq;
//     else
//       aux = aux->dir;
//   }
// }


typedef struct no {
  int dado;
  struct no *esq, *dir;
} no;


void em_ordem(no* raiz) {
  no* nodes_stack[100];
  no* aux;
  nodes_stack[0] = raiz;
  int stack_height = 1;

  while (1) {
    aux = nodes_stack[stack_height--];

    if (aux != NULL) {
      nodes_stack[stack_height++] = aux;
      nodes_stack[stack_height++] = aux->esq;
    }
    else {
      if (stack_height == 0) break;
      aux = nodes_stack[stack_height--];
      printf("%d ", aux->dado);
      nodes_stack[stack_height++] = aux->dir;
    }
  }

  printf("\n");
}