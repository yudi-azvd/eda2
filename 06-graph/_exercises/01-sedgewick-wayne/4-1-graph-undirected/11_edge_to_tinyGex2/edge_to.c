#include <stdio.h>

#include "../../../../list-und-graph/listundgraph.h"
#include "../../../../list-und-graph/listundgraph_bfspaths.h"
#include "../../../../list-und-graph/listundgraph_file.h"

// exercise-4.1.11
int main(int argc, char const *argv[])
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyGex2.txt");
  BFSPaths *p = BFSPaths_create(g, 0);

  for (int i = 0; i < ListUndGraph_vertices_count(g); i++)
  {
    printf("%2d: %2d\n", i, p->edge_to[i]);
  }

  free(p);
  ListUndGraph_destroy(g);
  return 0;
}
