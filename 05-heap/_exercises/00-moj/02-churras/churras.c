#include <stdlib.h>
#include <stdio.h>

#define MAX_RESTAURANTS 100000

int main() {
  int i, n_restaurants, n_friends, grade;

  while (1) {
    scanf("%d %d", &n_restaurants, &n_friends);

    for (i = 0; i < n_restaurants; i++) {
      scanf("%d", &grade);
      printf("grade %d\n", grade);
    }
    
    printf("\n");
    
    if (n_restaurants == 0 && n_friends == 0)
      break;
  }
  
  return 0;
}