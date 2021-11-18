#ifndef LISTUNDGRAPH_BFSPATHS_H_INCLUDED
#define LISTUNDGRAPH_BFSPATHS_H_INCLUDED

#include "listundgraph.h"
#include "../queue.h"

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

int *create_int_arr(int size)
{
  int *visited = (int *)malloc(size * sizeof(int));
  init_visited(visited, size);
  return visited;
}

typedef struct BFSPaths
{
  int max_vertices;
  int *visited; //
  int *edge_to;
  Vertex src;
} BFSPaths;

void bfs(ListUndGraph *g, int src, int counter, int *visited, int *edge_to)
{
  Vertex v, w;
  Queue *q = Queue_create();
  Node *node;
  visited[src] = counter++;

  Queue_enq(q, src);
  while (!Queue_empty(q))
  {
    v = Queue_deq(q);
    for (node = g->arr[v]; node != NULL; node = node->next)
    {
      w = node->vertex;
      if (visited[w] == NOT_VISITED)
      {
        edge_to[w] = v;
        visited[w] = counter++;
        Queue_enq(q, w);
      }
    }
  }

  Queue_destroy(q);
}

BFSPaths *BFSPaths_create(ListUndGraph *g, Vertex src)
{
  BFSPaths *p = (BFSPaths *)calloc(1, sizeof(BFSPaths));
  p->visited = create_int_arr(g->vertices);
  p->edge_to = create_int_arr(g->vertices);
  p->max_vertices = g->vertices;
  p->src = src;

  bfs(g, src, 0, p->visited, p->edge_to);
  return p;
}

void BFSPaths_destroy(BFSPaths *p)
{
  free(p->visited);
  free(p->edge_to);
  free(p);
}

uint8_t BFSPaths_has_path_to(BFSPaths *p, Vertex v)
{
  return is_visited(p->visited[v]);
}

// Assume que o caminho não vai ter mais vértices que o número
// de vértices do grafo original.
// O caminho inclui os nós de origem e destino [src, ..., dst]
Vertex *BFSPaths_path_to(BFSPaths *p, Vertex v, int *path_size)
{
  if (!BFSPaths_has_path_to(p, v))
  {
    *path_size = -1;
    return NULL;
  }

  Vertex *path_buffer = (Vertex *)calloc(p->max_vertices, sizeof(Vertex));
  Vertex src = p->src;
  int path_index = 0, edge_index = v;

  while (edge_index != src)
  {
    path_buffer[path_index] = edge_index;
    edge_index = p->edge_to[edge_index];
    path_index++;
  }

  path_buffer[path_index++] = src;
  *path_size = path_index;

  // Copia path_buffer invertido em path.
  Vertex *path = (Vertex *)calloc(*path_size, sizeof(Vertex));
  for (path_index = 0; path_index < *path_size; path_index++)
  {
    path[path_index] = path_buffer[*path_size - path_index - 1];
  }

  free(path_buffer);
  return path;
}

#endif // LISTUNDGRAPH_BFSPATHS_H_INCLUDED