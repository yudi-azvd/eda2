#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../lib/doctest.h"

#include "matundgraph.h"

TEST_SUITE_BEGIN("matundgraph");

TEST_CASE("create and destroy")
{
  MatUndGraph *g = MatUndGraph_create(6);

  CHECK(MatUndGraph_edges_count(g) == 0);
  CHECK(MatUndGraph_vertices_count(g) == 6);

  MatUndGraph_destroy(g);
}

TEST_CASE("create complete")
{
  MatUndGraph *g = MatUndGraph_create_complete(7);

  // MatUndGraph_show(g);

  CHECK(MatUndGraph_edges_count(g) == 21);
  CHECK(MatUndGraph_vertices_count(g) == 7);
  MatUndGraph_destroy(g);
}

TEST_CASE("removing edges from complete graph")
{
  int egdes_count = 6, vertices_count = 4;
  MatUndGraph *g = MatUndGraph_create_complete(vertices_count);

  CHECK(MatUndGraph_vertices_count(g) == vertices_count);
  CHECK(MatUndGraph_edges_count(g) == egdes_count);

  int i, j;
  for (i = 0; i < vertices_count; i++)
  {
    for (j = i + 1; j < vertices_count; j++)
    {
      MatUndGraph_remove_edge(g, i, j);
    }
  }

  CHECK(MatUndGraph_edges_count(g) == 0);
  MatUndGraph_destroy(g);
}

TEST_CASE("insert")
{
  MatUndGraph *g = MatUndGraph_create(3);

  CHECK(MatUndGraph_edges_count(g) == 0);
  MatUndGraph_insert_edge(g, 0, 1);
  CHECK(MatUndGraph_edges_count(g) == 1);
  MatUndGraph_insert_edge(g, 0, 2);
  CHECK(MatUndGraph_edges_count(g) == 2);

  MatUndGraph_destroy(g);
}

TEST_CASE("several inserts")
{
  MatUndGraph *g = MatUndGraph_create(10);

  for (size_t i = 0; i < 10; i++)
  {
    MatUndGraph_insert_edge(g, 0, i);
    CHECK(MatUndGraph_edges_count(g) == i + 1);
  }

  MatUndGraph_destroy(g);
}

TEST_CASE("copy")
{
  MatUndGraph *graph_a = MatUndGraph_create(5);

  MatUndGraph_insert_edge(graph_a, 0, 1);
  MatUndGraph_insert_edge(graph_a, 0, 2);
  MatUndGraph_insert_edge(graph_a, 0, 3);

  MatUndGraph *graph_b = MatUndGraph_copy(graph_a);

  CHECK(graph_a != graph_b);
  CHECK(MatUndGraph_equal(graph_a, graph_b));
  CHECK(MatUndGraph_vertices_count(graph_a) == MatUndGraph_vertices_count(graph_b));
  CHECK(MatUndGraph_edges_count(graph_a) == MatUndGraph_edges_count(graph_b));

  MatUndGraph_destroy(graph_a);
  MatUndGraph_destroy(graph_b);
}

TEST_CASE("copy modifications do not alter original")
{
  MatUndGraph *graph_a = MatUndGraph_create(5);

  MatUndGraph_insert_edge(graph_a, 0, 1);
  MatUndGraph_insert_edge(graph_a, 0, 2);
  MatUndGraph_insert_edge(graph_a, 0, 3);
  int graph_a_edges_count = MatUndGraph_edges_count(graph_a);

  MatUndGraph *graph_b = MatUndGraph_copy(graph_a);

  MatUndGraph_remove_edge(graph_b, 0, 1);
  MatUndGraph_remove_edge(graph_b, 0, 2);

  CHECK(MatUndGraph_edges_count(graph_a) == graph_a_edges_count);
  CHECK(!MatUndGraph_equal(graph_a, graph_b));

  MatUndGraph_destroy(graph_a);
  MatUndGraph_destroy(graph_b);
}

TEST_CASE("has edge")
{
  MatUndGraph *g = MatUndGraph_create(5);

  MatUndGraph_insert_edge(g, 0, 1);
  MatUndGraph_insert_edge(g, 0, 2);
  MatUndGraph_insert_edge(g, 0, 3);

  CHECK(MatUndGraph_has_edge(g, 0, 1));
  CHECK(MatUndGraph_has_edge(g, 0, 2));
  CHECK(MatUndGraph_has_edge(g, 0, 3));
  CHECK_FALSE(MatUndGraph_has_edge(g, 0, 4));

  MatUndGraph_destroy(g);
}

TEST_SUITE_END();