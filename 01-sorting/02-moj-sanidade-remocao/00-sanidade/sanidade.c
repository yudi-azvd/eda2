#include <stdio.h>
#include <stdlib.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-sanidade-e-remocao
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-sanidade-e-remocao/sanidade.html

typedef struct node_t {
  unsigned long int addr;
  unsigned long int prev;
  unsigned long int next;
} node_t;


#define NODES_SZ 250000
#define FD_PATH_SZ 1000


void print_node_t(node_t ptr) {
  printf("%lx %lx %lx\n", ptr.addr, ptr.prev, ptr.next);
}

void print_mem(node_t* m, int size) {
  int index = 0;
  for (; index < size; index++)
    print_node_t(m[index]);
}

int cmpptr(const void* p1, const void* p2) {
  node_t* ptr1 = (node_t*) p1;
  node_t* ptr2 = (node_t*) p2;
  return ptr1->addr - ptr2->addr;
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
  int is_sane = 1, total_nodes = 0;
  node_t nodes[NODES_SZ] = {[0 ... NODES_SZ-1] = {0, 0, 0}};
  node_t forward_path[FD_PATH_SZ] = {[0 ... FD_PATH_SZ-1] = {0, 0, 0}};
  node_t ptr1, ptr2, currptr;

  while (scanf("%lx %lx %lx", &currptr.addr, &currptr.prev, &currptr.next) != EOF) {
    nodes[total_nodes++] = currptr;
  }

  ptr1 = nodes[0];
  ptr2 = nodes[1];

  // print_mem(nodes, total_nodes);
  qsort(nodes, total_nodes, sizeof(node_t), cmpptr);
  // printf("\n");
  // print_mem(nodes, total_nodes);

  // printf("\n");
  // montar o caminho direto ptr1 -> ptr2 em forward_path
  currptr = ptr1;
  int iterations = 1, index = 0, node_idx, fd_path_len = 0;
  while (currptr.addr != ptr2.addr) {
    // print_node_t(currptr);
    node_idx = binarysearch(currptr.next, nodes, 0, total_nodes-1);
    if (node_idx == -1) {
      is_sane = 0;
      break;
    }
    
    if (iterations > total_nodes) {
      is_sane = 0;
      break;
    }

    forward_path[index++] = currptr;
    currptr = nodes[node_idx];
    iterations++;
    fd_path_len++;
  }
  fd_path_len++;
  forward_path[index++] = currptr;
  // print_node_t(currptr);
  
  if (is_sane) {
    // comparar o caminho inverso ptr2 -> ptr1 com forward_path
    currptr = ptr2; iterations = 1; index = 0;
    while (currptr.addr != ptr1.addr) {
      // print_node_t(currptr);
      
      if (currptr.addr != forward_path[fd_path_len-index-1].addr) {
        is_sane = 0;
        break;
      }

      int node_idx = binarysearch(currptr.prev, nodes, 0, total_nodes-1);
      if (node_idx == -1) {
        is_sane = 0;
        break;
      }

      if (iterations > fd_path_len) {
        is_sane = 0;
        break;
      }

      currptr = nodes[node_idx];
      ++iterations; ++index;
    }
  }

  // fd_path_len-1 pq o while não chega a incrementar iterations pra ptr1
  if (iterations != fd_path_len)
    is_sane = 0;

  printf("%s\n", is_sane ? "sana" : "insana");
  return 0;
}