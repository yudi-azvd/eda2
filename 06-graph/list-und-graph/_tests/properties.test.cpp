#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "../listundgraph_bfspaths.h"
#include "../listundgraph_properties.h"
#include "../listundgraph_file.h"

TEST_SUITE_BEGIN("listundgraph_properties");

TEST_CASE("create and destroy")
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyCG.txt");
  Properties *props = Properties_of(g);

  Properties_destroy(props);
  ListUndGraph_destroy(g);
}

TEST_CASE("tinyCG props")
{
  ListUndGraph *g = ListUndGraph_create_from_file("algs4-data/tinyCG.txt");
  Properties *props = Properties_of(g);

  CHECK(2 == Properties_eccentricity(props, 0));
  CHECK(2 == Properties_eccentricity(props, 1));

  CHECK(2 == Properties_diameter(props));
  CHECK(2 == Properties_radius(props));
  CHECK(0 == Properties_center(props));

  Properties_destroy(props);
  ListUndGraph_destroy(g);
}

// https://github.com/reneargento/algorithms-sedgewick-wayne/blob/b08ac963700d323db79d21cbe7368cdfb9c8212b/src/chapter4/section1/Exercise16.java#L72
TEST_CASE("reneargento example props")
{
  ListUndGraph *g = ListUndGraph_create(11);
  for (size_t i = 1; i < 11; i++)
    ListUndGraph_insert_edge(g, i-1, i);

  // ListUndGraph_show(g);  
  Properties *props = Properties_of(g);

  CHECK(10 == Properties_eccentricity(props, 0));
  CHECK(9 == Properties_eccentricity(props, 1));

  CHECK(10 == Properties_diameter(props));
  CHECK(5 == Properties_radius(props));
  CHECK(5 == Properties_center(props));

  Properties_destroy(props);
  ListUndGraph_destroy(g);
}
