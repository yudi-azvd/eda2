#ifndef GET_RES_DIR_H_INCLUDED
#define GET_RES_DIR_H_INCLUDED

#include <unistd.h>
#include <linux/limits.h>
#include <string.h>

// Preenche `res_dir` com /.../eda2/resources.
// "..." é o caminho absoluto até eda2/.
// res_dir deve ser um buffer com PATH_MAX bytes
void get_res_dir(char *res_dir)
{
  getcwd(res_dir, PATH_MAX);
  const char *base_dir_name = "eda2";
  char *base_ptr = strstr(res_dir, base_dir_name);
  *(base_ptr + strlen(base_dir_name)) = '\0';
  const char *res = "/resources";
  strcat(res_dir, res);
}

#endif // GET_RES_DIR_H_INCLUDED