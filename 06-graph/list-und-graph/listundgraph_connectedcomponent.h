#ifndef LISTUNDGRAPH_CONNECTEDCOMPONENT_H_INCLUDED
#define LISTUNDGRAPH_CONNECTEDCOMPONENT_H_INCLUDED

#include "listundgraph_search.h"

typedef struct ConnectedComponent
{
  int smallest_vertex, size;
  Vertex *vertices;
} ConnectedComponent;

ConnectedComponent *ConnectedComponent_create(int vertices)
{
  ConnectedComponent *cc = (ConnectedComponent *)calloc(1, sizeof(ConnectedComponent));
  cc->size = 0;
  cc->smallest_vertex = INT_MAX;
  cc->vertices = (Vertex *)calloc(vertices, sizeof(Vertex));
  return cc;
}

void ConnectedComponent_destroy(ConnectedComponent *cc)
{
  free(cc->vertices);
  free(cc);
}

void ConnectedComponent_destroy_array(ConnectedComponent **cc, int size)
{
  for (size_t i = 0; i < size; i++)
  {
    ConnectedComponent_destroy(cc[i]);
  }
  free(cc);
}


void ConnectedComponent_add(ConnectedComponent *cc, Vertex v)
{
  cc->vertices[cc->size++] = v;
  if (v < cc->smallest_vertex)
    cc->smallest_vertex = v;
}

ConnectedComponent **ListUndGraph_connected_components(ListUndGraph *g, int *cc_size)
{
  int v, cc_index = 0;
  int *visited = create_visited(g->vertices);
  
  ConnectedComponent **components =
      (ConnectedComponent **)calloc(g->vertices, sizeof(ConnectedComponent *));

  for (v = 0; v < g->vertices; v++)
  {
    if (visited[v] == NOT_VISITED)
    {
      components[cc_index] = ConnectedComponent_create(g->vertices);
      ConnectedComponent_add(components[cc_index], v);
      ListUndGraph_dfs_r(g, v, visited);
      cc_index++;
    }
    else
    {
      ConnectedComponent_add(components[cc_index-1], v);
    }
  }

  *cc_size = cc_index;
  free(visited);
  return components;
}

#endif // LISTUNDGRAPH_CONNECTEDCOMPONENT_H_INCLUDED