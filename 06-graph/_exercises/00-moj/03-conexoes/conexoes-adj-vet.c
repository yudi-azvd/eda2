#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-grafos
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-grafos/grafo-nlogonia-conexoes.html
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-grafos/grafo-nlogonia-conexoes.pdf

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
  uint8_t *matrix; // matrix de booleanos

  // 4 (bytes)
  // 4 (bytes)
  // 8 (bytes)
} MatDirGraph;

uint8_t *__MatDirGraph_matrix_create(int max_vertices, int initial_value)
{
  int i;
  uint8_t *matrix = (uint8_t *)malloc(max_vertices * max_vertices * sizeof(uint8_t));

  int j;
  for (i = 0; i < max_vertices; ++i)
  {
    for (j = 0; j < max_vertices; ++j)
    {
      matrix[i * max_vertices + j] = initial_value;
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
      g->matrix[i * g->vertices + j] = 0;
    }
  }
}

MatDirGraph *MatDirGraph_create(int max_vertices)
{
  MatDirGraph *g = (MatDirGraph *)calloc(1, sizeof(MatDirGraph));
  g->vertices = max_vertices;
  g->edges = 0;
  g->matrix = __MatDirGraph_matrix_create(max_vertices, __UNCONNECTED);
  return g;
}

void MatDirGraph_destroy(MatDirGraph *g)
{
  free(g->matrix);
  free(g);
}

void MatDirGraph_insert_edge(MatDirGraph *g, Vertex a, Vertex b)
{
  if (g->matrix[a * g->vertices + b] == __UNCONNECTED)
    ++g->edges;

  g->matrix[a * g->vertices + b] = __CONNECTED;
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
      if (g->matrix[i * g->vertices + j] == 1)
        printf(" %2d", j);
    }
    printf("\n");
  }
}

typedef struct TC
{
  uint8_t *tc;
  int vertices;
} TC;

// Retorna fecho transitivo de um grafo.
TC *TC_of(MatDirGraph *g)
{
  int s = 0, t = 0, i = 0;
  TC *tc = (TC *)malloc(1 * sizeof(TC));
  tc->tc = (uint8_t *)calloc(g->vertices, sizeof(uint8_t));
  tc->vertices = g->vertices;

  // a matriz do grafo é a base do fecho transitivo;
  for (s = 0; s < g->vertices; s++)
  {
    for (t = 0; t < g->vertices; t++)
    {
      tc->tc[s * g->vertices + t] = g->matrix[s * g->vertices + t];
    }
  }

  // todo vértice é conectado com ele mesmo
  for (s = 0; s < g->vertices; s++)
    tc->tc[s * g->vertices + s] = __CONNECTED;

  for (i = 0; i < g->vertices; ++i)
    for (s = 0; s < g->vertices; ++s)
      if (tc->tc[s * g->vertices + i] == __CONNECTED)
        for (t = 0; t < g->vertices; ++t)
          if (tc->tc[i * g->vertices + t] == __CONNECTED)
            tc->tc[s * g->vertices + t] = __CONNECTED;
  return tc;
}

void TC_destroy(TC *tc)
{
  int i = 0;
  free(tc->tc);
  free(tc);
}

uint8_t TC_reaches(TC *tc, Vertex s, Vertex t)
{
  return tc->tc[s * tc->vertices + t] == __CONNECTED;
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
      if (tc->tc[i * tc->vertices + j] == 1)
        printf(" %2d", j);
    }
    printf("\n");
  }
}

#define ONE_WAY 1
#define TWO_WAY 2

// FIXME: otimizar matriz de adjacências: transformá-lo em um
// vetor de adjacencias. Usar regex pra substituir todo [i*g->vertices+j]
// vet[i*g.vertices+j]
int main()
{
  int vertices, v, w, street_mode = 0;
  scanf("%d", &vertices);

  MatDirGraph *g = MatDirGraph_create(vertices);

  while (1)
  {
    scanf("%d %d %d", &v, &w, &street_mode);

    if (v == 0 && w == 0 && street_mode == 0)
      break;

    if (street_mode == ONE_WAY)
    {
      MatDirGraph_insert_edge(g, v, w);
    }
    else
    {
      MatDirGraph_insert_edge(g, v, w);
      MatDirGraph_insert_edge(g, w, v);
    }
  }

  char messages[4][15] = {
      "Impossibru",
      "Apenas Volta",
      "Apenas Ida",
      "Ida e Volta",
  };

  // calcular fecho transitivo
  TC *tc = TC_of(g);
  int reaches_first_way, reaches_second_way, index;
  while (scanf("%d %d", &v, &w) != EOF)
  {
    // consultar fecho transitivo
    reaches_first_way = TC_reaches(tc, v, w);
    reaches_second_way = TC_reaches(tc, w, v);

    index = 2 * reaches_first_way + reaches_second_way;
    printf("%s\n", messages[index]);
  }

  MatDirGraph_destroy(g);
  TC_destroy(tc);
  return 0;
}