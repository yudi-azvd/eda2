#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-grafos
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-grafos/euvouestarla.html
// https://moj.naquadah.com.br/contests/bcr-EDA2-2021_1-grafos/euvouestarla.pdf


int main()
{
  int i, N, M, J;

  scanf("%d %d %d", &N, &M, &J);


  for (i = 0; i < N; i++)
  {
    int neighbours_in_line;
    scanf("%d", &neighbours_in_line);

    for (size_t j = 0; j < neighbours_in_line; j++)
    {
      int neighbour;
      scanf("%d", &neighbour);
    }
  }

  return 0;
}