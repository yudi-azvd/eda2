#include <stdio.h>

#include "adj-mat-und-graph.h"

int main() {
  // AdjMatGraph* g = AdjMatUndGraph_create(6);
  AdjMatGraph* g = AdjMatUndGraph_create_complete(6);

  // AdjMatUndGraph_insert_edge(g, 1, 0);
  // AdjMatUndGraph_insert_edge(g, 5, 1);
  AdjMatUndGraph_remove_edge(g, 0, 0);
  AdjMatUndGraph_show(g);

  AdjMatUndGraph_destroy(g);
  return 0;
}