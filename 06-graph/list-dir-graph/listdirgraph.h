#ifndef LISTDIRGRAPH_H_INCLUDED
#define LISTDIRGRAPH_H_INCLUDED

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

uint8_t ListDirGraph_has_edge(ListDirGraph *g, Vertex a, Vertex b)
{
  Node *aux = g->arr[a];

  while (aux != NULL)
  {
    if (aux->vertex == b)
      return 1;
    aux = aux->next;
  }

  return 0;
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

#endif // LISTDIRGRAPH_H_INCLUDED
