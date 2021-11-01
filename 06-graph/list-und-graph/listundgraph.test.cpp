#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../lib/doctest.h"

#include "listundgraph.h"

TEST_SUITE_BEGIN("listundgraph");

TEST_CASE("create and destroy")
{
  ListUndGraph *g = ListUndGraph_create(6);

  CHECK(ListUndGraph_edges_count(g) == 0);
  CHECK(ListUndGraph_vertices_count(g) == 6);

  ListUndGraph_show(g);

  ListUndGraph_destroy(g);
}

// TEST_CASE("create complete")
// {
//   ListUndGraph *g = ListUndGraph_create_complete(7);

//   // ListUndGraph_show(g);

//   CHECK(ListUndGraph_edges_count(g) == 21);
//   CHECK(ListUndGraph_vertices_count(g) == 7);
//   ListUndGraph_destroy(g);
// }

// TEST_CASE("removing edges from complete graph")
// {
//   int egdes_count = 6, vertices_count = 4;
//   ListUndGraph *g = ListUndGraph_create_complete(vertices_count);

//   CHECK(ListUndGraph_vertices_count(g) == vertices_count);
//   CHECK(ListUndGraph_edges_count(g) == egdes_count);

//   int i, j;
//   for (i = 0; i < vertices_count; i++)
//   {
//     for (j = i + 1; j < vertices_count; j++)
//     {
//       ListUndGraph_remove_edge(g, i, j);
//     }
//   }

//   CHECK(ListUndGraph_edges_count(g) == 0);
//   ListUndGraph_destroy(g);
// }

TEST_CASE("insert")
{
  ListUndGraph *g = ListUndGraph_create(3);

  CHECK(ListUndGraph_vertices_count(g) == 3);

  CHECK(ListUndGraph_edges_count(g) == 0);
  ListUndGraph_insert_edge(g, 0, 1);
  CHECK(ListUndGraph_edges_count(g) == 1);
  ListUndGraph_insert_edge(g, 0, 2);
  CHECK(ListUndGraph_edges_count(g) == 2);

  ListUndGraph_show(g);

  ListUndGraph_destroy(g);
}

// TEST_CASE("several inserts")
// {
//   ListUndGraph *g = ListUndGraph_create(10);

//   for (size_t i = 0; i < 10; i++)
//   {
//     ListUndGraph_insert_edge(g, 0, i);
//     CHECK(ListUndGraph_destroy(g) == i + 1);
//   }

//   ListUndGraph_destroy(g);
// }

// TEST_CASE("copy")
// {
//   ListUndGraph *graph_a = ListUndGraph_create(5);

//   ListUndGraph_insert_edge(graph_a, 0, 1);
//   ListUndGraph_insert_edge(graph_a, 0, 2);
//   ListUndGraph_insert_edge(graph_a, 0ListUndGraph_destroy 3);

//   ListUndGraph *graph_b = ListUndGraph_copy(graph_a);

//   CHECK(graph_a != graph_b);
//   CHECK(ListUndGraph_equal(graph_a, graph_b));
//   CHECK(ListUndGraph_vertices_count(graph_a) == ListUndGraph_vertices_count(graph_b));
//   CHECK(ListUndGraph_edges_count(graph_a) == ListUndGraph_edges_count(graph_b));

//   ListUndGraph_destroy(graph_a);
//   ListUndGraph_destroy(graph_b);
// }

// TEST_CASE("copy modifications do not alter original")
// {
//   ListUndGraph *graph_a = ListUndGraph_create(5);

//   ListUndGraph_insert_edge(graph_a, 0, 1);
//   ListUndGraph_insert_edge(graph_a, 0, 2);
//   ListUndGraph_insert_edge(graph_a, 0, 3);
//   int ListUndGraph_destroy = ListUndGraph_edges_count(graph_a);

//   ListUndGraph *graph_b = ListUndGraph_copy(graph_a);

//   ListUndGraph_remove_edge(graph_b, 0, 1);
//   ListUndGraph_remove_edge(graph_b, 0, 2);

