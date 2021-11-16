#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <iostream>
#include <fstream>

#include <unistd.h>
#include <limits.h>

std::string get_res_dir()
{
  char cwd[PATH_MAX];
  const std::string base_dir_name = "eda2";
  getcwd(cwd, PATH_MAX);
  std::string curr_dir(cwd);
  int base_pos = curr_dir.find(base_dir_name);
  std::string base_dir = curr_dir.substr(0, base_pos + base_dir_name.length());
  // printf(">>> cwd: %s\n", cwd);
  // printf(">>> curr dir: %s\n", curr_dir.c_str());
  // printf(">>> base dir: %s\n", base_dir.c_str());

  return base_dir + "/resources";
}

void fill_graph_tinyG(ListUndGraph **g)
{
  std::string filepath = get_res_dir() + "/algs4-data/tinyG.txt";
  std::fstream infile(filepath.c_str());

  if (!infile.is_open())
  {
    printf("not possible to open file: %s\n", filepath.c_str());
    exit(1);
  }

  int vertices, edges, v, w, i = 0;
  infile >> vertices >> edges;

  *g = ListUndGraph_create(vertices);

  while (i++ < edges)
  {
    infile >> v >> w;
    ListUndGraph_insert_edge(*g, v, w);
  }
}


void fill_graph_tinyGex2(ListUndGraph **g)
{
  std::string filepath = get_res_dir() + "/algs4-data/tinyGex2.txt";
  std::fstream infile(filepath.c_str());

  if (!infile.is_open())
  {
    printf("not possible to open file: %s\n", filepath.c_str());
    exit(1);
  }

  int vertices, edges, v, w, i = 0;
  infile >> vertices >> edges;

  *g = ListUndGraph_create(vertices);

  while (i++ < edges)
  {
    infile >> v >> w;
    ListUndGraph_insert_edge(*g, v, w);
  }
}


#endif // UTIL_H_INCLUDED