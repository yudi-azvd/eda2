#ifndef MATDIRGRAPH_H_INCLUDED
#define MATDIRGRAPH_H_INCLUDED

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

Edge __MatDirGraph_edge_create(int a, int b)
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
typedef struct MatDirGraph
{
  int vertices;     // número de vértices
  int edges;        // número de arestas
  uint8_t **matrix; // matrix de booleanos

  // 4 (bytes)
  // 4 (bytes)
  // 8 (bytes)
} MatDirGraph;

// Não é amigável para a cache da CPU
uint8_t **__MatDirGraph_matrix_create(int max_vertices, int initial_value)
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

void __MatDirGraph_matrix_reset_main_diagonal(MatDirGraph *g)
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

void __MatDirGraph_matrix_destroy(MatDirGraph *g)
{
  int i;
  for (i = 0; i < g->vertices; ++i)
  {
    free(g->matrix[i]);
  }
  free(g->matrix);
}

MatDirGraph *MatDirGraph_create(int max_vertices)
{
  MatDirGraph *g = (MatDirGraph *)calloc(1, sizeof(MatDirGraph));
  g->vertices = max_vertices;
  g->edges = 0;
  g->matrix = __MatDirGraph_matrix_create(max_vertices, __UNCONNECTED);
  return g;
}

// cria um grafo com todos os vértices conectados entre si, sem contar
// com a conexão de um vértice a ele mesmo (ex: a-a)
MatDirGraph *MatDirGraph_create_complete(int max_vertices)
{
  MatDirGraph *g = (MatDirGraph *)calloc(1, sizeof(MatDirGraph));
  g->vertices = max_vertices;
  g->edges = max_vertices * (max_vertices - 1) / 2;
  g->matrix = __MatDirGraph_matrix_create(max_vertices, __CONNECTED);
  __MatDirGraph_matrix_reset_main_diagonal(g);
  return g;
}

void MatDirGraph_destroy(MatDirGraph *g)
{
  __MatDirGraph_matrix_destroy(g);
  free(g);
}

int MatDirGraph_edges_count(MatDirGraph *g)
{
  return g->edges;
}

int MatDirGraph_vertices_count(MatDirGraph *g)
{
  return g->vertices;
}

void MatDirGraph_insert_edge(MatDirGraph *g, Vertex a, Vertex b)
{
  if (g->matrix[a][b] == __UNCONNECTED)
    ++g->edges;

  g->matrix[a][b] = __CONNECTED;
}

// void MatDirGraph_remove_edge(MatDirGraph* g, Edge e) {
void MatDirGraph_remove_edge(MatDirGraph *g, Vertex a, Vertex b)
{
  if (g->matrix[a][b] == __CONNECTED)
    --g->edges;

  g->matrix[a][b] = __UNCONNECTED;
}

Edge *MatDirGraph_edges(MatDirGraph *g, int *edges_count)
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
        edges[e_counter++] = __MatDirGraph_edge_create(a, b);
      }
    }
  }

  return edges;
}

MatDirGraph *MatDirGraph_copy(MatDirGraph *g)
{
  MatDirGraph *copy = MatDirGraph_create(g->vertices);
  copy->edges = MatDirGraph_edges_count(g);
  copy->vertices = MatDirGraph_vertices_count(g);

  for (size_t i = 0; i < g->vertices; i++)
  {
    for (size_t j = i + 1; j < g->vertices; j++)
    {
      copy->matrix[i][j] = g->matrix[i][j];
    }
  }

  return copy;
}

uint8_t MatDirGraph_equal(MatDirGraph *a, MatDirGraph *b)
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

uint8_t MatDirGraph_has_edge(MatDirGraph *g, Vertex a, Vertex b)
{
  return g->matrix[a][b] == __CONNECTED;
}

Vertex *MatDirGraph_adjacent_to(MatDirGraph *g, const Vertex v, int *size)
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

void MatDirGraph_show(MatDirGraph *g)
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

#endif // MATDIRGRAPH_H_INCLUDED