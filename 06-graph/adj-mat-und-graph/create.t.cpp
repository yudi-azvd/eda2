#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../lib/doctest.h"

#include "adj-mat-und-graph.h"

TEST_CASE("olá") {
  MatGraph* g = MatUndGraph_create(6);

  MatUndGraph_destroy(g);
}