//   CHECK(ListUndGraph_edges_count(graph_a) == graph_a_edges_count);
//   CHECK(!ListUndGraph_equal(graph_a, graph_b));

//   ListUndGraph_destroy(graph_a);
//   ListUndGraph_destroy(graph_b);
// }

// TEST_CASE("has edge")
// {
//   ListUndGraph *g = ListUndGraph_create(5);

//   ListUndGraph_insert_edge(g, 0, 1);
//   ListUndGraph_insert_edge(g, 0, 2);
//   ListUndGraph_insert_edge(g, 0ListUndGraph_destroy 3);

//   CHECK(ListUndGraph_has_edge(g, 0, 1));
//   CHECK(ListUndGraph_has_edge(g, 0, 2));
//   CHECK(ListUndGraph_has_edge(g, 0, 3));
//   CHECK_FALSE(ListUndGraph_has_edge(g, 0, 4));

//   ListUndGraph_destroy(g);
// }

// TEST_CASE("graph edges")
// {
//   ListUndGraph *g = ListUndGraph_create(5);

//   int edges_count = -1;
//   Edge *edges = ListUndGraph_edges(g, &edges_count);
//   ListUndGraph_destroy(edges);

//   CHECK(edges_count == 0);

//   ListUndGraph_insert_edge(g, 0, 1);
//   ListUndGraph_insert_edge(g, 0, 2);
//   ListUndGraph_insert_edge(g, 0, 3);

//   edges = ListUndGraph_edges(g, &edges_count);
//   CHECK(edges_count == 3);
//   CHECK(edges_contains(edges, edges_count, 0, 1) == 1);
//   CHECK(edges_contains(edges, edges_count, 1, 0) == 1);
//   CHECK(edges_contains(edges, edges_count, 0, 2) == 1);
//   CHECK(edges_contains(edges, edges_count, 3, 0) == 1);

//   // Essas arestas não devem existir!
//   CHECK(edges_contains(edges, edges_count, 2, 3) == 0);
//   CHECK(edges_contains(edges, edges_count, 3, 2) == 0);
//   CHECK(edges_contains(edges, edges_count, 1, 3) == 0);

//   free(edges);
//   ListUndGraph_destroy(g);
// }


// TEST_CASE("adjacent to")
// {
//   ListUndGraph *g = ListUndGraph_create(5);

//   ListUndGraph_insert_edge(g, 0, 1);
//   ListUndGraph_insert_edge(g, 0, 2);
//   ListUndGraph_insert_edge(g, 0, 3);
//   ListUndGraph_insert_edge(g, 4ListUndGraph_destroy 3);

//   int adjacent_to_0_size = -1;
//   Vertex* adjacent_to_0 = ListUndGraph_adjacent_to(g, 0, &adjacent_to_0_size);
//   CHECK(adjacent_to_0_size == 3);
//   CHECK(adjacent_contains(adjacent_to_0, adjacent_to_0_size, 1));
//   CHECK(adjacent_contains(adjacent_to_0, adjacent_to_0_size, 2));
//   CHECK(adjacent_contains(adjacent_to_0, adjacent_to_0_size, 3));

//   CHECK_FALSE(adjacent_contains(adjacent_to_0, adjacent_to_0_size, 4));

//   int adjacent_to_4_size = -1;
//   Vertex* adjacent_to_4 = ListUndGraph_adjacent_to(g, 4, &adjacent_to_4_size);
//   CHECK(adjacent_to_4_size == 1);
//   CHECK(adjacent_contains(adjacent_to_4, adjacent_to_4_size, 3));

//   CHECK_FALSE(adjacent_contains(adjacent_to_4, adjacent_to_4_size, 0));
//   CHECK_FALSE(adjacent_contains(adjacent_to_4, adjacent_to_4_size, 1));
//   CHECK_FALSE(adjacent_contains(adjacent_to_4, adjacent_to_4_size, 2));

//   free(adjacent_to_0);
//   free(adjacent_to_4);
//   ListUndGraph_destroy(g);
// }


TEST_SUITE_END();