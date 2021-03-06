#ifndef LISTUNDGRAPH_TEST_HELPER_H_INCLUDED
#define LISTUNDGRAPH_TEST_HELPER_H_INCLUDED

#include <fstream>

#include "../listundgraph.h"

// Olhar imagem tinyCG.png
// Sedgewick Wayne Cap 4: Graphs, Undirected Graphs, DFS, pg 532 no livro
// 4.1
void fill_graph_tinyCGtxt(ListUndGraph** g) {
  *g = ListUndGraph_create(6);
  
  // Olhar em resources/algs4-data/tinyCG.txt
  ListUndGraph_insert_edge(*g, 0, 5);
  ListUndGraph_insert_edge(*g, 2, 4);
  ListUndGraph_insert_edge(*g, 2, 3);
  ListUndGraph_insert_edge(*g, 1, 2);
  ListUndGraph_insert_edge(*g, 0, 1);
  ListUndGraph_insert_edge(*g, 3, 4);
  ListUndGraph_insert_edge(*g, 3, 5);
  ListUndGraph_insert_edge(*g, 0, 2);

  // ListUndGraph_show(*g);
}

// Olhar imagem tinyG.png
// Sedgewick Wayne Cap 4: Graphs, Undirected Graphs, DFS, pg 525 no livro
// 4.1
void fill_graph_tinyGtxt(ListUndGraph** g) {
  *g = ListUndGraph_create(13);
  
  // Olhar em resources/algs4-data/tinyG.txt
  ListUndGraph_insert_edge(*g, 0, 5);
  ListUndGraph_insert_edge(*g, 4, 3);
  ListUndGraph_insert_edge(*g, 0, 1);
  ListUndGraph_insert_edge(*g, 9, 12);
  ListUndGraph_insert_edge(*g, 6, 4);
  ListUndGraph_insert_edge(*g, 5, 4);
  ListUndGraph_insert_edge(*g, 0, 2);
  ListUndGraph_insert_edge(*g, 11, 12);
  ListUndGraph_insert_edge(*g, 9, 10);
  ListUndGraph_insert_edge(*g, 0, 6);
  ListUndGraph_insert_edge(*g, 7, 8);
  ListUndGraph_insert_edge(*g, 9, 11);
  ListUndGraph_insert_edge(*g, 5, 3);

  // ListUndGraph_show(*g);
}

void fill_graph_moj_viagem_00in(ListUndGraph** g) {
  *g = ListUndGraph_create(6);
  
  // Olhar em viagem/samples/00.in
  ListUndGraph_insert_edge(*g, 0, 1);
  ListUndGraph_insert_edge(*g, 2, 3);
  ListUndGraph_insert_edge(*g, 2, 4);
  ListUndGraph_insert_edge(*g, 4, 5);

  // ListUndGraph_show(*g);
}

void fill_graph_moj_viagem_01in(ListUndGraph** g) {
  std::fstream infile("../../_exercises/00-moj/02-viagem/samples/01.in");

  if (!infile.is_open()) {
    printf("not possible to open file\n");
    exit(1);
  }

  int vertices, i = 0, v, w, _;

  infile >> vertices >> _;
  *g = ListUndGraph_create(vertices);
  
  while (!infile.eof())
  {
    infile >> v >> w;
    ListUndGraph_insert_edge(*g, v, w);
  }
  // ListUndGraph_show(*g);
}


void fill_graph_moj_viagem_02in(ListUndGraph** g) {
  std::fstream infile("../../_exercises/00-moj/02-viagem/samples/02.in");

  if (!infile.is_open()) {
    printf("not possible to open file\n");
    exit(1);
  }

  int vertices, i = 0, v, w, _;

  infile >> vertices >> _;
  *g = ListUndGraph_create(vertices);
  
  while (!infile.eof())
  {
    infile >> v >> w;
    ListUndGraph_insert_edge(*g, v, w);
  }
  // ListUndGraph_show(*g);
}

#endif // LISTUNDGRAPH_TEST_HELPER_H_INCLUDED