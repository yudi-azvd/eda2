#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "../listundgraph_dfspaths.h"
#include "../listundgraph_file.h"

TEST_SUITE_BEGIN("listundgraph_dfspaths");

TEST_CASE("create and destroy")
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyCG.txt");
  DFSPaths *p = DFSPaths_create(g, 0);

  DFSPaths_destroy(p);
  ListUndGraph_destroy(g);
}

TEST_CASE("tinyCG has_path_to")
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyCG.txt");
  DFSPaths *p = DFSPaths_create(g, 0);

  CHECK(DFSPaths_has_path_to(p, 1));
  CHECK(DFSPaths_has_path_to(p, 2));
  CHECK(DFSPaths_has_path_to(p, 3));
  CHECK(DFSPaths_has_path_to(p, 4));
  CHECK(DFSPaths_has_path_to(p, 5));

  DFSPaths_destroy(p);
  ListUndGraph_destroy(g);
}

TEST_CASE("tinyCG path_to")
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyCG.txt");
  DFSPaths *p = DFSPaths_create(g, 0);

  int path_size = -1;
  Vertex *path = DFSPaths_path_to(p, 5, &path_size);

  REQUIRE(4 == path_size);
  CHECK(0 == path[0]);
  CHECK(2 == path[1]);
  CHECK(3 == path[2]);
  CHECK(5 == path[3]);

  free(path);
  DFSPaths_destroy(p);
  ListUndGraph_destroy(g);
}

TEST_CASE("tinyG has_path_to")
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyG.txt");
  DFSPaths *p = DFSPaths_create(g, 0);

  CHECK(DFSPaths_has_path_to(p, 1));
  CHECK(DFSPaths_has_path_to(p, 2));
  CHECK(DFSPaths_has_path_to(p, 3));
  CHECK(DFSPaths_has_path_to(p, 4));
  CHECK(DFSPaths_has_path_to(p, 5));
  CHECK(DFSPaths_has_path_to(p, 6));

  CHECK_FALSE(DFSPaths_has_path_to(p, 7));
  CHECK_FALSE(DFSPaths_has_path_to(p, 8));

  CHECK_FALSE(DFSPaths_has_path_to(p, 9));
  CHECK_FALSE(DFSPaths_has_path_to(p, 10));
  CHECK_FALSE(DFSPaths_has_path_to(p, 11));
  CHECK_FALSE(DFSPaths_has_path_to(p, 12));

  DFSPaths_destroy(p);
  ListUndGraph_destroy(g);
}

TEST_CASE("tinyG path_to")
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyG.txt");
  DFSPaths *p = DFSPaths_create(g, 0);

  int path_size = -1;
  Vertex *path = DFSPaths_path_to(p, 5, &path_size);

  // ListUndGraph_show(g);
  REQUIRE(4 == path_size);
  CHECK(0 == path[0]);
  CHECK(6 == path[1]);
  CHECK(4 == path[2]);
  CHECK(5 == path[3]);

  free(path);
  DFSPaths_destroy(p);
  ListUndGraph_destroy(g);
}
