#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../../../lib/doctest.h"

#include "../../../../list-und-graph/listundgraph.h"
#include "has_edge_list.h"
#include "has_edge_list_util.h"

// exercise-4.1.3
TEST_SUITE_BEGIN("listundgraph_has_edge");

TEST_CASE("has edge")
{
  ListUndGraph *g;
  fill_graph_tinyG(&g);
}

TEST_SUITE_END();