#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-grafos
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-grafos/euvouestarla.html
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-grafos/euvouestarla.pdf

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

void MatUndGraph_insert_edge(MatUndGraph *g, Vertex a, Vertex b)
{
  if (g->matrix[a][b] == __UNCONNECTED)
    ++g->edges;

  g->matrix[a][b] = __CONNECTED;
  g->matrix[b][a] = __CONNECTED;
}

uint8_t MatUndGraph_has_edge(MatUndGraph *g, Vertex a, Vertex b)
{
  // não precisa checar b-a pq é um grafo não direcionado.
  return g->matrix[a][b] == __CONNECTED;
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

#define MAX_VERTICES 2000
#define WAS_NOT_THERE 0
#define WAS_THERE 1

typedef struct JuliusPos
{
  Vertex v;
  uint8_t was_here;
} JuliusPos;

void fill_graph(MatUndGraph *g, int N)
{
  int i, j, neighbours_in_line, neighbour;

  for (i = 0; i < N; i++)
  {
    scanf("%d", &neighbours_in_line);

    for (j = 0; j < neighbours_in_line; j++)
    {
      scanf("%d", &neighbour);
      MatUndGraph_insert_edge(g, i, neighbour);
    }
  }
}

void read_places_julius_has_been(uint8_t julius_was_here[], int M)
{
  int i = 0, vertex;
  for (i = 0; i < M; i++)
  {
    scanf("%d", &vertex);
    julius_was_here[vertex] = WAS_THERE;
  }
}

int is_neighbour_to_where_julius_has_been(uint8_t julius_was_here[], MatUndGraph *g, Vertex v)
{
  int i = 0;
  for (; i < g->vertices; i++)
  {
    if (g->matrix[v][i] == __CONNECTED)
      if (julius_was_here[i] == WAS_THERE)
        return 1;
  }

  return 0;
}

void predict_where_julius_will_be(uint8_t julius_was_there[], int J, MatUndGraph *g)
{
  int i, vertex, will_be_there = 0, is_neighbour = 0;
  for (int i = 0; i < J; i++)
  {
    scanf("%d", &vertex);

    is_neighbour = is_neighbour_to_where_julius_has_been(julius_was_there, g, vertex);
    will_be_there = julius_was_there[vertex] || is_neighbour;

    printf("%s vou estar la\n", will_be_there ? "Eu" : "Nao");
  }
}

int main()
{
  int N, M, J;
  uint8_t julius_was_there[MAX_VERTICES] =
      {[0 ... MAX_VERTICES - 1] = WAS_NOT_THERE};

  scanf("%d %d %d", &N, &M, &J);

  MatUndGraph *g = MatUndGraph_create(N);

  fill_graph(g, N);
  read_places_julius_has_been(julius_was_there, M);
  predict_where_julius_will_be(julius_was_there, J, g);

  MatUndGraph_destroy(g);
  return 0;
}