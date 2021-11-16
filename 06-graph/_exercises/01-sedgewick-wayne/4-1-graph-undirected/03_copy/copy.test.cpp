#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../../../lib/doctest.h"

#include "../../../../list-und-graph/listundgraph.h"
#include "../../util.h"
#include "../04_has_edge/has_edge_list.h"
#include "copy_list.h"

// exercise-4.1.3
TEST_SUITE_BEGIN("listundgraph_copy");

TEST_CASE("copy")
{
  ListUndGraph *original;
  fill_graph_tinyG(&original);

  ListUndGraph* copy = ListUndGraph_copy(original);

  CHECK(copy != original);

  ListUndGraph_insert_edge(original, 7, 9);
  ListUndGraph_insert_edge(original, 8, 10);

  CHECK_FALSE(ListUndGraph_has_edge(copy, 7, 9));
  CHECK_FALSE(ListUndGraph_has_edge(copy, 8, 10));  

  ListUndGraph_destroy(original);
  ListUndGraph_destroy(copy);
}

TEST_SUITE_END();