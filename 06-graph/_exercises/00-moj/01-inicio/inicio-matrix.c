// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-grafos
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-grafos/grafo-nucleos-cidades.html
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-grafos/grafo-nucleos-cidades.pdf

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Adjacent Matrix Undirected Graph

// Aula do prof Bruno Ribas
// https://youtu.be/-CWbqWbNBTQ?t=5888

// IME USP
// https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/graphdatastructs.html

typedef int Vertex;

typedef struct Edge
{
  Vertex a, b;
} Edge;

Edge __MatUndGraph_edge_create(int a, int b)
{
  Edge e = {a, b};
  return e;
}

uint8_t UndEdge_equal(Edge e1, Edge e2)
{
  return (e1.a == e2.a && e1.b == e2.b) || (e1.a == e2.b && e1.b == e2.b);
}

#define __CONNECTED 1
#define __UNCONNECTED 0

// Em uma máquina de 64 bits
typedef struct MatUndGraph
{
  int vertices;     // número de vértices
  int edges;        // número de arestas
  uint8_t **matrix; // matrix de booleanos
  // 4 (bytes)
  // 4 (bytes)
  // 8 (bytes)
} MatUndGraph;

// Não é amigável para a cache da CPU
uint8_t **__MatUndGraph_matrix_create(int max_vertices, int initial_value)
{
  int i;
  uint8_t **matrix = (uint8_t **)malloc(max_vertices * sizeof(uint8_t *));

  for (i = 0; i < max_vertices; ++i)
  {
    matrix[i] = (uint8_t *)malloc(max_vertices * sizeof(uint8_t));
  }

  int j;
  for (i = 0; i < max_vertices; ++i)
  {
    for (j = 0; j < max_vertices; ++j)
    {
      (matrix)[i][j] = initial_value;
    }
  }

  return matrix;
}


void __MatUndGraph_matrix_destroy(MatUndGraph *g)
{
  int i;
  for (i = 0; i < g->vertices; ++i)
  {
    free(g->matrix[i]);
  }
  free(g->matrix);
}

MatUndGraph *MatUndGraph_create(int max_vertices)
{
  MatUndGraph *g = (MatUndGraph *)calloc(1, sizeof(MatUndGraph));
  g->vertices = max_vertices;
  g->edges = 0;
  g->matrix = __MatUndGraph_matrix_create(max_vertices, __UNCONNECTED);
  return g;
}


void MatUndGraph_destroy(MatUndGraph *g)
{
  __MatUndGraph_matrix_destroy(g);
  free(g);
}


void MatUndGraph_insert_edge(MatUndGraph *g, Vertex a, Vertex b)
{
  if (g->matrix[a][b] == __UNCONNECTED)
    ++g->edges;

  g->matrix[a][b] = __CONNECTED;
  g->matrix[b][a] = __CONNECTED;
}


Edge *MatUndGraph_edges(MatUndGraph *g, int *edges_count)
{
  int a, b, e_counter = 0;
  *edges_count = g->edges; // tá certo isso?
  Edge *edges = (Edge *)calloc(*edges_count, sizeof(Edge));

  for (a = 0; a < g->edges; a++)
  {
    for (b = a + 1; b < g->edges; b++)
    {
      if (g->matrix[a][b] == 1)
      {
        edges[e_counter++] = __MatUndGraph_edge_create(a, b);
      }
    }
  }

  return edges;
}



uint8_t MatUndGraph_has_edge(MatUndGraph *g, Vertex a, Vertex b)
{
  // não precisa checar b-a pq é um grafo não direcionado.
  return g->matrix[a][b] == __CONNECTED;
}

Vertex *MatUndGraph_adjacent_to(MatUndGraph *g, const Vertex v, int *size)
{
  int i, j;
  *size = 0;
  Vertex *vertices = (Vertex *)calloc(g->vertices - 1, sizeof(Vertex));
  for (i = 0; i < g->vertices; i++)
  {
    if (g->matrix[v][i] == __CONNECTED)
      vertices[(*size)++] = i;
  }
  return vertices;
}

void MatUndGraph_show(MatUndGraph *g)
{
  int i, j;
  printf("%d vertices, %d edges\n", g->vertices, g->edges);
  for (i = 0; i < g->vertices; i++)
  {
    printf("%2d:", i);
    for (j = 0; j < g->vertices; j++)
    {
      if (g->matrix[i][j] == 1)
        printf(" %2d", j);
    }
    printf("\n");
  }
}


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

int MatUndGraph_count_connected_components(MatUndGraph *g)
{
  int v, connected_components_count = 0;
  int *visited = create_visited(g->vertices);

  for (v = 0; v < g->vertices; v++)
  {
    if (visited[v] == NOT_VISITED)
    {
      MatUndGraph_dfs_r(g, v, visited);
      connected_components_count++;
    }
  }

  free(visited);
  return connected_components_count;
}


int main(int argc, char const *argv[])
{
  int cities, city_a, city_b;
  scanf("%d", &cities);

  MatUndGraph* g = MatUndGraph_create(cities);

  while (scanf("%d %d", &city_a, &city_b) != EOF)
  {
    MatUndGraph_insert_edge(g, city_a, city_b);
  }

  int connected_cities = MatUndGraph_count_connected_components(g);

  printf("%d\n", connected_cities);  

  MatUndGraph_destroy(g);
  return 0;
}
