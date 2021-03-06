#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../../../lib/doctest.h"

#include "../../../../list-und-graph/listundgraph.h"
#include "../../../../list-und-graph/listundgraph_file.h"
#include "has_edge_list.h"

// exercise-4.1.3
TEST_SUITE_BEGIN("listundgraph_has_edge");

TEST_CASE("has edge")
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyG.txt");

  CHECK(ListUndGraph_has_edge(g, 7, 8));
  CHECK(ListUndGraph_has_edge(g, 9, 10));
  CHECK(ListUndGraph_has_edge(g, 0, 1));
  CHECK(ListUndGraph_has_edge(g, 0, 2));

  CHECK_FALSE(ListUndGraph_has_edge(g, 1, 2));
  CHECK_FALSE(ListUndGraph_has_edge(g, 7, 9));
  CHECK_FALSE(ListUndGraph_has_edge(g, 12, 10));

  ListUndGraph_destroy(g);
}

TEST_SUITE_END();