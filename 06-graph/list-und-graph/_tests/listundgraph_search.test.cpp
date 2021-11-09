#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "../listundgraph_search.h"
#include "listundgraph_test_helper.h"

TEST_SUITE_BEGIN("listundgraph_search");

TEST_CASE("tinyCG sedgewick-wayne")
{
  ListUndGraph *g;
  fill_graph_tinyCGtxt(&g);

  CHECK(ListUndGraph_vertices_count(g) == 6);
  CHECK(ListUndGraph_edges_count(g) == 8);

  int vertices = ListUndGraph_vertices_count(g);
  int *visited = create_visited(vertices);

  ListUndGraph_dfs_r(g, 0, visited);

  // Ordem em que os vértices foram visitados
  CHECK(0 == visited[0]);
  CHECK(1 == visited[2]);
  CHECK(2 == visited[1]);
  CHECK(3 == visited[3]);
  CHECK(4 == visited[5]);
  CHECK(5 == visited[4]);

  // ListUndGraph_show(g);

  free(visited);
  ListUndGraph_destroy(g);
}

TEST_CASE("tinyG sedgewick-wayne DFS on 1st cluster")
{
  ListUndGraph *g;
  fill_graph_tinyGtxt(&g);

  // ListUndGraph_show(g);

  CHECK(ListUndGraph_vertices_count(g) == 13);
  CHECK(ListUndGraph_edges_count(g) == 13);

  int vertices = ListUndGraph_vertices_count(g);
  int *visited = create_visited(vertices);

  ListUndGraph_dfs_r(g, 0, visited);

  // 1st cluster visited
  CHECK(is_visited(visited[0]));
  CHECK(is_visited(visited[1]));
  CHECK(is_visited(visited[2]));
  CHECK(is_visited(visited[6]));

  // 2nd cluster NOT visited
  CHECK_FALSE(is_visited(visited[7]));
  CHECK_FALSE(is_visited(visited[8]));

  // 3rd cluster NOT visited
  CHECK_FALSE(is_visited(visited[9]));
  CHECK_FALSE(is_visited(visited[10]));
  CHECK_FALSE(is_visited(visited[11]));
  CHECK_FALSE(is_visited(visited[12]));

  free(visited);
  ListUndGraph_destroy(g);
}

TEST_CASE("tinyG sedgewick-wayne DFS on 2nd cluster")
{
  ListUndGraph *g;
  fill_graph_tinyGtxt(&g);

  CHECK(ListUndGraph_vertices_count(g) == 13);
  CHECK(ListUndGraph_edges_count(g) == 13);

  int vertices = ListUndGraph_vertices_count(g);
  int *visited = create_visited(vertices);

  ListUndGraph_dfs_r(g, 7, visited);

  // 1st cluster NOT visited
  CHECK_FALSE(is_visited(visited[0]));
  CHECK_FALSE(is_visited(visited[1]));
  CHECK_FALSE(is_visited(visited[2]));
  CHECK_FALSE(is_visited(visited[3]));
  CHECK_FALSE(is_visited(visited[4]));
  CHECK_FALSE(is_visited(visited[5]));
  CHECK_FALSE(is_visited(visited[6]));

  // 2nd cluster visited
  CHECK(is_visited(visited[7]));
  CHECK(is_visited(visited[8]));

  // 2nd cluster NOT VISITED
  CHECK_FALSE(is_visited(visited[9]));
  CHECK_FALSE(is_visited(visited[10]));
  CHECK_FALSE(is_visited(visited[11]));
  CHECK_FALSE(is_visited(visited[12]));

  free(visited);
  ListUndGraph_destroy(g);
}

TEST_CASE("tinyG sedgewick-wayne DFS on 3rd cluster")
{
  ListUndGraph *g;
  fill_graph_tinyGtxt(&g);

  CHECK(ListUndGraph_vertices_count(g) == 13);
  CHECK(ListUndGraph_edges_count(g) == 13);

  int vertices = ListUndGraph_vertices_count(g);
  int *visited = create_visited(vertices);

  ListUndGraph_dfs_r(g, 12, visited);

  // 1st cluster NOT visited
  CHECK_FALSE(is_visited(visited[0]));
  CHECK_FALSE(is_visited(visited[1]));
  CHECK_FALSE(is_visited(visited[2]));
  CHECK_FALSE(is_visited(visited[3]));
  CHECK_FALSE(is_visited(visited[4]));
  CHECK_FALSE(is_visited(visited[5]));
  CHECK_FALSE(is_visited(visited[6]));

  // 2nd cluster NOT visited
  CHECK_FALSE(is_visited(visited[7]));
  CHECK_FALSE(is_visited(visited[8]));

  // 3rd cluster VISITED
  CHECK(is_visited(visited[9]));
  CHECK(is_visited(visited[10]));
  CHECK(is_visited(visited[11]));
  CHECK(is_visited(visited[12]));

  free(visited);
  ListUndGraph_destroy(g);
}

TEST_CASE("find connected components tinyG")
{
  ListUndGraph *g;
  fill_graph_tinyGtxt(&g);

  int connected_components = ListUndGraph_count_connected_components(g);

  CHECK(3 == connected_components);

  ListUndGraph_destroy(g);
}

TEST_CASE("connected components vector tinyG")
{
  ListUndGraph *g;
  fill_graph_tinyGtxt(&g);

  /*
  ListUndGraphConnComp {
    Vertex vertices[];
    int edges_count;
  }

  LUGConnComp* components = ListUndGraph_connected_components(g, &components_size);

  */

  ListUndGraph_destroy(g);
}

TEST_SUITE_END();