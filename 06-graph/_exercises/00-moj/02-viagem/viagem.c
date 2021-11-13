// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-grafos
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-grafos/grafo-ajude-joao.html
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-grafos/grafo-ajude-joao.pdf

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

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

typedef struct ConnectedComponent
{
  int smallest_vertex, size;
  Vertex *vertices;
} ConnectedComponent;

int cmp_cc_size(const void *cc1, const void *cc2)
{
  ConnectedComponent c1 = *(ConnectedComponent *)cc1;
  ConnectedComponent c2 = *(ConnectedComponent *)cc2;
  if (c1.size == c2.size)
    return c2.smallest_vertex - c1.smallest_vertex;
  return c1.size - c2.size;
}

ConnectedComponent ConnectedComponent_create(int vertices)
{
  ConnectedComponent cc; // = (ConnectedComponent *)calloc(1, sizeof(ConnectedComponent));
  cc.size = 0;
  cc.smallest_vertex = INT_MAX;
  cc.vertices = (Vertex *)calloc(vertices, sizeof(Vertex));
  return cc;
}

void ConnectedComponent_destroy(ConnectedComponent *cc)
{
  free(cc->vertices);
}

void ConnectedComponent_destroy_array(ConnectedComponent *cc, int size)
{
  for (size_t i = 0; i < size; i++)
  {
    ConnectedComponent_destroy(&cc[i]);
  }
  free(cc);
}

void ConnectedComponent_add(ConnectedComponent *cc, Vertex v)
{
  cc->vertices[cc->size++] = v;
  if (v < cc->smallest_vertex)
    cc->smallest_vertex = v;
}

uint8_t ConnectedComponent_has_edges(ConnectedComponent *cc)
{
  return cc->size > 1;
}

int __ListUndGraph_cc_dfs_r(ListUndGraph *g, Vertex src, int *visited, int counter, ConnectedComponent *cc)
{
  int new_src = -1;
  visited[src] = counter++;
  ConnectedComponent_add(cc, src);
  Node *node = g->arr[src];

  for (; node != NULL; node = node->next)
  {
    new_src = node->vertex;
    if (visited[new_src] == NOT_VISITED)
      counter = __ListUndGraph_cc_dfs_r(g, new_src, visited, counter, cc);
  }

  return counter;
}

void ListUndGraph_cc_dfs_r(ListUndGraph *g, Vertex src, int *visited, ConnectedComponent *cc)
{
  // counter na vdd seria uma variável de instância em um objeto DFSSearch
  int counter = 0;
  __ListUndGraph_cc_dfs_r(g, src, visited, counter, cc);
}

ConnectedComponent *ListUndGraph_connected_components(ListUndGraph *g, int *cc_size)
{
  int v, cc_index = 0;
  int *visited = create_visited(g->vertices);

  ConnectedComponent *cc =
      (ConnectedComponent *)calloc(g->vertices, sizeof(ConnectedComponent));

  for (v = 0; v < g->vertices; v++)
  {
    if (visited[v] == NOT_VISITED)
    {
      cc[cc_index] = ConnectedComponent_create(g->vertices);
      ListUndGraph_cc_dfs_r(g, v, visited, &cc[cc_index]);
      cc_index++;
    }
  }

  *cc_size = cc_index;
  free(visited);
  return cc;
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

int is_john_in_greatest_size_region(Vertex john_v, ConnectedComponent *regions, int region_size)
{
  int cc_index = region_size - 1, v;
  int greatest_region_size = regions[cc_index].size;

  while (regions[cc_index].size == greatest_region_size)
  {

    for (v = 0; v < regions[cc_index].size; v++)
    {
      if (regions[cc_index].vertices[v] == john_v)
        return 1;
    }

    cc_index--;
  }

  return 0;
}

int find_john_region(Vertex john_v, ConnectedComponent *regions, int region_size)
{
  int cc_index = region_size - 1, v;
  int greatest_region_size = regions[region_size - 1].size;
  ConnectedComponent c;

  for (; cc_index >= 0; cc_index--)
  {
    c = regions[cc_index];

    for (v = 0; v < c.size; v++)
    {
      if (c.vertices[v] == john_v)
        return cc_index;
    }
  }

  return -1;
}

int main(int argc, char **argv)
{
  int debug_mode = argc > 1;
  int v, w, john_current_vertex, max_vertices;

  scanf("%d %d", &max_vertices, &john_current_vertex);

  ListUndGraph *g = ListUndGraph_create(max_vertices);

  while (scanf("%d %d", &v, &w) != EOF)
  {
    ListUndGraph_insert_edge(g, v, w);
  }

  int cc_size = -1;
  ConnectedComponent *cc = ListUndGraph_connected_components(g, &cc_size);
  qsort(cc, cc_size, sizeof(ConnectedComponent), cmp_cc_size);

  int john_region = find_john_region(john_current_vertex, cc, cc_size);
  int john_is_in_greatest_region =
      is_john_in_greatest_size_region(john_current_vertex, cc, cc_size);

  if (debug_mode)
  {
    printf("\n");
    ListUndGraph_show(g);
    printf("\n");
    printf("               john vertex: %d\n", john_current_vertex);
    printf("               john region: %d\n", john_region);
    printf("john is in greatest region: %d\n", john_is_in_greatest_region);
    printf("\n");
    printf("                  #regiões: %d\n", cc_size);
  }

  if (john_is_in_greatest_region && !ConnectedComponent_has_edges(&cc[john_region]))
  {
    printf("Fique em casa\n");
  }
  else if (john_is_in_greatest_region)
  {
    printf("Bora pra estrada\n");
  }
  else {
    printf("Vamos para %d\n", cc[cc_size-1].smallest_vertex);
  }

  // ConnectedComponent_destroy_array(cc, cc_size);
  // ListUndGraph_destroy(g);
  return 0;
}

// !!! encontrar o agrupamento de cidades com maior quantidade de cidades !!!

// encontrar a componente conexa com maior quantidade de vértices
// dado um vértice, como encontrar a sua componente conexa?
// dado um componente conexo, como determinar se um vértice está nele?
