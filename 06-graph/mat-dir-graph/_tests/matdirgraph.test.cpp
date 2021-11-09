#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "../matdirgraph.h"
#include "matdirgraph_test_helper.h"

TEST_SUITE_BEGIN("matdirgraph");

TEST_CASE("create and destroy")
{
  MatDirGraph *g = MatDirGraph_create(6);

  CHECK(MatDirGraph_edges_count(g) == 0);
  CHECK(MatDirGraph_vertices_count(g) == 6);

  MatDirGraph_destroy(g);
}

TEST_CASE("create complete")
{
  MatDirGraph *g = MatDirGraph_create_complete(7);

  // MatDirGraph_show(g);

  CHECK(MatDirGraph_edges_count(g) == 21);
  CHECK(MatDirGraph_vertices_count(g) == 7);
  MatDirGraph_destroy(g);
}

TEST_CASE("removing edges from complete graph")
{
  int egdes_count = 6, vertices_count = 4;
  MatDirGraph *g = MatDirGraph_create_complete(vertices_count);

  CHECK(MatDirGraph_vertices_count(g) == vertices_count);
  CHECK(MatDirGraph_edges_count(g) == egdes_count);

  int i, j;
  for (i = 0; i < vertices_count; i++)
  {
    for (j = i + 1; j < vertices_count; j++)
    {
      MatDirGraph_remove_edge(g, i, j);
    }
  }

  CHECK(MatDirGraph_edges_count(g) == 0);
  MatDirGraph_destroy(g);
}

TEST_CASE("insert")
{
  MatDirGraph *g = MatDirGraph_create(3);

  CHECK(MatDirGraph_edges_count(g) == 0);
  MatDirGraph_insert_edge(g, 0, 1);
  CHECK(MatDirGraph_edges_count(g) == 1);
  MatDirGraph_insert_edge(g, 0, 2);
  CHECK(MatDirGraph_edges_count(g) == 2);

  MatDirGraph_destroy(g);
}

TEST_CASE("two way insert")
{
  MatDirGraph *g = MatDirGraph_create(6);

  CHECK(MatDirGraph_vertices_count(g) == 6);
  CHECK(MatDirGraph_edges_count(g) == 0);

  MatDirGraph_insert_edge(g, 0, 1);
  CHECK(MatDirGraph_edges_count(g) == 1);
  MatDirGraph_insert_edge(g, 1, 0);
  CHECK(MatDirGraph_edges_count(g) == 2);
  MatDirGraph_insert_edge(g, 0, 2);
  CHECK(MatDirGraph_edges_count(g) == 3);
  MatDirGraph_insert_edge(g, 2, 0);
  CHECK(MatDirGraph_edges_count(g) == 4);

  // MatDirGraph_show(g);

  MatDirGraph_destroy(g);
}

TEST_CASE("several inserts")
{
  MatDirGraph *g = MatDirGraph_create(10);

  for (size_t i = 0; i < 10; i++)
  {
    MatDirGraph_insert_edge(g, 0, i);
    CHECK(MatDirGraph_edges_count(g) == i + 1);
  }

  MatDirGraph_destroy(g);
}

TEST_CASE("copy")
{
  MatDirGraph *graph_a = MatDirGraph_create(5);

  MatDirGraph_insert_edge(graph_a, 0, 1);
  MatDirGraph_insert_edge(graph_a, 0, 2);
  MatDirGraph_insert_edge(graph_a, 0, 3);

  MatDirGraph *graph_b = MatDirGraph_copy(graph_a);

  CHECK(graph_a != graph_b);
  CHECK(MatDirGraph_equal(graph_a, graph_b));
  CHECK(MatDirGraph_vertices_count(graph_a) == MatDirGraph_vertices_count(graph_b));
  CHECK(MatDirGraph_edges_count(graph_a) == MatDirGraph_edges_count(graph_b));

  MatDirGraph_destroy(graph_a);
  MatDirGraph_destroy(graph_b);
}

