#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "../listdirgraph.h"

TEST_SUITE_BEGIN("listdirgraph");

TEST_CASE("create and destroy")
{
  ListDirGraph *g = ListDirGraph_create(6);

  CHECK(ListDirGraph_edges_count(g) == 0);
  CHECK(ListDirGraph_vertices_count(g) == 6);

  // ListDirGraph_show(g);

  ListDirGraph_destroy(g);
}

// TEST_CASE("create complete")
// {
//   ListDirGraph *g = ListDirGraph_create_complete(7);

//   // ListDirGraph_show(g);

//   CHECK(ListDirGraph_edges_count(g) == 21);
//   CHECK(ListDirGraph_vertices_count(g) == 7);
//   ListDirGraph_destroy(g);
// }

// TEST_CASE("removing edges from complete graph")
// {
//   int egdes_count = 6, vertices_count = 4;
//   ListDirGraph *g = ListDirGraph_create_complete(vertices_count);

//   CHECK(ListDirGraph_vertices_count(g) == vertices_count);
//   CHECK(ListDirGraph_edges_count(g) == egdes_count);

//   int i, j;
//   for (i = 0; i < vertices_count; i++)
//   {
//     for (j = i + 1; j < vertices_count; j++)
//     {
//       ListDirGraph_remove_edge(g, i, j);
//     }
//   }

//   CHECK(ListDirGraph_edges_count(g) == 0);
//   ListDirGraph_destroy(g);
// }

TEST_CASE("insert")
{
  ListDirGraph *g = ListDirGraph_create(3);

  CHECK(ListDirGraph_vertices_count(g) == 3);

  CHECK(ListDirGraph_edges_count(g) == 0);
  ListDirGraph_insert_edge(g, 0, 1);
  CHECK(ListDirGraph_edges_count(g) == 1);
  ListDirGraph_insert_edge(g, 0, 2);
  CHECK(ListDirGraph_edges_count(g) == 2);

  // ListDirGraph_show(g);

  ListDirGraph_destroy(g);
}

TEST_CASE("two way insert")
{
  ListDirGraph *g = ListDirGraph_create(6);

  CHECK(ListDirGraph_vertices_count(g) == 6);
  CHECK(ListDirGraph_edges_count(g) == 0);

  ListDirGraph_insert_edge(g, 0, 1);
  CHECK(ListDirGraph_edges_count(g) == 1);
  ListDirGraph_insert_edge(g, 1, 0);
  CHECK(ListDirGraph_edges_count(g) == 2);
  ListDirGraph_insert_edge(g, 0, 2);
  CHECK(ListDirGraph_edges_count(g) == 3);
  ListDirGraph_insert_edge(g, 2, 0);
  CHECK(ListDirGraph_edges_count(g) == 4);

  // ListDirGraph_show(g);

  ListDirGraph_destroy(g);
}

TEST_CASE("several inserts")
{
  ListDirGraph *g = ListDirGraph_create(10);

  for (size_t i = 0; i < 10; i++)
  {
    ListDirGraph_insert_edge(g, 0, i);
    CHECK(ListDirGraph_edges_count(g) == i + 1);
  }

  ListDirGraph_destroy(g);
}

// TEST_CASE("copy")
// {
//   ListDirGraph *graph_a = ListDirGraph_create(5);

//   ListDirGraph_insert_edge(graph_a, 0, 1);
//   ListDirGraph_insert_edge(graph_a, 0, 2);
//   ListDirGraph_insert_edge(graph_a, 0, 3);

//   ListDirGraph *graph_b = ListDirGraph_copy(graph_a);

//   CHECK(graph_a != graph_b);
//   CHECK(ListDirGraph_equal(graph_a, graph_b));
//   CHECK(ListDirGraph_vertices_count(graph_a) == ListDirGraph_vertices_count(graph_b));
//   CHECK(ListDirGraph_edges_count(graph_a) == ListDirGraph_edges_count(graph_b));

//   ListDirGraph_destroy(graph_a);
//   ListDirGraph_destroy(graph_b);
// }

// TEST_CASE("copy modifications do not alter original")
// {
//   ListDirGraph *graph_a = ListDirGraph_create(5);

