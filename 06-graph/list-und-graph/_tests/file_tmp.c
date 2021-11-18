#include <stdio.h>

#include "../listundgraph.h"
#include "../listundgraph_file.h"

int main(int argc, char const *argv[])
{
  ListUndGraph* g = ListUndGraph_create_from_file("algs4-data/tinyG.txt");
  ListUndGraph_show(g);
  ListUndGraph_destroy(g);
  return 0;
}


