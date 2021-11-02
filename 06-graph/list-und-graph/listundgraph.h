#ifndef LISTUNDGRAPH_H_INCLUDED
#define LISTUNDGRAPH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef int Vertex;

typedef struct Node
{
  int vertex;
  Node *next;
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

uint8_t ListUndGraph_equal(ListUndGraph *ga, ListUndGraph *gb)
{
  if (ga->edges != gb->edges)
    return 0;
  if (ga->vertices != gb->vertices)
    return 0;

  // É um pouco mais complicado que isso.
  // A ordem dos nós não deve fazer diferença
  // na igualdade de dois gráficos

  // for (int i = 0; i < ga->vertices; i++)
  // {
  //   if (ga->arr[i] != gb->arr[i])
  //     return 0;
  // }

  return 1;
}

ListUndGraph *ListUndGraph_copy(ListUndGraph *original)
{
  ListUndGraph *copy = ListUndGraph_create(original->vertices);
  copy->edges = original->edges;

  int i;
  for (i = 0; i < original->vertices; i++)
  {
    copy->arr[i] = original->arr[i];
  }

  // copiar cada nó
  // ...
  return copy;
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

#endif // LISTUNDGRAPH_H_INCLUDED