TEST_CASE("copy modifications do not alter original")
{
  MatDirGraph *graph_a = MatDirGraph_create(5);

  MatDirGraph_insert_edge(graph_a, 0, 1);
  MatDirGraph_insert_edge(graph_a, 0, 2);
  MatDirGraph_insert_edge(graph_a, 0, 3);
  int graph_a_edges_count = MatDirGraph_edges_count(graph_a);

  MatDirGraph *graph_b = MatDirGraph_copy(graph_a);

  MatDirGraph_remove_edge(graph_b, 0, 1);
  MatDirGraph_remove_edge(graph_b, 0, 2);

  CHECK(MatDirGraph_edges_count(graph_a) == graph_a_edges_count);
  CHECK(!MatDirGraph_equal(graph_a, graph_b));

  MatDirGraph_destroy(graph_a);
  MatDirGraph_destroy(graph_b);
}

TEST_CASE("has edge")
{
  MatDirGraph *g = MatDirGraph_create(5);

  MatDirGraph_insert_edge(g, 0, 1);
  MatDirGraph_insert_edge(g, 0, 2);
  MatDirGraph_insert_edge(g, 0, 3);

  CHECK(MatDirGraph_has_edge(g, 0, 1));
  CHECK(MatDirGraph_has_edge(g, 0, 2));
  CHECK(MatDirGraph_has_edge(g, 0, 3));
  CHECK_FALSE(MatDirGraph_has_edge(g, 0, 4));

  MatDirGraph_destroy(g);
}

TEST_CASE("graph edges")
{
  MatDirGraph *g = MatDirGraph_create(5);

  int edges_count = -1;
  Edge *edges = MatDirGraph_edges(g, &edges_count);
  free(edges);

  CHECK(edges_count == 0);

  MatDirGraph_insert_edge(g, 0, 1);
  MatDirGraph_insert_edge(g, 0, 2);
  MatDirGraph_insert_edge(g, 0, 3);

  edges = MatDirGraph_edges(g, &edges_count);
  CHECK(edges_count == 3);
  CHECK(edges_contains(edges, edges_count, 0, 1) == 1);
  CHECK(edges_contains(edges, edges_count, 1, 0) == 1);
  CHECK(edges_contains(edges, edges_count, 0, 2) == 1);
  CHECK(edges_contains(edges, edges_count, 3, 0) == 1);

  // Essas arestas não devem existir!
  CHECK(edges_contains(edges, edges_count, 2, 3) == 0);
  CHECK(edges_contains(edges, edges_count, 3, 2) == 0);
  CHECK(edges_contains(edges, edges_count, 1, 3) == 0);

  free(edges);
  MatDirGraph_destroy(g);
}


TEST_CASE("adjacent to")
{
  MatDirGraph *g = MatDirGraph_create(5);

  MatDirGraph_insert_edge(g, 0, 1);
  MatDirGraph_insert_edge(g, 0, 2);
  MatDirGraph_insert_edge(g, 0, 3);
  MatDirGraph_insert_edge(g, 4, 3);

  int adjacent_to_0_size = -1;
  Vertex* adjacent_to_0 = MatDirGraph_adjacent_to(g, 0, &adjacent_to_0_size);
  CHECK(adjacent_to_0_size == 3);
  CHECK(adjacent_contains(adjacent_to_0, adjacent_to_0_size, 1));
  CHECK(adjacent_contains(adjacent_to_0, adjacent_to_0_size, 2));
  CHECK(adjacent_contains(adjacent_to_0, adjacent_to_0_size, 3));

  CHECK_FALSE(adjacent_contains(adjacent_to_0, adjacent_to_0_size, 4));

  int adjacent_to_4_size = -1;
  Vertex* adjacent_to_4 = MatDirGraph_adjacent_to(g, 4, &adjacent_to_4_size);
  CHECK(adjacent_to_4_size == 1);
  CHECK(adjacent_contains(adjacent_to_4, adjacent_to_4_size, 3));

  CHECK_FALSE(adjacent_contains(adjacent_to_4, adjacent_to_4_size, 0));
  CHECK_FALSE(adjacent_contains(adjacent_to_4, adjacent_to_4_size, 1));
  CHECK_FALSE(adjacent_contains(adjacent_to_4, adjacent_to_4_size, 2));

  free(adjacent_to_0);
  free(adjacent_to_4);
  MatDirGraph_destroy(g);
}


TEST_SUITE_END();