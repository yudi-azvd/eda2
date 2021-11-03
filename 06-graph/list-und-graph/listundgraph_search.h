#ifndef LISTUNDGRAPH_SEARCH_H_INCLUDED
#define LISTUNDGRAPH_SEARCH_H_INCLUDED

#include "listundgraph.h"

#define NOT_VISITED -1

int is_visited(int v)
{
  return v != NOT_VISITED;
}

void init_visited(int *visited, int size)
{
  for (int i = 0; i < size; i++)
  {
    visited[i] = NOT_VISITED;
  }
}

int *create_visited(int size)
{
  int *visited = (int *)malloc(size * sizeof(int));
  init_visited(visited, size);
  return visited;
}

static int __ListUndGraph_dfs_r(ListUndGraph *g, Vertex src, int *visited, int counter)
{
  int new_src = -1;
  visited[src] = counter++;
  Node *node = g->arr[src];

  for (; node != NULL; node = node->next)
  {
    new_src = node->vertex;
    if (visited[new_src] == NOT_VISITED)
      counter = __ListUndGraph_dfs_r(g, new_src, visited, counter);
  }

  return counter;
}

void ListUndGraph_dfs_r(ListUndGraph *g, Vertex src, int *visited)
{
  // counter na vdd seria uma variável de instância em um objeto DFSSearch
  int counter = 0;
  __ListUndGraph_dfs_r(g, src, visited, counter);
}

int ListUndGraph_count_connected_components(ListUndGraph *g)
{
  int v, connected_components_count = 0;
  int *visited = create_visited(g->vertices);

  for (v = 0; v < g->vertices; v++)
  {
    if (visited[v] == NOT_VISITED)
    {
      ListUndGraph_dfs_r(g, v, visited);
      connected_components_count++;
    }
  }

  free(visited);
  return connected_components_count;
}

#endif // LISTUNDGRAPH_SEARCH_H_INCLUDED