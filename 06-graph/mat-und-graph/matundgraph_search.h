#ifndef MATUNDGRAPH_SEARCH_H_INCLUDED
#define MATUNDGRAPH_SEARCH_H_INCLUDED

#include "matundgraph.h"

#define NOT_VISITED -1

int is_visited(int v)
{
  return v != NOT_VISITED;
}

void init_visited(int *visited, int size)
{
  for (size_t i = 0; i < size; i++)
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

int __MatUndGraph_dfs_r(MatUndGraph *g, Vertex src, int *visited, int counter)
{
  int new_src = 0;
  visited[src] = counter++;

  for (; new_src < g->vertices; new_src++)
  {
    if (g->matrix[src][new_src] != 0)
      if (visited[new_src] == NOT_VISITED)
        counter = __MatUndGraph_dfs_r(g, new_src, visited, counter);
  }

  return counter;
}

void MatUndGraph_dfs_r(MatUndGraph *g, Vertex src, int *visited)
{
  int counter = 0;
  __MatUndGraph_dfs_r(g, src, visited, counter);
}

#endif // MATUNDGRAPH_SEARCH_H_INCLUDED