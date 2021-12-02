#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "../listundgraph_file.h"
#include "../listundgraph_cycle.h"

TEST_SUITE_BEGIN("listundgraph_cycle");

TEST_CASE("create and destroy")
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyG.txt");
  Cycle *cy = Cycle_create(g);

  Cycle_destroy(cy);
  ListUndGraph_destroy(g);
}

TEST_CASE("tinyG should have cycle")
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyG.txt");
  Cycle *cy = Cycle_create(g);

  CHECK(Cycle_has(cy));

  Cycle_destroy(cy);
  ListUndGraph_destroy(g);
}

TEST_CASE("tinyCG should have cycle")
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyCG.txt");
  Cycle *cy = Cycle_create(g);

  CHECK(Cycle_has(cy));

  Cycle_destroy(cy);
  ListUndGraph_destroy(g);
}

TEST_CASE("tiny line should not have a cycle")
{
  ListUndGraph *g = ListUndGraph_create(5);
  ListUndGraph_insert_edge(g, 0, 1);
  ListUndGraph_insert_edge(g, 1, 2);
  ListUndGraph_insert_edge(g, 3, 4);

  Cycle *cy = Cycle_create(g);

  CHECK_FALSE(Cycle_has(cy));

  Cycle_destroy(cy);
  ListUndGraph_destroy(g);
}
