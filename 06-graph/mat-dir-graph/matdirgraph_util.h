#ifndef MATDIRGRAPH_UTIL_H_INCLUDED
#define MATDIRGRAPH_UTIL_H_INCLUDED

#include "matdirgraph.h"

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

int __MatDirGraph_dfs_r(MatDirGraph *g, Vertex src, int *visited, int counter)
{
  int new_src = 0;
  visited[src] = counter++;

  for (; new_src < g->vertices; new_src++)
  {
    if (g->matrix[src][new_src] != 0)
      if (visited[new_src] == NOT_VISITED)
        counter = __MatDirGraph_dfs_r(g, new_src, visited, counter);
  }

  return counter;
}

void MatDirGraph_dfs_r(MatDirGraph *g, Vertex src, int *visited)
{
  int counter = 0;
  __MatDirGraph_dfs_r(g, src, visited, counter);
}

int MatDirGraph_count_connected_components(MatDirGraph *g)
{
  int v, connected_components_count = 0;
  int *visited = create_visited(g->vertices);

  for (v = 0; v < g->vertices; v++)
  {
    if (visited[v] == NOT_VISITED)
    {
      MatDirGraph_dfs_r(g, v, visited);
      connected_components_count++;
    }
  }

  free(visited);
  return connected_components_count;
}

////////////////////////////////////////////////////////////
////// FECHO TRANSITIVO
////////////////////////////////////////////////////////////

typedef struct TC
{
  uint8_t **tc;
  int vertices;
} TC;

// Retorna fecho transitivo de um grafo.
TC *TC_create_from(MatDirGraph *g)
{
  int s = 0, t = 0, i = 0;
  TC *tc = (TC *)malloc(1 * sizeof(TC));
  tc->tc = (uint8_t **)calloc(g->vertices, sizeof(uint8_t*));
  tc->vertices = g->vertices;
  int vertices = g->vertices;

  for (; s < vertices; s++)
  {
    tc->tc[s] = (uint8_t *)calloc(vertices, sizeof(uint8_t));
  }

  // a matriz do grafo é a base do fecho transitivo;
  for (s = 0; s < vertices; s++)
  {
    for (t = 0; t < vertices; t++)
    {
      tc->tc[s][t] = g->matrix[s][t];
    }
  }

  // todo vértice é conectado com ele mesmo
  for (s = 0; s < vertices; s++)
    tc->tc[s][s] = __CONNECTED;

  for (i = 0; i < vertices; ++i)
    for (s = 0; s < vertices; ++s)
      if (tc->tc[s][i] == __CONNECTED)
        for (t = 0; t < vertices; ++t)
          if (tc->tc[i][t] == __CONNECTED)
            tc->tc[s][t] = __CONNECTED;
  return tc;
}

void TC_destroy(TC* tc)
{
  int i = 0;
  for (; i < tc->vertices; i++)
  {
    free(tc->tc[i]);
  }

  free(tc->tc);
  free(tc);
}

uint8_t TC_reaches(TC* tc, Vertex s, Vertex t)
{
  return tc->tc[s][t] == __CONNECTED;
}

void TC_show(TC* tc)
{
  int i, j;
  printf("TC: %d vertices\n", tc->vertices);
  for (i = 0; i < tc->vertices; i++)
  {
    printf("%2d:", i);
    for (j = 0; j < tc->vertices; j++)
    {
      if (tc->tc[i][j] == 1)
        printf(" %2d", j);
    }
    printf("\n");
  }
}

#endif // MATDIRGRAPH_UTIL_H_INCLUDED