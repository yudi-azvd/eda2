#ifndef MATDIRGRAPH_TEST_HELPER_H_INCLUDED
#define MATDIRGRAPH_TEST_HELPER_H_INCLUDED

#include <fstream>
#include <stdlib.h>

#include "../matdirgraph.h"

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

// Olhar imagem tinyDG.png
// Sedgewick Wayne Cap 4: Graphs, Directed Graphs, DFS, pg 569 no livro
// 4.2
void fill_graph_tinyDGtxt(MatDirGraph** g) {
  std::fstream infile("../../../resources/algs4-data/tinyDG.txt");
  std::string line;

  if (!infile.is_open()) {
    printf("not possible to open file\n");
    exit(1);
  }

  int vertices, edges, v, w, i = 0;
  infile >> vertices >> edges;

  *g = MatDirGraph_create(vertices);
  while(i++ < edges) {
    infile >> v >> w;
    MatDirGraph_insert_edge(*g, v, w);
  }

  // MatDirGraph_show(*g);
  infile.close();
}


#endif // MATDIRGRAPH_TEST_HELPER_H_INCLUDED