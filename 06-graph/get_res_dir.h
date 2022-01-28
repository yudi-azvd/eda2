#ifndef GET_RES_DIR_H_INCLUDED
#define GET_RES_DIR_H_INCLUDED

#include <unistd.h>
#include <linux/limits.h>
#include <string.h>

// Preenche RES_DIR com "/.../eda2/resources".
// "..." é o caminho absoluto até "eda2/".
//
// RES_DIR deve ser um buffer com PATH_MAX bytes.
void get_res_dir(char *res_dir)
{
  getcwd(res_dir, PATH_MAX);
  const char *root_dir_name = "eda2";
  char *root_dir_ptr = strstr(res_dir, root_dir_name);
  *(root_dir_ptr + strlen(root_dir_name)) = '\0';
  const char *res = "/resources";
  strcat(res_dir, res);
}

#endif // GET_RES_DIR_H_INCLUDED