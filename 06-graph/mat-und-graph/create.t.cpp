#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../lib/doctest.h"

#include "matundgraph.h"

TEST_CASE("mat und graph create and destroy") {
  MatUndGraph* g = MatUndGraph_create(6);

  MatUndGraph_destroy(g);
}