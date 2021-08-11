#include <stdlib.h>
#include <stdio.h>

// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-sanidade-e-remocao/remocao.html


typedef struct node_t {
  unsigned long int addr;
  unsigned long int prev;
  unsigned long int next;
} node_t;


#define NODES_SZ   250000

void merge(node_t* v, int lo, int hi1, int hi2) {
  int k = 0, i = lo, j = hi1+1;
  node_t* aux = (node_t*) calloc(hi2-lo+1, sizeof(node_t));

  while (i <= hi1 && j <= hi2) {
    if (v[i].addr < v[j].addr) // less(v[i], v[j])
      aux[k++] = v[i++];
    else
      aux[k++] = v[j++];
  }

  // copiar o restinho do 1o vetor
  while (i <= hi1) {
    aux[k++] = v[i++];
  }

  // copiar o restinho do 2o vetor
  while (j <= hi2) {
    aux[k++] = v[j++];
  }

  // copiar para o vetor original
  k = 0;
  for (i = lo; i <= hi2; ++i)
    v[i] = aux[k++];

  free(aux);  
}

void mergesort(node_t* v, int lo, int hi) {
  if (lo >= hi) return;

  int mid = (lo+hi)/2;

  mergesort(v, lo, mid);
  mergesort(v, mid+1, hi);
  merge(v, lo, mid, hi);
}

void print_node_t(node_t ptr) {
  printf("%lx %lx %lx\n", ptr.addr, ptr.prev, ptr.next);
}

void print_nodes(node_t* m, int size) {
  int index = 0;
  for (; index < size; index++)
    print_node_t(m[index]);
}

int binarysearch(unsigned long addr, node_t* v, int lo, int hi) {
  int mid = (lo + hi)/2;

  while (lo <= hi) {
    if (v[mid].addr < addr)
      lo = mid+1;
    else if (addr < v[mid].addr)
      hi = mid-1;
    else
      return mid;

    mid = (lo + hi)/2;
  }

  return v[mid].addr == addr ? mid : -1;
}


// Ordenar por addr e fazer busca binária.
int main() {
  int total_nodes = 0;
  node_t nodes[NODES_SZ] = {[0 ... NODES_SZ-1] = {0, 0, 0}};
  node_t ptr1, ptr2, currptr;

  while (scanf("%lx %lx %lx", &currptr.addr, &currptr.prev, &currptr.next) != EOF) {
    nodes[total_nodes++] = currptr;
  }

  ptr1 = nodes[0];
  ptr2 = nodes[1];

  // print_nodes(nodes, total_nodes);
  mergesort(nodes, 0, total_nodes-1);
  // printf("\n");
  // print_nodes(nodes, total_nodes);

  // a partir de ptr1, tenho que encontrar o nó mais anterior
  // a ele andando pra trás: é o nó com .prev = 0 ou com .prev 
  // para um nó que não existe
  node_t* most_anterior_node = &ptr1;
  int node_index = 0, most_anterior_node_index = 0;
  while (most_anterior_node->prev != 0) {
    node_index = binarysearch(most_anterior_node->prev, nodes, 0, total_nodes-1);
    if (node_index == -1)
      break;

    most_anterior_node = &nodes[node_index];
  }
  // printf("\n");
  // print_node_t(most_anterior_node);

  // a partir de ptr2, tenho que encontrar o nó mais posterior
  // a ele andando pra frente: é o nó com .next = 0 ou com .next 
  // para um nó que não existe
  node_t most_posterior_node = ptr2;
  node_index = 0;
  while (most_posterior_node.prev != 0) {
    node_index = binarysearch(most_posterior_node.next, nodes, 0, total_nodes-1);
    if (node_index == -1)
      break;
    
    most_posterior_node = nodes[node_index];
  }
  // print_node_t(most_posterior_node);
  // printf("\n");

  int ptr1_prev_index = binarysearch(ptr1.prev, nodes, 0, total_nodes-1);
  int ptr2_next_index = binarysearch(ptr2.next, nodes, 0, total_nodes-1);
  nodes[ptr1_prev_index].next = nodes[ptr2_next_index].addr;
  nodes[ptr2_next_index].prev = nodes[ptr1_prev_index].addr;

  // varrer lista imprimindo os nós até chegar ao nó anterior a ptr1
  // assumindo que ela tem todos os seus nós ligados 
  // corretamente.
  node_t node = *most_anterior_node;
  // most_anterior_node = 
  while (node.addr != nodes[ptr1_prev_index].addr) {
    print_node_t(node);
    node_index = binarysearch(node.next, nodes, 0, total_nodes-1);
    node = nodes[node_index];
  }
  print_node_t(node); // imprime ptr1_prev

  // varrer lista imprimindo os nós até chegar ao most_posterior_node
  // assumindo que ela tem todos os seus nós ligados 
  // corretamente.
  node = nodes[ptr2_next_index];
  while (node.addr != most_posterior_node.addr) {
    node_index = binarysearch(node.next, nodes, 0, total_nodes-1);
    print_node_t(node);
    node = nodes[node_index];
  }
  print_node_t(node);

  printf("\n");
  node = ptr1;
  while (node.addr != ptr2.addr) {
    printf("%lx\n", node.addr);
    node_index = binarysearch(node.next, nodes, 0, total_nodes-1);
    node = nodes[node_index];
  }
  printf("%lx\n", nodes[node_index].addr);

  return 0;
}
