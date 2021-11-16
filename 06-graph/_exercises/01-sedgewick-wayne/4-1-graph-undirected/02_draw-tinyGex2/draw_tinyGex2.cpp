#include <iostream>

#include "../../../../list-und-graph/listundgraph.h"
#include "../../util.h"

int main(int argc, char const *argv[])
{
  ListUndGraph *g;
  fill_graph_tinyGex2(&g);
  ListUndGraph_show(g);
  ListUndGraph_destroy(g);
  return 0;
}
