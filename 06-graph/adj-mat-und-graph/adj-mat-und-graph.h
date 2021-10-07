#ifndef ADJMATUNDGRAPH_H_INCLUDED
#define ADJMATUNDGRAPH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


// Adjacent Matrix Undirected Graph

// Aula do prof Bruno Ribas
// https://youtu.be/-CWbqWbNBTQ?t=5888

// IME USP
// https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/graphdatastructs.html

typedef struct Edge {
  int a, b;
} Edge;

typedef uint8_t Vertex;

Edge AdjMatUndGraph_edge_create(int a, int b) {
  Edge e = {a, b};
  return e;
}


// Em uma máquina de 64 bits
typedef struct AdjMatGraph {
  int vertices; // número de vértices
  int edges; // número de arestas
  Vertex **matrix;
  // 4 (bytes)
  // 4 (bytes)
  // 8 (bytes)
} AdjMatGraph;


// Não é amigável para a cache da CPU
Vertex** _AdjMatUndGraph_matrix_create(int max_vertices, int initial_value) {
  int i;
  Vertex** matrix = (Vertex**) malloc(max_vertices*sizeof(Vertex*));

  for (i = 0; i < max_vertices; ++i) {
    matrix[i] = (Vertex*) malloc(max_vertices*sizeof(Vertex));
  }

  int j;
  for (i = 0; i < max_vertices; ++i) {
    for (j = 0; j < max_vertices; ++j) {
      (matrix)[i][j] = initial_value;
    }
  }

  return matrix;
}

void _AdjMatUndGraph_matrix_destroy(AdjMatGraph* g) {
  int i;
  for (i = 0; i < g->vertices; ++i) {
    free(g->matrix[i]);
  }
  free(g->matrix);
}


AdjMatGraph* AdjMatUndGraph_create(int max_vertices) {
  AdjMatGraph* g = (AdjMatGraph*) calloc(1, sizeof(AdjMatGraph));
  g->vertices = max_vertices;
  g->edges = 0;
  g->matrix = _AdjMatUndGraph_matrix_create(max_vertices, 0);
  return g;
}

// cria um grafo com todos os vértices conectados entre si, até mesmo de
// a-a
AdjMatGraph* AdjMatUndGraph_create_complete(int max_vertices) {
  AdjMatGraph* g = (AdjMatGraph*) calloc(1, sizeof(AdjMatGraph));
  g->vertices = max_vertices;
  g->edges = 0;
  g->matrix = _AdjMatUndGraph_matrix_create(max_vertices, 1);
  return g;
}

void AdjMatUndGraph_destroy(AdjMatGraph* g) {
  _AdjMatUndGraph_matrix_destroy(g);
  free(g);
}

void AdjMatUndGraph_insert_edge(AdjMatGraph* g, Vertex a, Vertex b) {
  if (g->matrix[a][b] == 0)
    ++g->edges;
  
  g->matrix[a][b] = 1;
  g->matrix[b][a] = 1;
}

// void AdjMatUndGraph_remove_edge(AdjMatGraph* g, Edge e) {
void AdjMatUndGraph_remove_edge(AdjMatGraph* g, Vertex a, Vertex b) {
  if (g->matrix[a][b] == 1)
    --g->edges;
  
  g->matrix[a][b] = 0;
  g->matrix[b][a] = 0;
}


// int AdjMatUndGraph_edges(AdjMatGraph* g, Edge edges[]) {
//   int a, b, edges_count = 0;
//   for (a = 0; a < g->edges; a++) {
//     for (b = a+1; b < g->edges; b++) {
//       if (g->matrix[a][b] == 1) { 
//         edges[edges_count++] = AdjMatUndGraph_edge_create(a, b);
//       }
//     }
//   }

//   return edges_count;
// }

// AdjMatGraph AdjMatUndGraph_copy(AdjMatGraph* g) {

// }

void AdjMatUndGraph_show(AdjMatGraph* g) {
  int i, j;
  for (i = 0; i < g->vertices; i++) {
    printf("%2d:", i);
    for (j = 0; j < g->vertices; j++) {
      if (g->matrix[i][j] == 1)
        printf(" %2d", j);
    }
    printf("\n");
  }
}


#endif // ADJMATUNDGRAPH_H_INCLUDED