#ifndef LISTUNDGRAPH_H_INCLUDED
#define LISTUNDGRAPH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef int Vertex;

typedef struct Node
{
  int vertex;
  Node* next;
} Node;

Node* Node_create(int vertex, Node* next) {
  Node* node = (Node*) calloc(1, sizeof(node));
  node->vertex = vertex;
  node->next = next;
  return node;
}

typedef struct ListUndGraph
{
  int vertices, edges;
  Node** arr;
} ListUndGraph;

int ListUndGraph_edges_count(ListUndGraph* g) {
  return g->edges;
}

int ListUndGraph_vertices_count(ListUndGraph* g) {
  return g->vertices;
}

ListUndGraph* ListUndGraph_create(int max_vertices) {
  ListUndGraph* g = (ListUndGraph*) calloc(1, sizeof(g));
  g->edges = 0;
  g->vertices = max_vertices;
  g->arr = (Node**) calloc(max_vertices, sizeof(Node*));
  return g;
}

void ListUndGraph_destroy(ListUndGraph* g) {
  Node* node;

  for (int i = 0; i < g->vertices; i++)
  {
    node = g->arr[i];
    while (node != NULL)
    {
      free(node);
      node = node->next;
    }
  }
  
  free(g->arr);
  free(g);
}

void ListUndGraph_insert_edge(ListUndGraph* g, Vertex a, Vertex b) {
  Node* new_node = (Node*) calloc(1, sizeof(new_node));
  g->edges++;
  g->arr[a] = Node_create(b, g->arr[a]);
  g->arr[b] = Node_create(a, g->arr[b]);
}

void ListUndGraph_show(ListUndGraph* g) {
  printf("vertices: %d, edges: %d\n", g->vertices, g->edges);
  Node * node;
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