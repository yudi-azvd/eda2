// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-grafos
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-grafos/grafo-ajude-joao.html
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-grafos/grafo-ajude-joao.pdf

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
  int vertices, edges, *edges_counts;
  Node **arr;
} ListUndGraph;

int ListUndGraph_edges_count(ListUndGraph *g)
{
  return g->edges;
}

int ListUndGraph_vertices_count(ListUndGraph *g)
{
  return g->vertices;
}

ListUndGraph *ListUndGraph_create(int max_vertices)
{
  ListUndGraph *g = (ListUndGraph *)calloc(1, sizeof(ListUndGraph));
  g->edges = 0;
  g->vertices = max_vertices;
  g->edges_counts = (int *)calloc(max_vertices, sizeof(int));
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

  free(g->edges_counts);
  free(g->arr);
  free(g);
}

void ListUndGraph_insert_edge(ListUndGraph *g, Vertex a, Vertex b)
{
  g->edges++;
  g->arr[a] = Node_create(b, g->arr[a]);
  g->edges_counts[a]++;
  g->arr[b] = Node_create(a, g->arr[b]);
  g->edges_counts[b]++;
}

void ListUndGraph_show(ListUndGraph *g)
{
  printf("vertices: %d, edges: %d\n", g->vertices, g->edges);
  Node *node;
  for (int i = 0; i < g->vertices; i++)
  {
    if (g->vertices > 15 && g->edges_counts[i] == 0)
      continue;

    printf("%3d | v_count %3d: ", i, g->edges_counts[i]);

    node = g->arr[i];
    while (node != NULL)
    {
      printf(" %d", node->vertex);
      node = node->next;
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
  for (int i = 0; i < size; i++)
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

int __ListUndGraph_dfs_r(ListUndGraph *g, Vertex src, int *visited, int counter)
{
  int new_src = -1;
  visited[src] = counter++;
  Node *node = g->arr[src];

  for (; node != NULL; node = node->next)
  {
    new_src = node->vertex;
    if (visited[new_src] == NOT_VISITED)
      counter = __ListUndGraph_dfs_r(g, new_src, visited, counter);
  }

  return counter;
}

void ListUndGraph_dfs_r(ListUndGraph *g, Vertex src, int *visited)
{
  // counter na vdd seria uma variável de instância em um objeto DFSSearch
  int counter = 0;
  __ListUndGraph_dfs_r(g, src, visited, counter);
}

int ListUndGraph_count_connected_components(ListUndGraph *g)
{
  int v, connected_components_count = 0;
  int *visited = create_visited(g->vertices);

  for (v = 0; v < g->vertices; v++)
  {
    if (visited[v] == NOT_VISITED)
    {
      ListUndGraph_dfs_r(g, v, visited);
      connected_components_count++;
    }
  }

  free(visited);
  return connected_components_count;
}

int find_vertex_with_greatest_edges_count(ListUndGraph *g)
{
  int i, max_index = 0;
  for (i = 0; i < g->vertices; i++)
  {
    if (g->edges_counts[i] > g->edges_counts[max_index])
      max_index = i;
  }

  return max_index;
}

int main(int argc, char **argv)
{
  int debug_mode = argc > 1 ? 1 : 0;
  int v, w, john_current_vertex, max_vertices;

  scanf("%d %d", &max_vertices, &john_current_vertex);

  ListUndGraph *g = ListUndGraph_create(max_vertices);

  while (scanf("%d %d", &v, &w) != EOF)
  {
    ListUndGraph_insert_edge(g, v, w);
  }

  int max_edges_count_vertex = find_vertex_with_greatest_edges_count(g);
  int max_edges_count = g->edges_counts[max_edges_count_vertex];
  int john_vertex_edges_count = g->edges_counts[john_current_vertex];

  if (debug_mode)
  {
    printf("\n");
    ListUndGraph_show(g);
    printf("\n");
    printf("            john vertex: %d\n", john_current_vertex);
    printf("john vertex edges count: %d\n", john_vertex_edges_count);
    printf(" max edges count vertex: %d\n", max_edges_count_vertex);
    printf("        max edges count: %d\n", max_edges_count);
    printf("\n");
    printf("#clusters %d\n", ListUndGraph_count_connected_components(g));
  }

  if (john_current_vertex == max_edges_count_vertex && max_edges_count == 0)
    printf("Fique em casa\n");
  else if (john_current_vertex == max_edges_count_vertex && max_edges_count > 0)
    printf("Bora pra estrada\n");
  else if (max_edges_count_vertex > john_current_vertex)
    printf("Vamos para %d\n", max_edges_count_vertex);
  else
  {
  }

  ListUndGraph_destroy(g);
  return 0;
}

// encontrar o agrupamento de cidades com maior quantidade de estradas

// encontrar a componente conexa com maior quantidade de arestas
// dado um vértice, como encontrar a sua componente conexa?
// dado um componente conexo, como determinar se um vértice está nele?
