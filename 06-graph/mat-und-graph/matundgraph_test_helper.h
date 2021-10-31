#ifndef MATUNDGRAPH_TEST_HELPER_H_INCLUDED
#define MATUNDGRAPH_TEST_HELPER_H_INCLUDED

#include "matundgraph.h"

// HELPER
// HELPER
// HELPER
uint8_t edges_contains(Edge *edges, int edges_size, Vertex a, Vertex b)
{
  int i;
  Edge e = {a, b};
  for (i = 0; i < edges_size; i++)
  {
    if (UndEdge_equal(edges[i], e))
    {
      return 1;
    }
  }

  return 0;
}

uint8_t adjacent_contains(Vertex* adjacent, int adjacent_size, Vertex v) {
  for (size_t i = 0; i < adjacent_size; i++)
  {
    if (adjacent[i] == v)
      return 1;
  }
  
  return 0;
}


#endif // MATUNDGRAPH_TEST_HELPER_H_INCLUDED