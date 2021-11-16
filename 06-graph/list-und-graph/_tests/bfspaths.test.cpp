#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "../listundgraph_bfspaths.h"
#include "listundgraph_test_helper.h"

TEST_SUITE_BEGIN("listundgraph_bfspaths");

TEST_CASE("create and destroy")
{
  ListUndGraph *g;
  fill_graph_tinyCGtxt(&g);

  BFSPaths *p = BFSPaths_create(g, 0);

  BFSPaths_destroy(p);
  ListUndGraph_destroy(g);
}

TEST_CASE("tinyCG has_path_to")
{
  ListUndGraph *g;
  fill_graph_tinyCGtxt(&g);

  BFSPaths *p = BFSPaths_create(g, 0);

  CHECK(BFSPaths_has_path_to(p, 1));
  CHECK(BFSPaths_has_path_to(p, 2));
  CHECK(BFSPaths_has_path_to(p, 3));
  CHECK(BFSPaths_has_path_to(p, 4));
  CHECK(BFSPaths_has_path_to(p, 5));

  BFSPaths_destroy(p);
  ListUndGraph_destroy(g);
}

TEST_CASE("tinyCG path_to")
{
  ListUndGraph *g;
  fill_graph_tinyCGtxt(&g);

  BFSPaths *p = BFSPaths_create(g, 0);

  int path_size = -1;
  Vertex *path = BFSPaths_path_to(p, 5, &path_size);

  REQUIRE(4 == path_size);
  CHECK(5 == path[0]);
  CHECK(3 == path[1]);
  CHECK(2 == path[2]);
  CHECK(0 == path[3]);

  free(path);
  BFSPaths_destroy(p);
  ListUndGraph_destroy(g);
}

TEST_CASE("tinyG has_path_to")
{
  ListUndGraph *g;
  fill_graph_tinyGtxt(&g);

  BFSPaths *p = BFSPaths_create(g, 0);

  CHECK(BFSPaths_has_path_to(p, 1));
  CHECK(BFSPaths_has_path_to(p, 2));
  CHECK(BFSPaths_has_path_to(p, 3));
  CHECK(BFSPaths_has_path_to(p, 4));
  CHECK(BFSPaths_has_path_to(p, 5));
  CHECK(BFSPaths_has_path_to(p, 6));

  CHECK_FALSE(BFSPaths_has_path_to(p, 7));
  CHECK_FALSE(BFSPaths_has_path_to(p, 8));

  CHECK_FALSE(BFSPaths_has_path_to(p, 9));
  CHECK_FALSE(BFSPaths_has_path_to(p, 10));
  CHECK_FALSE(BFSPaths_has_path_to(p, 11));
  CHECK_FALSE(BFSPaths_has_path_to(p, 12));

  BFSPaths_destroy(p);
  ListUndGraph_destroy(g);
}

TEST_CASE("tinyG path_to")
{
  ListUndGraph *g;
  fill_graph_tinyGtxt(&g);

  BFSPaths *p = BFSPaths_create(g, 0);

  int path_size = -1;
  Vertex *path = BFSPaths_path_to(p, 5, &path_size);

  // ListUndGraph_show(g);
  REQUIRE(4 == path_size);
  CHECK(5 == path[0]);
  CHECK(4 == path[1]);
  CHECK(6 == path[2]);
  CHECK(0 == path[3]);

  free(path);
  BFSPaths_destroy(p);
  ListUndGraph_destroy(g);
}
