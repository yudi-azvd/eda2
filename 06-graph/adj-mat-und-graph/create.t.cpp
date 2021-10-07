#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../lib/doctest.h"

#include "adj-mat-und-graph.h"

TEST_CASE("olá") {
  AdjMatGraph* g = AdjMatUndGraph_create(6);

  AdjMatUndGraph_destroy(g);
}