#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "../listundgraph_cc.h"
#include "../listundgraph_file.h"

TEST_SUITE_BEGIN("listundgraph_cc");

TEST_CASE("create and destroy")
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyG.txt");
  CC *cc = CC_of(g);

  CC_destroy(cc);
  ListUndGraph_destroy(g);
}

TEST_CASE("tinyG id")
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyG.txt");
  CC *cc = CC_of(g);

  REQUIRE(3 == CC_count(cc));

  CHECK(0 == CC_id(cc, 0));
  CHECK(0 == CC_id(cc, 1));
  CHECK(0 == CC_id(cc, 2));
  CHECK(0 == CC_id(cc, 3));
  CHECK(0 == CC_id(cc, 4));
  CHECK(0 == CC_id(cc, 5));
  CHECK(0 == CC_id(cc, 6));

  CHECK(1 == CC_id(cc, 7));
  CHECK(1 == CC_id(cc, 8));

  CHECK(2 == CC_id(cc, 9));
  CHECK(2 == CC_id(cc, 10));
  CHECK(2 == CC_id(cc, 11));
  CHECK(2 == CC_id(cc, 12));

  CC_destroy(cc);
  ListUndGraph_destroy(g);
}

TEST_CASE("tinyG connected")
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyG.txt");
  CC *cc = CC_of(g);

  REQUIRE(3 == CC_count(cc));

  CHECK(CC_connected(cc, 2, 3));
  CHECK(CC_connected(cc, 6, 5));
  CHECK(CC_connected(cc, 7, 8));
  CHECK(CC_connected(cc, 12, 10));
  CHECK(CC_connected(cc, 11, 10));
  
  CHECK_FALSE(CC_connected(cc, 6, 9));
  CHECK_FALSE(CC_connected(cc, 5, 10));
  CHECK_FALSE(CC_connected(cc, 11, 7));

  CC_destroy(cc);
  ListUndGraph_destroy(g);
}