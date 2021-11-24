#ifndef LISTUNDGRAPH_CC_H_INCLUDED
#define LISTUNDGRAPH_CC_H_INCLUDED

#include "listundgraph.h"

// Implementação Sedgewick-Wayne de Connected Components

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

typedef struct CC
{
  int count;
  int *id;
  int *visited;
} CC;

void __cc_dfs(ListUndGraph *g, int v, int counter, int *visited, int *id)
{
  Node *node = g->arr[v];
  visited[v] = 1;
  id[v] = counter;

  while (node != NULL)
  {
    if (visited[node->vertex] == NOT_VISITED)
    {
      id[node->vertex] = v;
      __cc_dfs(g, node->vertex, counter, visited, id);
    }
    node = node->next;
  }
}

CC *CC_of(ListUndGraph *g)
{
  CC *cc = (CC *)calloc(1, sizeof(CC));
  cc->id = create_int_arr(g->vertices);
  cc->visited = create_int_arr(g->vertices);

  int cc_counter = 0;
  for (size_t v = 0; v < g->vertices; v++)
  {
    if (cc->visited[v] == NOT_VISITED)
    {
      __cc_dfs(g, v, cc_counter, cc->visited, cc->id);
      cc_counter++;
    }
  }

  cc->count = cc_counter;
  return cc;
}

void CC_destroy(CC *cc)
{
  free(cc->id);
  free(cc->visited);
  free(cc);
}

int CC_id(CC *cc, Vertex v)
{
  return cc->id[v];
}

int CC_count(CC *cc)
{
  return cc->count;
}

int CC_connected(CC *cc, Vertex v, Vertex w)
{
  return cc->id[v] == cc->id[w];
}

#endif // LISTUNDGRAPH_CC_H_INCLUDED