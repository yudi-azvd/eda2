#ifndef MATUNDGRAPH_SEARCH_H_INCLUDED
#define MATUNDGRAPH_SEARCH_H_INCLUDED

#include "matundgraph.h"

#define NOT_VISITED -1

void __init_visited(int *visited, int size)
{
  for (size_t i = 0; i < size; i++)
  {
    visited[i] = NOT_VISITED;
  }
}

int __MatUndGraph_dfs_r(MatUndGraph *g, Vertex src, int *visited, int counter)
{
  int i, new_src;
  visited[src] = counter++;

  for (i = 0; i < g->vertices; i++)
  {
    if (g->matrix[src][new_src] != 0)
      if (visited[new_src] == NOT_VISITED)
        counter = __MatUndGraph_dfs_r(g, new_src, visited, counter);
  }

  return counter;
}

int *MatUndGraph_dfs_r(MatUndGraph *g, Vertex src)
{
  int *visited = (int *)malloc(g->vertices * sizeof(int));
  __init_visited(visited, g->vertices);

  int counter = 0;
  __MatUndGraph_dfs_r(g, src, visited, counter);

  return visited;
}

#endif // MATUNDGRAPH_SEARCH_H_INCLUDED