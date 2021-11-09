#ifndef MATUNDGRAPH_H_INCLUDED
#define MATUNDGRAPH_H_INCLUDED

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

void __MatUndGraph_matrix_reset_main_diagonal(MatUndGraph *g)
{
  int j, i;
  for (i = 0; i < g->vertices; ++i)
  {
    for (j = i; j < i + 1; ++j)
    {
      g->matrix[i][j] = 0;
    }
  }
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

// cria um grafo com todos os vértices conectados entre si, sem contar
// com a conexão de um vértice a ele mesmo (ex: a-a)
MatUndGraph *MatUndGraph_create_complete(int max_vertices)
{
  MatUndGraph *g = (MatUndGraph *)calloc(1, sizeof(MatUndGraph));
  g->vertices = max_vertices;
  g->edges = max_vertices * (max_vertices - 1) / 2;
  g->matrix = __MatUndGraph_matrix_create(max_vertices, __CONNECTED);
  __MatUndGraph_matrix_reset_main_diagonal(g);
  return g;
}

void MatUndGraph_destroy(MatUndGraph *g)
{
  __MatUndGraph_matrix_destroy(g);
  free(g);
}

int MatUndGraph_edges_count(MatUndGraph *g)
{
  return g->edges;
}

int MatUndGraph_vertices_count(MatUndGraph *g)
{
  return g->vertices;
}

void MatUndGraph_insert_edge(MatUndGraph *g, Vertex a, Vertex b)
{
  if (g->matrix[a][b] == __UNCONNECTED)
    ++g->edges;

  g->matrix[a][b] = __CONNECTED;
  g->matrix[b][a] = __CONNECTED;
}

// void MatUndGraph_remove_edge(MatUndGraph* g, Edge e) {
void MatUndGraph_remove_edge(MatUndGraph *g, Vertex a, Vertex b)
{
  if (g->matrix[a][b] == __CONNECTED)
    --g->edges;

  g->matrix[a][b] = __UNCONNECTED;
  g->matrix[b][a] = __UNCONNECTED;
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

MatUndGraph *MatUndGraph_copy(MatUndGraph *g)
{
  MatUndGraph *copy = MatUndGraph_create(g->vertices);
  copy->edges = MatUndGraph_edges_count(g);
  copy->vertices = MatUndGraph_vertices_count(g);

  for (size_t i = 0; i < g->vertices; i++)
  {
    for (size_t j = i + 1; j < g->vertices; j++)
    {
      copy->matrix[i][j] = g->matrix[i][j];
    }
  }

  return copy;
}

uint8_t MatUndGraph_equal(MatUndGraph *a, MatUndGraph *b)
{
  if (a->vertices != b->vertices)
    return 0;
  if (a->edges != b->edges)
    return 0;

  for (size_t i = 0; i < a->vertices; i++)
  {
    for (size_t j = i + 1; j < a->vertices; j++)
    {
      if (a->matrix[i][j] != b->matrix[i][j])
        return 0;
    }
  }

  return 1;
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

#endif // MATUNDGRAPH_H_INCLUDED