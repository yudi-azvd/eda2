#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "../listundgraph_search.h"
#include "../listundgraph_connectedcomponent.h"
#include "listundgraph_test_helper.h"

TEST_SUITE_BEGIN("listundgraph_connectedcomponent");

TEST_CASE("create and destroy")
{
  ConnectedComponent *cc = ConnectedComponent_create(5);

  ConnectedComponent_destroy(cc);
}

TEST_CASE("moj-viagem 00.in")
{
  ListUndGraph *g;
  fill_graph_moj_viagem_00in(&g);

  int cc_size = 0;
  ConnectedComponent **cc =
      ListUndGraph_connected_components(g, &cc_size);
  
  CHECK(cc_size == 2);

  ConnectedComponent_destroy_array(cc, cc_size);
  ListUndGraph_destroy(g);
}

TEST_SUITE_END();