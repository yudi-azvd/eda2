#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "../matdirgraph_util.h"
#include "matdirgraph_test_helper.h"

TEST_SUITE_BEGIN("matdirgraph_util");

TEST_CASE("tinyDG sedgewick-wayne, sources: 1")
{
  MatDirGraph *g;
  fill_graph_tinyDGtxt(&g);

  CHECK(MatDirGraph_vertices_count(g) == 13);
  CHECK(MatDirGraph_edges_count(g) == 22);

  int vertices = MatDirGraph_vertices_count(g);
  int *visited = create_visited(vertices);

  const int SOURCE = 1;
  MatDirGraph_dfs_r(g, SOURCE, visited);

  CHECK(is_visited(visited[1]));
  CHECK_FALSE(is_visited(visited[0]));
  CHECK_FALSE(is_visited(visited[2]));

  free(visited);
  MatDirGraph_destroy(g);
}

TEST_CASE("tinyDG sedgewick-wayne, sources: 2")
{
  MatDirGraph *g;
  fill_graph_tinyDGtxt(&g);

  CHECK(MatDirGraph_vertices_count(g) == 13);
  CHECK(MatDirGraph_edges_count(g) == 22);

  int vertices = MatDirGraph_vertices_count(g);
  int *visited = create_visited(vertices);

  const int SOURCE = 2;
  MatDirGraph_dfs_r(g, SOURCE, visited);

  CHECK(is_visited(visited[0]));
  CHECK(is_visited(visited[1]));
  CHECK(is_visited(visited[2]));
  CHECK(is_visited(visited[3]));
  CHECK(is_visited(visited[4]));
  CHECK(is_visited(visited[5]));

  CHECK_FALSE(is_visited(visited[6]));

  free(visited);
  MatDirGraph_destroy(g);
}

TEST_CASE("tinyDG sedgewick-wayne, sources: 1 2 6")
{
  MatDirGraph *g;
  fill_graph_tinyDGtxt(&g);

  CHECK(MatDirGraph_vertices_count(g) == 13);
  CHECK(MatDirGraph_edges_count(g) == 22);

  int vertices = MatDirGraph_vertices_count(g);
  int *visited = create_visited(vertices);

  const int SOURCE = 2;
  MatDirGraph_dfs_r(g, 1, visited);
  MatDirGraph_dfs_r(g, 2, visited);
  MatDirGraph_dfs_r(g, 6, visited);

  CHECK(is_visited(visited[0]));
  CHECK(is_visited(visited[1]));
  CHECK(is_visited(visited[2]));
  CHECK(is_visited(visited[3]));
  CHECK(is_visited(visited[4]));
  CHECK(is_visited(visited[5]));
  CHECK(is_visited(visited[6]));
  CHECK(is_visited(visited[9]));
  CHECK(is_visited(visited[10]));
  CHECK(is_visited(visited[11]));
  CHECK(is_visited(visited[12]));

  CHECK_FALSE(is_visited(visited[7]));

  free(visited);
  MatDirGraph_destroy(g);
}

TEST_CASE("tc create and destroy")
{
  MatDirGraph *g = MatDirGraph_create(2);
  TC* tc = TC_of(g);

  TC_destroy(tc);
  MatDirGraph_destroy(g);
}

TEST_CASE("tc simple example")
{
  // tirado dessa aula: https://youtu.be/w6w0LW_7Ins?t=5502
  MatDirGraph *g = MatDirGraph_create(4);

  MatDirGraph_insert_edge(g, 1, 0);
  MatDirGraph_insert_edge(g, 1, 3);
  MatDirGraph_insert_edge(g, 2, 3);
  MatDirGraph_insert_edge(g, 0, 2);

  TC* tc = TC_of(g);

  CHECK(TC_reaches(tc, 1, 0));
  CHECK(TC_reaches(tc, 1, 2));
  CHECK(TC_reaches(tc, 0, 3));
  CHECK(TC_reaches(tc, 2, 3));
  
  CHECK_FALSE(TC_reaches(tc, 3, 1));
  CHECK_FALSE(TC_reaches(tc, 3, 0));
  CHECK_FALSE(TC_reaches(tc, 3, 2));

  // TC_show(tc);

  TC_destroy(tc);
  MatDirGraph_destroy(g);
}

TEST_SUITE_END();