// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-grafos
// http://br.spoj.com/problems/NATUREZA.pdf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ANIMALS 5000
#define MAX_ANIMAL_LENGTH 31

void print_animals(char *animals[MAX_ANIMAL_LENGTH], int animals_size)
{
  int i = 0;
  for (; i < animals_size; i++)
  {
    printf("> %s\n", animals[i]);
  }
}

int cmp_str(const void *str1, const void *str2)
{
  const char *s1 = *(const char **)str1;
  const char *s2 = *(const char **)str2;

  // return strncmp(s1, s2, MAX_ANIMAL_LENGTH - 1);
  return strcmp(s1, s2);
}

void allocate_animals(char *animals[])
{
  for (size_t i = 0; i < MAX_ANIMALS; i++)
  {
    animals[i] = (char *)calloc(1, sizeof(char));
  }
}

int main(int argc, char const *argv[])
{
  int i, j, number_of_animals, number_of_relationships;
  int animals_size;
  char *animals[MAX_ANIMAL_LENGTH];
  char animal1[MAX_ANIMAL_LENGTH], animal2[MAX_ANIMAL_LENGTH];

  allocate_animals(animals);

  while (1)
  {
    scanf("%d %d", &number_of_animals, &number_of_relationships);

    if (number_of_animals == 0 && number_of_relationships == 0)
      break;

    for (i = 0; i < number_of_animals; i++)
    {
      scanf("%s", animals[i]);
    }

    animals_size = i;
    qsort(animals, animals_size, sizeof(char *), cmp_str);
    print_animals(animals, animals_size);

    for (i = 0; i < number_of_relationships; i++)
    {
      scanf("%s %s", animal1, animal2);
      printf("%s -> %s\n", animal2, animal1);
    }
  }

  return 0;
}
