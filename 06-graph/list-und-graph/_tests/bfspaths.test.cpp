#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "../listundgraph_bfspaths.h"
#include "../listundgraph_file.h"

TEST_SUITE_BEGIN("listundgraph_bfspaths");

TEST_CASE("create and destroy")
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyCG.txt");
  BFSPaths *p = BFSPaths_create(g, 0);

  BFSPaths_destroy(p);
  ListUndGraph_destroy(g);
}

TEST_CASE("tinyCG has_path_to")
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyCG.txt");
  BFSPaths *p = BFSPaths_create(g, 0);

  CHECK(BFSPaths_has_path_to(p, 1));
  CHECK(BFSPaths_has_path_to(p, 2));
  CHECK(BFSPaths_has_path_to(p, 3));
  CHECK(BFSPaths_has_path_to(p, 4));
  CHECK(BFSPaths_has_path_to(p, 5));

  BFSPaths_destroy(p);
  ListUndGraph_destroy(g);
}

TEST_CASE("tinyCG path_to 5")
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyCG.txt");
  BFSPaths *p = BFSPaths_create(g, 0);

  int path_size = -1;
  Vertex *path_to_5 = BFSPaths_path_to(p, 5, &path_size);

  REQUIRE(2 == path_size);
  CHECK(0 == path_to_5[0]);
  CHECK(5 == path_to_5[1]);

  free(path_to_5);
  BFSPaths_destroy(p);
  ListUndGraph_destroy(g);
}

TEST_CASE("tinyCG path_to 4")
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyCG.txt");
  BFSPaths *p = BFSPaths_create(g, 0);

  int path_size = -1;
  Vertex *path_to_4 = BFSPaths_path_to(p, 4, &path_size);

  REQUIRE(3 == path_size);
  CHECK(0 == path_to_4[0]);
  CHECK(2 == path_to_4[1]);
  CHECK(4 == path_to_4[2]);

  free(path_to_4);
  BFSPaths_destroy(p);
  ListUndGraph_destroy(g);
}

TEST_CASE("tinyG has_path_to")
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyG.txt");
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
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyG.txt");
  BFSPaths *p = BFSPaths_create(g, 0);

  int path_size = -1;
  Vertex *path_to_4 = BFSPaths_path_to(p, 4, &path_size);

  REQUIRE(3 == path_size);
  CHECK(0 == path_to_4[0]);
  CHECK(6 == path_to_4[1]);
  CHECK(4 == path_to_4[2]);

  free(path_to_4);
  BFSPaths_destroy(p);
  ListUndGraph_destroy(g);
}
