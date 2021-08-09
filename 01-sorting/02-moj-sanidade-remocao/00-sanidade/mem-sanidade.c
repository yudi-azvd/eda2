#include <stdio.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-sanidade-e-remocao
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-sanidade-e-remocao/sanidade.html
/**
 * Tentei simular a memória "real" com os ponteiros. O campo
 * addr de node_t indexa num vetor mem. Mas uma das entradas
 * fornecidas tem addr = 0xFACADA, que é o índice 16.435.930.
 * Não parece cabível desperdiçar tanto espaço.
 */

typedef struct node_t {
  unsigned long int addr;
  unsigned long int prev;
  unsigned long int next;
} node_t;

#define MEM_SIZE 500000

node_t mem[MEM_SIZE] = {[0 ... MEM_SIZE-1] = {0, 0, 0}};
unsigned long forward_path[MEM_SIZE/2];

void print_node_t(node_t ptr) {
  printf("%lx %lx %lx\n", ptr.addr, ptr.prev, ptr.next);
}

void print_forward_path(unsigned long* fd_path, int size) {
  int i = 0;
  for (; i < size-1; ++i) {
    printf("%lx ", fd_path[i]);
  }
  printf("%lx\n", fd_path[i]);
}

int main() {
  int is_sane = 1, forward_path_idx = 0, subseq_len = 0;
  node_t ptr1, ptr2, currptr;

  scanf("%lx %lx %lx", &ptr1.addr, &ptr1.prev, &ptr1.next);
  scanf("%lx %lx %lx", &ptr2.addr, &ptr2.prev, &ptr2.next);

  mem[ptr1.addr] = ptr1;
  mem[ptr2.addr] = ptr2;
  while (scanf("%lx %lx %lx", &currptr.addr, &currptr.prev, &currptr.next) != EOF) {
    mem[currptr.addr] = currptr;
  }

  // não é à prova de caminhos circulares!!!
  // caminho ptr1 -> ptr2
  currptr = ptr1;
  while (currptr.next != 0) {
    // print_node_t(mem[currptr.addr]);
    forward_path[subseq_len] = currptr.addr;
    currptr = mem[currptr.next];
    subseq_len++;
  }
  // print_node_t(mem[currptr.addr]);
  forward_path[subseq_len] = currptr.addr;
  subseq_len++;

  // printf("\n");
  // print_forward_path(forward_path, subseq_len);

  // não é à prova de caminhos circulares!!!
  // caminho ptr2 -> ptr1
  currptr = ptr2;
  while (currptr.prev != 0) {
    if (currptr.addr != forward_path[subseq_len-forward_path_idx++ - 1]) {
      is_sane = 0;
      break;
    }
    
    // printf("%lx ", currptr.addr);
    currptr = mem[currptr.prev];
  }
  // checando o último ptr, que deveria ser ptr1
  if (currptr.addr != forward_path[subseq_len-forward_path_idx++ - 1])
    is_sane = 0;
  // printf("%lx\n", currptr.addr);

  // printf("\n\nsubseq_len %d\n", subseq_len);
  printf("%s\n", is_sane ? "sana" : "insana");
  return 0;
}