//   ListDirGraph_insert_edge(graph_a, 0, 1);
//   ListDirGraph_insert_edge(graph_a, 0, 2);
//   ListDirGraph_insert_edge(graph_a, 0, 3);
//   int ListDirGraph_destroy = ListDirGraph_edges_count(graph_a);

//   ListDirGraph *graph_b = ListDirGraph_copy(graph_a);

//   ListDirGraph_remove_edge(graph_b, 0, 1);
//   ListDirGraph_remove_edge(graph_b, 0, 2);

//   CHECK(ListDirGraph_edges_count(graph_a) == graph_a_edges_count);
//   CHECK(!ListDirGraph_equal(graph_a, graph_b));

//   ListDirGraph_destroy(graph_a);
//   ListDirGraph_destroy(graph_b);
// }

TEST_CASE("has edge")
{
  ListDirGraph *g = ListDirGraph_create(5);

  ListDirGraph_insert_edge(g, 0, 1);
  ListDirGraph_insert_edge(g, 0, 2);
  ListDirGraph_insert_edge(g, 0, 3);

  CHECK(ListDirGraph_has_edge(g, 0, 1));
  CHECK(ListDirGraph_has_edge(g, 0, 2));
  CHECK(ListDirGraph_has_edge(g, 0, 3));

  CHECK_FALSE(ListDirGraph_has_edge(g, 1, 0));
  CHECK_FALSE(ListDirGraph_has_edge(g, 2, 0));
  CHECK_FALSE(ListDirGraph_has_edge(g, 3, 0));

  CHECK_FALSE(ListDirGraph_has_edge(g, 0, 4));

  ListDirGraph_destroy(g);
}

// TEST_CASE("graph edges")
// {
//   ListDirGraph *g = ListDirGraph_create(5);

//   int edges_count = -1;
//   Edge *edges = ListDirGraph_edges(g, &edges_count);
//   ListDirGraph_destroy(edges);

//   CHECK(edges_count == 0);

//   ListDirGraph_insert_edge(g, 0, 1);
//   ListDirGraph_insert_edge(g, 0, 2);
//   ListDirGraph_insert_edge(g, 0, 3);

//   edges = ListDirGraph_edges(g, &edges_count);
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
//   ListDirGraph_destroy(g);
// }

// TEST_CASE("adjacent to")
// {
//   ListDirGraph *g = ListDirGraph_create(5);

//   ListDirGraph_insert_edge(g, 0, 1);
//   ListDirGraph_insert_edge(g, 0, 2);
//   ListDirGraph_insert_edge(g, 0, 3);
//   ListDirGraph_insert_edge(g, 4, 3);

//   int adjacent_to_0_size = -1;
//   Vertex* adjacent_to_0 = ListDirGraph_adjacent_to(g, 0, &adjacent_to_0_size);
//   CHECK(adjacent_to_0_size == 3);
//   CHECK(adjacent_contains(adjacent_to_0, adjacent_to_0_size, 1));
//   CHECK(adjacent_contains(adjacent_to_0, adjacent_to_0_size, 2));
//   CHECK(adjacent_contains(adjacent_to_0, adjacent_to_0_size, 3));

//   CHECK_FALSE(adjacent_contains(adjacent_to_0, adjacent_to_0_size, 4));

//   int adjacent_to_4_size = -1;
//   Vertex* adjacent_to_4 = ListDirGraph_adjacent_to(g, 4, &adjacent_to_4_size);
//   CHECK(adjacent_to_4_size == 1);
//   CHECK(adjacent_contains(adjacent_to_4, adjacent_to_4_size, 3));

//   CHECK_FALSE(adjacent_contains(adjacent_to_4, adjacent_to_4_size, 0));
//   CHECK_FALSE(adjacent_contains(adjacent_to_4, adjacent_to_4_size, 1));
//   CHECK_FALSE(adjacent_contains(adjacent_to_4, adjacent_to_4_size, 2));

//   free(adjacent_to_0);
//   free(adjacent_to_4);
//   ListDirGraph_destroy(g);
// }

TEST_SUITE_END();