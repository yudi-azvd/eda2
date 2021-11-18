#ifndef LISTUNDGRAPH_FILE_H_INCLUDED
#define LISTUNDGRAPH_FILE_H_INCLUDED

#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>
#include <string.h>

#include "../get_res_dir.h"

#include "listundgraph.h"

ListUndGraph *ListUndGraph_create_from_file(const char *filepath)
{
  char full_filepath[PATH_MAX];
  get_res_dir(full_filepath);
  strcat(full_filepath, "/");
  strcat(full_filepath, filepath);

  FILE* fp = fopen(full_filepath, "r");
  if (!fp) {
    printf("not possible to open %s", full_filepath);
  }

  int vertices, edges = -1, i = 0, v, w;
  fscanf(fp, "%d",  &vertices);
  fscanf(fp, "%d",  &edges);

  ListUndGraph *g = ListUndGraph_create(vertices);
  while (i++ < edges)
  {
    fscanf(fp, "%d %d",  &v, &w);
    ListUndGraph_insert_edge(g, v, w);
  }

  fclose(fp);
  return g;
}

#endif // LISTUNDGRAPH_FILE_H_INCLUDED