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
  int *visited;
  int *edge_to;
  int *dist_to;
  Vertex src;
} BFSPaths;

void bfs(ListUndGraph *g, int src, int *visited, int *edge_to, int *dist_to)
{
  Vertex v, w;
  Queue *q = Queue_create();
  Node *node;
  int visits_counter = 0, dist_to_v = 0;
  dist_to[src] = 0;
  visited[src] = visits_counter++;

  Queue_enq(q, src);
  while (!Queue_empty(q))
  {
    v = Queue_deq(q);
    if (visited[v] != NOT_VISITED)
      dist_to_v = dist_to[v];
    for (node = g->arr[v]; node != NULL; node = node->next)
    {
      w = node->vertex;
      if (visited[w] == NOT_VISITED)
      {
        edge_to[w] = v;
        visited[w] = visits_counter++;
        dist_to[w] = dist_to_v + 1;
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
  p->dist_to = create_int_arr(g->vertices);
  p->max_vertices = g->vertices;
  p->src = src;

  bfs(g, src, p->visited, p->edge_to, p->dist_to);
  return p;
}

void BFSPaths_destroy(BFSPaths *p)
{
  free(p->visited);
  free(p->edge_to);
  free(p->dist_to);
  free(p);
}

uint8_t BFSPaths_has_path_to(BFSPaths *p, Vertex v)
{
  return is_visited(p->visited[v]);
}

// Assume que o caminho não vai ter mais vértices que o número
// de vértices do grafo original.
// O caminho inclui os nós de origem e destino [src, ..., dst]
Vertex *BFSPaths_path_to(BFSPaths *p, Vertex dst, int *path_size)
{
  if (!BFSPaths_has_path_to(p, dst))
  {
    *path_size = -1;
    return NULL;
  }

  Vertex *path_buffer = create_int_arr(p->max_vertices);
  Vertex src = p->src;
  int path_index = 0, edge_index = dst;

  while (edge_index != src)
  {
    path_buffer[path_index] = edge_index;
    edge_index = p->edge_to[edge_index];
    path_index++;
  }

  path_buffer[path_index++] = src;
  *path_size = path_index;

  // Copia path_buffer invertido em path.
  Vertex *path = create_int_arr(*path_size);
  for (path_index = 0; path_index < *path_size; path_index++)
  {
    path[path_index] = path_buffer[*path_size - path_index - 1];
  }

  free(path_buffer);
  return path;
}

int BFSPaths_dist_to(BFSPaths *p, Vertex dst)
{
  return p->dist_to[dst];
}

#endif // LISTUNDGRAPH_BFSPATHS_H_INCLUDED