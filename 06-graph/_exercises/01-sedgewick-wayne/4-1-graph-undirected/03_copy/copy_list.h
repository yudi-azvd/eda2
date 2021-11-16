#ifndef COPY_LIST_H_INCLUDED
#define COPY_LIST_H_INCLUDED

#include "../../../../list-und-graph/listundgraph.h"

// exercise-4.1.3
ListUndGraph* ListUndGraph_copy(ListUndGraph* g) {
  ListUndGraph *copy = ListUndGraph_create(g->vertices);
  int i = 0;
  Node* node;

  for (; i < g->vertices; i++)
  {
    node = g->arr[i];

    while (node != NULL) {
      ListUndGraph_insert_edge(copy, i, node->vertex);
      node = node->next;
    }
  }

  return copy;
}

#endif // COPY_LIST_H_INCLUDED