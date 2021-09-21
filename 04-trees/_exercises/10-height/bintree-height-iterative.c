#include <stdio.h>
#include <stdlib.h>


typedef struct node_t {
  int value;
  struct node_t* left;
  struct node_t* right;
} node_t;


int bintree_height_i(node_t* root) {
  return 1;
}


// assumir que dados não se repetem
void search_insert(node_t* node, int to_insert, char op, int to_find) {
  if (node == NULL)
    return;
  
  if (node->value == to_find) {
    node_t* new_node = calloc(1, sizeof(node_t));
    new_node->value = to_insert;
    new_node->right = NULL;
    new_node->left = NULL;
    if (op == 'E')
      node->left = new_node;
    else
      node->right = new_node;
    return;
  }
  else {
    search_insert(node->left, to_insert, op, to_find);
    search_insert(node->right, to_insert, op, to_find);
  }
}

int main() {
  int to_find, to_insert;
  char operation;
  node_t r;
  node_t* root = NULL;
  
  int eof = scanf("%d", &to_insert);
  if (eof != EOF) { 
    root = &r;
    root->value = to_insert;
    root->left = NULL;
    root->right = NULL;

    while (scanf("%d %c %d", &to_insert, &operation, &to_find) != EOF) {
      search_insert(&r, to_insert, operation, to_find);
    }
  }

  printf("%d\n", bintree_height_i(root));

  return 0;
}