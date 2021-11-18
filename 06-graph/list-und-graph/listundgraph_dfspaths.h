#ifndef LISTUNDGRAPH_DFSPATHS_H_INCLUDED
#define LISTUNDGRAPH_DFSPATHS_H_INCLUDED

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

typedef struct DFSPaths
{
  int max_vertices;
  int *visited; //
  int *edge_to;
  Vertex src;
} DFSPaths;

void dfs(ListUndGraph *g, int v, int counter, int *visited, int *edge_to)
{
  Node *node = g->arr[v];
  visited[v] = counter++;

  while (node != NULL)
  {
    if (visited[node->vertex] == NOT_VISITED)
    {
      edge_to[node->vertex] = v;
      dfs(g, node->vertex, counter, visited, edge_to);
    }
    node = node->next;
  }
}

DFSPaths *DFSPaths_create(ListUndGraph *g, Vertex src)
{
  DFSPaths *p = (DFSPaths *)calloc(1, sizeof(DFSPaths));
  p->visited = create_visited(g->vertices);
  p->edge_to = (int *)calloc(g->vertices, sizeof(int));
  p->src = src;
  p->max_vertices = g->vertices;

  int counter = 0;
  dfs(g, src, counter, p->visited, p->edge_to);
  return p;
}

void DFSPaths_destroy(DFSPaths *p)
{
  free(p->visited);
  free(p->edge_to);
  free(p);
}

uint8_t DFSPaths_has_path_to(DFSPaths *p, Vertex v)
{
  return is_visited(p->visited[v]);
}

// Assume que o caminho não vai ter mais vértices que o número
// de vértices do grafo original.
// O caminho inclui os nós de origem e destino [src, ..., dst]
Vertex *DFSPaths_path_to(DFSPaths *p, Vertex v, int *path_size)
{
  if (!DFSPaths_has_path_to(p, v)) {
    *path_size = -1;
    return NULL;
  }

  Vertex *path_inverted = (Vertex *)calloc(p->max_vertices, sizeof(Vertex));
  Vertex src = p->src;
  int path_index = 0, edge_index = v;

  while (edge_index != src) {
    path_inverted[path_index] = edge_index;
    edge_index = p->edge_to[edge_index];
    path_index++;
  }
  path_inverted[path_index++] = src;
  *path_size = path_index;

  // Copia path_buffer invertido em path.
  Vertex *path = (Vertex *)calloc(*path_size, sizeof(Vertex));
  for (path_index = 0; path_index < *path_size; path_index++)
  {
    path[path_index] = path_inverted[*path_size - path_index - 1];
  }

  free(path_inverted);
  return path;
}

#endif // LISTUNDGRAPH_DFSPATHS_H_INCLUDED