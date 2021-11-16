#ifndef COPY_LIST_H_INCLUDED
#define COPY_LIST_H_INCLUDED

#include "../../../../list-und-graph/listundgraph.h"

// exercise-4.1.3
ListUndGraph* ListUndGraph_copy(ListUndGraph* g) {
  ListUndGraph *copy = ListUndGraph_create(g->vertices);
  return copy;
}

#endif // COPY_LIST_H_INCLUDED