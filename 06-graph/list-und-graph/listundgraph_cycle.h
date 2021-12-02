#ifndef LISTUNDGRAPH_CC_H_INCLUDED
#define LISTUNDGRAPH_CC_H_INCLUDED

#include "listundgraph.h"

#define NOT_VISITED -1

int is_visited(int v)
{
  return v != NOT_VISITED;
}

void init_int_arr(int *visited, int size)
{
  for (int i = 0; i < size; i++)
  {
    visited[i] = NOT_VISITED;
  }
}

int *create_int_arr(int size)
{
  int *visited = (int *)malloc(size * sizeof(int));
  init_int_arr(visited, size);
  return visited;
}

void __cy_dfs(ListUndGraph *g, int v, int u, int *visited, uint8_t *has_cycle)
{
  Node *node = g->arr[v];
  visited[v] = 1;

  while (node != NULL)
  {
    if (visited[node->vertex] == NOT_VISITED)
      __cy_dfs(g, node->vertex, v, visited, has_cycle);
    else if (node->vertex != u)
      *has_cycle = 1;

    node = node->next;
  }
}

typedef struct Cycle
{
  uint8_t has_cycle;
  int *visited;
} Cycle;

Cycle *Cycle_create(ListUndGraph *g)
{
  Cycle *cy = (Cycle *)calloc(1, sizeof(Cycle));
  cy->visited = create_int_arr(g->vertices);

  for (size_t v = 0; v < g->vertices; v++)
  {
    if (cy->visited[v] == NOT_VISITED)
      __cy_dfs(g, v, v, cy->visited, &cy->has_cycle);
  }

  return cy;
}

void Cycle_destroy(Cycle *cy)
{
  free(cy->visited);
  free(cy);
}

uint8_t Cycle_has(Cycle *cy)
{
  return cy->has_cycle;
}

#endif // LISTUNDGRAPH_CC_H_INCLUDED