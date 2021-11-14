#include <stdio.h>
#include <stdlib.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-grafos
// https://br.spoj.com/problems/IREVIR.pdf

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
  int i;
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
  tc->tc = (uint8_t **)calloc(g->vertices, sizeof(uint8_t *));
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
  // for (s = 0; s < vertices; s++)
  //   tc->tc[s][s] = __CONNECTED;

  for (i = 0; i < vertices; ++i)
    for (s = 0; s < vertices; ++s)
      if (tc->tc[s][i] == __CONNECTED)
        for (t = 0; t < vertices; ++t)
          if (tc->tc[i][t] == __CONNECTED)
            tc->tc[s][t] = __CONNECTED;
  return tc;
}

void TC_destroy(TC *tc)
{
  int i = 0;
  for (; i < tc->vertices; i++)
  {
    free(tc->tc[i]);
  }

  free(tc->tc);
  free(tc);
}

uint8_t TC_reaches(TC *tc, Vertex s, Vertex t)
{
  return tc->tc[s][t] == __CONNECTED;
}

void TC_show(TC *tc)
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
    fflush(stdout);
  }
}

int graph_is_connected(MatDirGraph *g)
{ 
  int i, j;
  TC *tc = TC_create_from(g);
  // MatDirGraph_show(g);
  // TC_show(tc);
  for (i = 0; i < g->vertices; i++)
  {
    for (j = 0; j < g->vertices; j++)
    {
      if (!TC_reaches(tc, i, j))
        return 0;
    }
  }

  TC_destroy(tc);
  return 1;
}

#define TWO_WAY 2

int main()
{
  int i, vertices = 0, lines = 0;
  int v, w, street_mode = 0;

  MatDirGraph *g;

  while (1)
  {
    scanf("%d %d", &vertices, &lines);

    if (vertices == 0 && lines == 0)
      break;

    g = MatDirGraph_create(vertices);

    for (i = 0; i < lines; i++)
    {
      scanf("%d %d %d", &v, &w, &street_mode);

      MatDirGraph_insert_edge(g, v - 1, w - 1);
      if (street_mode == TWO_WAY)
      {
        MatDirGraph_insert_edge(g, w - 1, v - 1);
      }
    }

    printf("%d\n", graph_is_connected(g));

    MatDirGraph_destroy(g);
  }

  return 0;
}
