#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../lib/doctest.h"

#include "matundgraph_test_helper.h"
#include "matundgraph_search.h"

TEST_SUITE_BEGIN("matundgraph_search");

TEST_CASE("tinyCG sedgewick-wayne")
{
  MatUndGraph *g;
  fill_graph_tinyCGtxt(&g);

  CHECK(MatUndGraph_vertices_count(g) == 6);
  CHECK(MatUndGraph_edges_count(g) == 8);

  int vertices = MatUndGraph_vertices_count(g);
  int *visited = create_visited(vertices);

  MatUndGraph_dfs_r(g, 0, visited);

  // Ordem em que os vértices foram visitados
  CHECK(is_visited(visited[0]));
  CHECK(is_visited(visited[2]));
  CHECK(is_visited(visited[1]));
  CHECK(is_visited(visited[3]));
  CHECK(is_visited(visited[5]));
  CHECK(is_visited(visited[4]));

  // MatUndGraph_show(g);

  free(visited);
  MatUndGraph_destroy(g);
}


TEST_CASE("tinyG sedgewick-wayne DFS on 1st cluster") {
  MatUndGraph *g;
  fill_graph_tinyGtxt(&g);

  // MatUndGraph_show(g);

  CHECK(MatUndGraph_vertices_count(g) == 13);
  CHECK(MatUndGraph_edges_count(g) == 13);

  int vertices = MatUndGraph_vertices_count(g);
  int *visited = create_visited(vertices);

  MatUndGraph_dfs_r(g, 0, visited);

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
  MatUndGraph_destroy(g);
}


TEST_CASE("tinyG sedgewick-wayne DFS on 2nd cluster") {
  MatUndGraph *g;
  fill_graph_tinyGtxt(&g);

  CHECK(MatUndGraph_vertices_count(g) == 13);
  CHECK(MatUndGraph_edges_count(g) == 13);

  int vertices = MatUndGraph_vertices_count(g);
  int *visited = create_visited(vertices);

  MatUndGraph_dfs_r(g, 7, visited);
  
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
  MatUndGraph_destroy(g);
}


TEST_CASE("tinyG sedgewick-wayne DFS on 3rd cluster") {
  MatUndGraph *g;
  fill_graph_tinyGtxt(&g);

  CHECK(MatUndGraph_vertices_count(g) == 13);
  CHECK(MatUndGraph_edges_count(g) == 13);

  int vertices = MatUndGraph_vertices_count(g);
  int *visited = create_visited(vertices);

  MatUndGraph_dfs_r(g, 12, visited);
  
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
  MatUndGraph_destroy(g);
}

// TEST_CASE("find connected components tinyG") {
//   MatUndGraph* g;
//   fill_graph_tinyGtxt(&g);

//   int connected_components = MatUndGraph_count_connected_components(g);

//   CHECK(3 == connected_components);

//   MatUndGraph_destroy(g);
// }

TEST_SUITE_END();