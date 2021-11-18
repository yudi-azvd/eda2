#ifndef _04_HAS_EDGE_LIST_H_INCLUDED
#define _04_HAS_EDGE_LIST_H_INCLUDED

#include "../../../../list-und-graph/listundgraph.h"
#include "has_edge_list.h"

// exercise-4.1.4
int ListUndGraph_has_edge(ListUndGraph* g, int v, int w) {
  Node* node = g->arr[v];
  while (node != NULL)
  {
    if (node->vertex == w)
      return 1;
    node = node->next;
  }
  
  return 0;
}

#endif // _04_HAS_EDGE_LIST_H_INCLUDED