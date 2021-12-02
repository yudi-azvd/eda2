#ifndef LISTUNDGRAPH_CONNECTEDCOMPONENT_H_INCLUDED
#define LISTUNDGRAPH_CONNECTEDCOMPONENT_H_INCLUDED

#include <stdlib.h>

#include "listundgraph_search.h"

typedef struct ConnectedComponent
{
  int smallest_vertex, size;
  Vertex *vertices;
} ConnectedComponent;

int cmp_cc_size(const void *cc1, const void *cc2)
{
  return ((*(ConnectedComponent *)cc1).size - (*(ConnectedComponent *)cc2).size);
}

ConnectedComponent ConnectedComponent_create(int vertices)
{
  ConnectedComponent cc; // = (ConnectedComponent *)calloc(1, sizeof(ConnectedComponent));
  cc.size = 0;
  cc.smallest_vertex = INT_MAX;
  cc.vertices = (Vertex *)calloc(vertices, sizeof(Vertex));
  return cc;
}

void ConnectedComponent_destroy(ConnectedComponent *cc)
{
  free(cc->vertices);
}

void ConnectedComponent_destroy_array(ConnectedComponent *cc, int size)
{
  for (size_t i = 0; i < size; i++)
  {
    ConnectedComponent_destroy(&cc[i]);
  }
  free(cc);
}

void ConnectedComponent_add(ConnectedComponent *cc, Vertex v)
{
  cc->vertices[cc->size++] = v;
  if (v < cc->smallest_vertex)
    cc->smallest_vertex = v;
}

int __ListUndGraph_cc_dfs_r(ListUndGraph *g, Vertex src, int *visited, int counter, ConnectedComponent *cc)
{
  int new_src = -1;
  visited[src] = counter++;
  ConnectedComponent_add(cc, src);
  Node *node = g->arr[src];

  for (; node != NULL; node = node->next)
  {
    new_src = node->vertex;
    if (visited[new_src] == NOT_VISITED)
      counter = __ListUndGraph_cc_dfs_r(g, new_src, visited, counter, cc);
  }

  return counter;
}

void ListUndGraph_cc_dfs_r(ListUndGraph *g, Vertex src, int *visited, ConnectedComponent *cc)
{
  // counter na vdd seria uma variável de instância em um objeto DFSSearch
  int counter = 0;
  __ListUndGraph_cc_dfs_r(g, src, visited, counter, cc);
}

ConnectedComponent *ListUndGraph_connected_components(ListUndGraph *g, int *cc_size)
{
  int v, cc_index = 0;
  int *visited = create_visited(g->vertices);

  ConnectedComponent *cc =
      (ConnectedComponent *)calloc(g->vertices, sizeof(ConnectedComponent));

  for (v = 0; v < g->vertices; v++)
  {
    if (visited[v] == NOT_VISITED)
    {
      cc[cc_index] = ConnectedComponent_create(g->vertices);
      ListUndGraph_cc_dfs_r(g, v, visited, &cc[cc_index]);
      cc_index++;
    }
  }

  *cc_size = cc_index;
  free(visited);
  return cc;
}

#endif // LISTUNDGRAPH_CONNECTEDCOMPONENT_H_INCLUDED