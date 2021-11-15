// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-grafos
// http://br.spoj.com/problems/NATUREZA.pdf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#define MAX_ANIMALS 5000
#define MAX_ANIMAL_LENGTH 31

#define LPHASHTABLE_INITIAL_CAPACITY 5003
// #define LPHASHTABLE_INITIAL_CAPACITY 7993
#define MAX_STRING 31

int hash_str(const char *v, int M)
{
  int hash_result, a = 31415, b = 27183;

  for (hash_result = 0; *v != '\0'; v++)
  {
    a = a * b % (M - 1);
    hash_result = (a * hash_result + *v) % M;
  }

  return hash_result;
}

typedef struct LPHashTable
{
  int capacity;
  int size;
  char strings[LPHASHTABLE_INITIAL_CAPACITY][MAX_STRING];
} LPHashTable;

LPHashTable *LPHashTable_create()
{
  LPHashTable *ht = (LPHashTable *)
      calloc(1, sizeof(LPHashTable));

  ht->size = 0;
  ht->capacity = LPHASHTABLE_INITIAL_CAPACITY;

  return ht;
}

void LPHashTable_destroy(LPHashTable *ht)
{
  free(ht);
}

void LPHashTable_print(LPHashTable *ht)
{
  if (ht == NULL)
    printf("HT is null");

  int i = 0;
  printf("[\n");
  for (; i < ht->capacity; i++)
  {
    if (ht->strings[i][0] != '\0')
      printf("  %4d <- %s\n", i, ht->strings[i]);
  }
  printf("]\n");
}

void LPHashTable_reset(LPHashTable *ht)
{
  int i = 0;
  ht->size = 0;
  
  // for (; i < ht->capacity; i++)
  //   ht->strings[i][0] = '\0';
  // tá certo isso?
  memset(ht->strings, '\0', ht->capacity*MAX_ANIMAL_LENGTH);
}

int LPHashTable_set(LPHashTable *ht, const char *key)
{
  int capacity = ht->capacity;
  unsigned hash = hash_str(key, capacity);
  int probe;
  char k[MAX_STRING];

  for (probe = 0; probe < capacity; probe++)
  {
    k[0] = '\0';
    strcpy(k, ht->strings[hash]);

    if (k[0] == '\0' || strcmp(k, key) == 0)
      break;

    hash = (hash + 1) % capacity;
  }

  ht->size++;
  strcpy(ht->strings[hash], key);
  return hash;
}

