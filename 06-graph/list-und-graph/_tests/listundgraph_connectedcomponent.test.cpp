#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "../listundgraph_search.h"
#include "../listundgraph_connectedcomponent.h"
#include "listundgraph_test_helper.h"

TEST_SUITE_BEGIN("listundgraph_connectedcomponent");

TEST_CASE("create and destroy")
{
  ConnectedComponent cc = ConnectedComponent_create(5);

  ConnectedComponent_destroy(&cc);
}

TEST_CASE("moj-viagem 00.in")
{
  ListUndGraph *g;
  fill_graph_moj_viagem_00in(&g);

  int cc_size = 0;
  ConnectedComponent *cc =
      ListUndGraph_connected_components(g, &cc_size);
  
  CHECK(cc_size == 2);
  qsort(cc, cc_size, sizeof(ConnectedComponent), cmp_cc_size);
  CHECK(4 == cc[cc_size-1].size);

  ConnectedComponent_destroy_array(cc, cc_size);
  ListUndGraph_destroy(g);
}

TEST_CASE("moj-viagem 01.in: greatest cc has min vertex = 2")
{
  ListUndGraph *g;
  fill_graph_moj_viagem_01in(&g);

  int cc_size = 0;
  ConnectedComponent *cc =
      ListUndGraph_connected_components(g, &cc_size);
  
  CHECK(cc_size == 3);

  qsort(cc, cc_size, sizeof(ConnectedComponent), cmp_cc_size);

  // debugar cc: *(*cc@cc_size)[0].vertices@(*cc@cc_size)[0].size
  CHECK(7 == cc[cc_size-1].size);
  CHECK(2 == cc[cc_size-1].smallest_vertex);

  ConnectedComponent_destroy_array(cc, cc_size);
  ListUndGraph_destroy(g);
}

TEST_CASE("moj-viagem 02.in: greatest cc has with min vertex = 1")
{
  ListUndGraph *g;
  fill_graph_moj_viagem_02in(&g);

  int cc_size = 0;
  ConnectedComponent *cc =
      ListUndGraph_connected_components(g, &cc_size);
  
  CHECK(cc_size == 3);

  qsort(cc, cc_size, sizeof(ConnectedComponent), cmp_cc_size);

  // debugar cc: *(*cc@cc_size)[0].vertices@(*cc@cc_size)[0].size
  CHECK(3 == cc[cc_size-1].size);
  bool last_or_first_to_last_has_min_vertex_equals_1 = (1 == cc[cc_size-1].smallest_vertex) || (1 == cc[cc_size-2].smallest_vertex);
  CHECK(last_or_first_to_last_has_min_vertex_equals_1);

  ConnectedComponent_destroy_array(cc, cc_size);
  ListUndGraph_destroy(g);
}

TEST_SUITE_END();