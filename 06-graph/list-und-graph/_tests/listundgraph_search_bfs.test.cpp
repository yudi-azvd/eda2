#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "../listundgraph_search.h"
#include "listundgraph_test_helper.h"

TEST_SUITE_BEGIN("listundgraph_search_bfs");

TEST_CASE("tinyCG sedgewick-wayne")
{
  ListUndGraph *g;
  fill_graph_tinyCGtxt(&g);

  CHECK(ListUndGraph_vertices_count(g) == 6);
  CHECK(ListUndGraph_edges_count(g) == 8);

  int vertices = ListUndGraph_vertices_count(g);
  int *visited = create_visited(vertices);

  ListUndGraph_bfs(g, 0, visited);

  // Ordem em que os vértices foram visitados
  CHECK(0 == visited[0]);
  CHECK(1 == visited[2]);
  CHECK(2 == visited[1]);
  CHECK(3 == visited[5]);
  CHECK(4 == visited[3]);
  CHECK(5 == visited[4]);

  // ListUndGraph_show(g);

  free(visited);
  ListUndGraph_destroy(g);
}


TEST_SUITE_END();