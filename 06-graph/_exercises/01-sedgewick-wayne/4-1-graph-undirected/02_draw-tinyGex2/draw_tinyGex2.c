#include <stdio.h>

#include "../../../../list-und-graph/listundgraph.h"
#include "../../../../list-und-graph/listundgraph_file.h"

int main(int argc, char const *argv[])
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyGex2.txt");
  ListUndGraph_show(g);
  ListUndGraph_destroy(g);
  return 0;
}
