#include <stdio.h>

#include "matundgraph.h"

int main() {
  // MatUndGraph* g = MatUndGraph_create(6);
  MatUndGraph* g = MatUndGraph_create_complete(6);

  MatUndGraph_insert_edge(g, 1, 0);
  MatUndGraph_insert_edge(g, 5, 1);
  // MatUndGraph_remove_edge(g, 0, 0);
  MatUndGraph_show(g);

  MatUndGraph_destroy(g);
  return 0;
}