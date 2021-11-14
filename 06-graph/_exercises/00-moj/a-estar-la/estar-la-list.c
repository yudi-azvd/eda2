#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-grafos
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-grafos/euvouestarla.html
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-grafos/euvouestarla.pdf

#define __CONNECTED 1
#define __UNCONNECTED 0

// List Undirected Graph

typedef int Vertex;

typedef struct Edge
{
  Vertex a, b;
} Edge;

typedef struct Node
{
  int vertex;
  struct Node *next;
} Node;

Node *Node_create(int vertex, Node *next)
{
  Node *node = (Node *)calloc(1, sizeof(Node));
  node->vertex = vertex;
  node->next = next;
  return node;
}

typedef struct ListUndGraph
{
  int vertices, edges;
  Node **arr;
} ListUndGraph;

ListUndGraph *ListUndGraph_create(int max_vertices)
{
  ListUndGraph *g = (ListUndGraph *)calloc(1, sizeof(ListUndGraph));
  g->edges = 0;
  g->vertices = max_vertices;
  g->arr = (Node **)calloc(max_vertices, sizeof(Node *));
  return g;
}

void ListUndGraph_destroy(ListUndGraph *g)
{
  Node *aux;

  for (int i = 0; i < g->vertices; i++)
  {
    while (g->arr[i] != NULL)
    {
      aux = g->arr[i]->next;
      free(g->arr[i]);
      g->arr[i] = aux;
    }
  }

  free(g->arr);
  free(g);
}

void ListUndGraph_insert_edge(ListUndGraph *g, Vertex a, Vertex b)
{
  g->edges++;
  g->arr[a] = Node_create(b, g->arr[a]);
  g->arr[b] = Node_create(a, g->arr[b]);
}

void ListUndGraph_show(ListUndGraph *g)
{
  printf("vertices: %d, edges: %d\n", g->vertices, g->edges);
  Node *node;
  for (int i = 0; i < g->vertices; i++)
  {
    printf("v %d: ", i);

    node = g->arr[i];
    while (node != NULL)
    {
      printf(" %d", node->vertex);
      node = node->next;
    }
    printf("\n");
  }
}

#define MAX_VERTICES 2000
#define WAS_NOT_THERE 0
#define WAS_HERE 1

void fill_graph(ListUndGraph *g, int N)
{
  int i, j, neighbours_in_line, neighbour;

  for (i = 0; i < N; i++)
  {
    scanf("%d", &neighbours_in_line);

    for (j = 0; j < neighbours_in_line; j++)
    {
      scanf("%d", &neighbour);
      ListUndGraph_insert_edge(g, i, neighbour);
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

int is_neighbour_to_where_julius_has_been(uint8_t julius_was_here[], ListUndGraph *g, Vertex v)
{
  Node *node = g->arr[v];
  for (; node != NULL; node = node->next)
  {
    if (julius_was_here[node->vertex] == WAS_HERE)
      return 1;
  }

  return 0;
}

void predict_where_julius_will_be(uint8_t julius_was_here[], int J, ListUndGraph *g)
{
  int i, vertex, will_be_here = 0, is_neighbour = 0;
  for (int i = 0; i < J; i++)
  {
    scanf("%d", &vertex);

    is_neighbour = is_neighbour_to_where_julius_has_been(julius_was_here, g, vertex);
    will_be_here = julius_was_here[vertex] || is_neighbour;

    printf("%s vou estar la\n", will_be_here ? "Eu" : "Nao");
  }
}

int main()
{
  int N, M, J;
  uint8_t julius_was_here[MAX_VERTICES] =
      {[0 ... MAX_VERTICES - 1] = WAS_NOT_THERE};

  scanf("%d %d %d", &N, &M, &J);

  ListUndGraph *g = ListUndGraph_create(N);

  fill_graph(g, N);
  read_places_julius_has_been(julius_was_here, M);
  predict_where_julius_will_be(julius_was_here, J, g);

  // ListUndGraph_destroy(g);
  return 0;
}