int LPHashTable_search(LPHashTable *ht, const char *key)
{
  int capacity = ht->capacity, probe, iterations = 0;
  unsigned hash = hash_str(key, capacity);
  char k[MAX_STRING];

  while (ht->strings[hash][0] != '\0')
  {
    if (iterations >= capacity)
      return -1;

    if (strcmp(ht->strings[hash], key) == 0)
      return hash;
    else
    {
      hash = (hash + 1) % capacity;
      iterations++;
    }
  }
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Adjacent Matrix Undirected Graph

// Aula do prof Bruno Ribas
// https://youtu.be/-CWbqWbNBTQ?t=5888

// IME USP
// https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/graphdatastructs.html

typedef int Vertex;

typedef struct Edge
{
  Vertex a, b;
} Edge;


#define __CONNECTED 1
#define __UNCONNECTED 0

// #define MAX_VERTICES 5000
#define MAX_VERTICES LPHASHTABLE_INITIAL_CAPACITY

// Em uma máquina de 64 bits
typedef struct MatUndGraph
{
  int vertices;                               // número de vértices
  int edges;                                  // número de arestas
  uint8_t matrix[MAX_VERTICES][MAX_VERTICES]; // matrix de booleanos
} MatUndGraph;

// Não é amigável para a cache da CPU
uint8_t **__MatUndGraph_matrix_set(uint8_t m[MAX_VERTICES][MAX_VERTICES], int max_vertices, int initial_value)
{
  int i;
  int j;
  for (i = 0; i < max_vertices; ++i)
    memset(m[i], initial_value, max_vertices);
}

MatUndGraph *MatUndGraph_create(int max_vertices)
{
  MatUndGraph *g = (MatUndGraph *)calloc(1, sizeof(MatUndGraph));
  g->vertices = max_vertices;
  g->edges = 0;
  __MatUndGraph_matrix_set(g->matrix, max_vertices, __UNCONNECTED);
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

void MatUndGraph_show(MatUndGraph *g)
{
  int i, j, entire_row_is_zero;
  printf("%d vertices, %d edges\n", g->vertices, g->edges);
  for (i = 0; i < g->vertices; i++)
  {
    entire_row_is_zero = 1;
    for (j = 0; j < g->vertices; j++)
    {
      if (g->matrix[i][j] != 0)
      {
        entire_row_is_zero = 0;
        break;
      }
    }

    if (entire_row_is_zero)
      continue;

    printf("%2d:", i);
    for (j = 0; j < g->vertices; j++)
    {
      if (g->matrix[i][j] == 1)
        printf(" %2d", j);
    }
    printf("\n");
  }
}

void MatUndGraph_reset(MatUndGraph *g)
{
  __MatUndGraph_matrix_set(g->matrix, g->vertices, __UNCONNECTED);
  g->edges = 0;
}

#define NOT_VISITED -1

int is_visited(int v)
{
  return v != NOT_VISITED;
}

void init_visited(int *visited, int size)
{
  for (size_t i = 0; i < size; i++)
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

int __MatUndGraph_dfs_r(MatUndGraph *g, Vertex src, int *visited, int counter, int *existent_animals, int existent_animals_size)
{
  int i = 0, new_src;
  visited[src] = counter++;

  for (; i < existent_animals_size; i++)
  {
    new_src = existent_animals[i];
    if (g->matrix[src][new_src] != 0)
      if (visited[new_src] == NOT_VISITED)
        counter = __MatUndGraph_dfs_r(g, new_src, visited, counter, existent_animals, existent_animals_size);
  }

  return counter;
}

// Retorna o número de vértices da componente conexa
int MatUndGraph_dfs_r(MatUndGraph *g, Vertex src, int *visited, int *existent_animals, int existent_animals_size)
{
  int counter = 0;
  counter = __MatUndGraph_dfs_r(g, src, visited, counter, existent_animals, existent_animals_size);
  return counter;
}

int MatUndGraph_max_size_connected_component(MatUndGraph *g, int *existent_animals, int existent_animals_size)
{
  int i, v, vv, max_cc_size = INT_MIN, curr_cc_size;
  int *visited = create_visited(g->vertices);

  for (i = 0; i < existent_animals_size; i++)
  {
    v = existent_animals[i];
    if (visited[v] == NOT_VISITED)
    {
      curr_cc_size = MatUndGraph_dfs_r(g, v, visited, existent_animals, existent_animals_size);
      if (curr_cc_size > max_cc_size)
        max_cc_size = curr_cc_size;
    }
  }

  free(visited);
  return max_cc_size;
}

int main(int argc, char const *argv[])
{
  int debug_mode = argc > 1;
  int i, j, number_of_animals, number_of_relationships;
  int v, w, max_cc_size = 0, cc_size, hash;
  char animal[MAX_ANIMAL_LENGTH], animal1[MAX_ANIMAL_LENGTH], animal2[MAX_ANIMAL_LENGTH];
  int existent_animals[MAX_ANIMALS];

  MatUndGraph *food_chain = MatUndGraph_create(LPHASHTABLE_INITIAL_CAPACITY);
  // MatUndGraph *food_chain = MatUndGraph_create(MAX_ANIMALS);
  // LPHashTable *animals = LPHashTable_create();
  LPHashTable animals;
  animals.size = 0;
  animals.capacity = LPHASHTABLE_INITIAL_CAPACITY;

  while (scanf("%d %d", &number_of_animals, &number_of_relationships) == 2 && !(number_of_animals == 0 && number_of_relationships == 0))
  {
    for (i = 0; i < number_of_animals; i++)
    {
      scanf("%s", animal);
      hash = LPHashTable_set(&animals, animal);
      existent_animals[i] = hash;
    }

    for (i = 0; i < number_of_relationships; i++)
    {
      scanf("%s %s", animal1, animal2);
      v = LPHashTable_search(&animals, animal1);
      w = LPHashTable_search(&animals, animal2);
      MatUndGraph_insert_edge(food_chain, w, v);
    }

    // if (debug_mode)
    // {
    //   LPHashTable_print(&animals);
    //   MatUndGraph_show(food_chain);
    // }

    max_cc_size = MatUndGraph_max_size_connected_component(food_chain, existent_animals, number_of_animals);
    printf("%d\n", max_cc_size);

    MatUndGraph_reset(food_chain);
    LPHashTable_reset(&animals);
  }

  MatUndGraph_destroy(food_chain);
  return 0;
}
