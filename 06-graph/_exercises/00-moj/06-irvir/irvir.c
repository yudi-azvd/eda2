#include <stdio.h>
#include <stdlib.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-grafos
// https://br.spoj.com/problems/IREVIR.pdf

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// List Directed Graph

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

typedef struct ListDirGraph
{
  int vertices, edges;
  Node **arr;
} ListDirGraph;

int ListDirGraph_edges_count(ListDirGraph *g)
{
  return g->edges;
}

int ListDirGraph_vertices_count(ListDirGraph *g)
{
  return g->vertices;
}

ListDirGraph *ListDirGraph_create(int max_vertices)
{
  ListDirGraph *g = (ListDirGraph *)calloc(1, sizeof(ListDirGraph));
  g->edges = 0;
  g->vertices = max_vertices;
  g->arr = (Node **)calloc(max_vertices, sizeof(Node *));
  return g;
}

void ListDirGraph_destroy(ListDirGraph *g)
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

void ListDirGraph_insert_edge(ListDirGraph *g, Vertex a, Vertex b)
{
  g->edges++;
  g->arr[a] = Node_create(b, g->arr[a]);
}

void ListDirGraph_show(ListDirGraph *g)
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

int __ListDirGraph_dfs_r(ListDirGraph *g, Vertex src, int *visited, int counter)
{
  int new_src = -1;
  visited[src] = counter++;
  Node *node = g->arr[src];

  for (; node != NULL; node = node->next)
  {
    new_src = node->vertex;
    if (visited[new_src] == NOT_VISITED)
      counter = __ListDirGraph_dfs_r(g, new_src, visited, counter);
  }

  return counter;
}

void ListDirGraph_dfs_r(ListDirGraph *g, Vertex src, int *visited)
{
  // counter na vdd seria uma variável de instância em um objeto DFSSearch
  int counter = 0;
  __ListDirGraph_dfs_r(g, src, visited, counter);
}

int ListDirGraph_count_connected_components(ListDirGraph *g)
{
  int v, connected_components_count = 0;
  int *visited = create_visited(g->vertices);

  for (v = 0; v < g->vertices; v++)
  {
    if (visited[v] == NOT_VISITED)
    {
      ListDirGraph_dfs_r(g, v, visited);
      connected_components_count++;
    }
  }

  free(visited);
  return connected_components_count;
}

int main()
{
  int i, vertices = 0, lines = 0;
  int v, w, is_one_way = 0, connected_components_count;

  ListDirGraph* g;

  while (1)
  {
    scanf("%d %d", &vertices, &lines);

    if (vertices == 0 && lines == 0)
      break;

    g = ListDirGraph_create(vertices);

    for (i = 0; i < lines; i++)
    {
      scanf("%d %d %d", &v, &w, &is_one_way);

      if (is_one_way == 1) {
        ListDirGraph_insert_edge(g, v-1, w-1);
      }
      else {
        ListDirGraph_insert_edge(g, v-1, w-1);
        ListDirGraph_insert_edge(g, w-1, v-1);
      }
    }
    
    connected_components_count = -1;
    connected_components_count = ListDirGraph_count_connected_components(g);

    // TÁ ERRADO!!!
    printf("%d\n", connected_components_count == 1);

    ListDirGraph_destroy(g);
  }

  return 0;
}
