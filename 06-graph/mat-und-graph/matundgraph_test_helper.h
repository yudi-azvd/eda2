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

// Olhar imagem tinyCG.png
// Sedgewick Wayne Cap 4: Graphs, Undirected Graphs, DFS, pg 532 no livro
// 4.1
void fill_graph_tinyCGtxt(MatUndGraph** g) {
  *g = MatUndGraph_create(6);
  
  // Olhar em resources/algs4-data/tinyCG.txt
  MatUndGraph_insert_edge(*g, 0, 5);
  MatUndGraph_insert_edge(*g, 2, 4);
  MatUndGraph_insert_edge(*g, 2, 3);
  MatUndGraph_insert_edge(*g, 1, 2);
  MatUndGraph_insert_edge(*g, 0, 1);
  MatUndGraph_insert_edge(*g, 3, 4);
  MatUndGraph_insert_edge(*g, 3, 5);
  MatUndGraph_insert_edge(*g, 0, 2);

  // MatUndGraph_show(g);
}

// Olhar imagem tinyG.png
// Sedgewick Wayne Cap 4: Graphs, Undirected Graphs, DFS, pg 525 no livro
// 4.1
void fill_graph_tinyGtxt(MatUndGraph** g) {
  *g = MatUndGraph_create(13);
  
  // Olhar em resources/algs4-data/tinyG.txt
  MatUndGraph_insert_edge(*g, 0, 5);
  MatUndGraph_insert_edge(*g, 4, 3);
  MatUndGraph_insert_edge(*g, 0, 1);
  MatUndGraph_insert_edge(*g, 9, 12);
  MatUndGraph_insert_edge(*g, 6, 4);
  MatUndGraph_insert_edge(*g, 5, 4);
  MatUndGraph_insert_edge(*g, 0, 2);
  MatUndGraph_insert_edge(*g, 11, 12);
  MatUndGraph_insert_edge(*g, 9, 10);
  MatUndGraph_insert_edge(*g, 0, 6);
  MatUndGraph_insert_edge(*g, 7, 8);
  MatUndGraph_insert_edge(*g, 9, 11);
  MatUndGraph_insert_edge(*g, 5, 3);

  // MatUndGraph_show(g);
}


#endif // MATUNDGRAPH_TEST_HELPER_H_INCLUDED