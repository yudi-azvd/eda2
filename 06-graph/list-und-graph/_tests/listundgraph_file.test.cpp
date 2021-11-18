#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "../listundgraph.h"
#include "../listundgraph_file.h"

TEST_SUITE_BEGIN("listundgraph_file");

TEST_CASE("create and destroy")
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyG.txt");

  CHECK(ListUndGraph_edges_count(g) == 13);
  CHECK(ListUndGraph_vertices_count(g) == 13);

  // ListUndGraph_show(g);

  ListUndGraph_destroy(g);
}


TEST_SUITE_END();