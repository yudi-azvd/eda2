#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-grafos
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-grafos/euvouestarla.html
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-grafos/euvouestarla.pdf

typedef int Vertex;

#define __CONNECTED 1
#define __UNCONNECTED 0
#define MAX_VERTICES 2000

// Em uma máquina de 64 bits
typedef struct MatUndGraph
{
  int vertices;                               // número de vértices
  int edges;                                  // número de arestas
  uint8_t matrix[MAX_VERTICES][MAX_VERTICES]; // matrix de booleanos
} MatUndGraph;

void __MatUndGraph_matrix_destroy(MatUndGraph *g)
{
  free(g->matrix);
}

MatUndGraph *MatUndGraph_create(int max_vertices)
{
  MatUndGraph *g = (MatUndGraph *)calloc(1, sizeof(MatUndGraph));
  g->vertices = max_vertices;
  g->edges = 0;
  return g;
}

void MatUndGraph_destroy(MatUndGraph *g)
{
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

#define WAS_NOT_HERE 0
#define WAS_HERE 1

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
    julius_was_here[vertex] = WAS_HERE;
  }
}

int is_neighbour_to_where_julius_has_been(uint8_t julius_was_here[], MatUndGraph *g, Vertex v)
{
  int neighbour_to_v = 0;
  for (; neighbour_to_v < g->vertices; neighbour_to_v++)
  {
    if (g->matrix[v][neighbour_to_v] == __CONNECTED)
      if (julius_was_here[neighbour_to_v] == WAS_HERE)
        return 1;
  }

  return 0;
}

void predict_where_julius_will_be(uint8_t julius_was_here[], int J, MatUndGraph *g)
{
  int i = 0, vertex, will_be_here = 0, is_neighbour = 0;
  for (; i < J; i++)
  {
    scanf("%d", &vertex);

    will_be_here = julius_was_here[vertex] ||
                   is_neighbour_to_where_julius_has_been(julius_was_here, g, vertex);

    printf("%s vou estar la\n", will_be_here ? "Eu" : "Nao");
  }
}

int main()
{
  int N, M, J;
  uint8_t julius_was_here[MAX_VERTICES] =
      {[0 ... MAX_VERTICES - 1] = WAS_NOT_HERE};

  scanf("%d %d %d", &N, &M, &J);

  MatUndGraph g;
  g.vertices = N;

  fill_graph(&g, N);
  read_places_julius_has_been(julius_was_here, M);
  predict_where_julius_will_be(julius_was_here, J, &g);

  // MatUndGraph_destroy(g);
  return 0;
}