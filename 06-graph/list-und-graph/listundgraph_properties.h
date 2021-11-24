#ifndef LISTUNDGRAPH_PROPERTIES_H_INCLUDED
#define LISTUNDGRAPH_PROPERTIES_H_INCLUDED

#include "listundgraph.h"
#include "listundgraph_bfspaths.h"

// exercise-4.1.16

typedef struct Properties
{
  int *eccentricities;
  int diameter;
  int radius;
  int center;
} Properties;

int __calculate_center(int *eccentricities, int size, int radius) {
  for (size_t v = 0; v < size; v++)
  {
    if (eccentricities[v] == radius)  
      return v;
  }
  
  return -1;
}


// Retorna o centro no retorno normal da função.
// Retorna o diẫmetro e raio pelos argumentos
void __calculate_diameter_radius(int *eccentricities, int size, int *diam, int *radius)
{
  int max_ecc = 0;
  int min_ecc = INT_MAX;
  for (int v = 0; v < size; v++)
  {
    if (eccentricities[v] > max_ecc)
      max_ecc = eccentricities[v];
    if (eccentricities[v] < min_ecc)
      min_ecc = eccentricities[v];
  }

  *diam = max_ecc;
  *radius = min_ecc;
}

int __calculate_eccentricity(ListUndGraph *g, Vertex v)
{
  int max_distance = INT_MIN;
  BFSPaths *paths = BFSPaths_create(g, v);

  for (size_t i = 0; i < g->vertices; i++)
  {
    if (paths->dist_to[i] > max_distance)
      max_distance = paths->dist_to[i];
  }

  BFSPaths_destroy(paths);
  return max_distance;
}

void __calculate_eccentricities(ListUndGraph *g, int *eccentricities)
{
  int v = 0, size = g->vertices;
  for (; v < size; v++)
  {
    eccentricities[v] = __calculate_eccentricity(g, v);
  }
}

Properties *Properties_of(ListUndGraph *g)
{
  Properties *props = (Properties *)calloc(1, sizeof(Properties));
  props->eccentricities = (int *)calloc(g->vertices, sizeof(int));

  int size = g->vertices;
  __calculate_eccentricities(g, props->eccentricities);
  __calculate_diameter_radius(props->eccentricities, size, &props->diameter, &props->radius);
  props->center = __calculate_center(props->eccentricities, g->vertices, props->radius);
  return props;
}

void Properties_destroy(Properties *props)
{
  free(props->eccentricities);
  free(props);
}

int Properties_eccentricity(Properties *props, Vertex v)
{
  return props->eccentricities[v];
}

int Properties_diameter(Properties *props)
{
  return props->diameter;
}

int Properties_radius(Properties *props)
{
  return props->radius;
}

int Properties_center(Properties *props)
{
  return props->center;
}

#endif // LISTUNDGRAPH_PROPERTIES_H_INCLUDED