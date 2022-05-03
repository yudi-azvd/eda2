#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHTABLE_SIZE 3

// Vídeo do fábio akita


typedef struct HashTableNode {
  char *key;
  char* value;
  struct HashTableNode* next;
} HashTableNode;


typedef struct HashTable {
  struct HashTableNode *array[HASHTABLE_SIZE];
} HashTable;



HashTable* HashTable_create() {
  return (HashTable*) calloc(1, sizeof (HashTable));
}


void HashTable_destroy(HashTable* table) {
  int i;
  HashTableNode* node = NULL, *tmp = NULL;
  for (i = 0; i < HASHTABLE_SIZE; ++i) {
    node = table->array[i];
    while (node) {
      tmp = node->next;
      free(node);
      node = tmp;
    }
  }

  free(table);
}


HashTableNode* HashTable_create_node(char *key, char *value) {
  HashTableNode* node = (HashTableNode*) calloc(1, sizeof(HashTableNode));
  node->key = key;
  node->value = value;
  return node;
}


/* djb2 */
unsigned int HashTable_hash_code(char* key) {
  unsigned long hash = 5381;
  unsigned int c;

  while ((c = *key++)) {
    hash = (hash << 5) + hash + c;
  }

  return hash % HASHTABLE_SIZE;
}


void HashTable_insert(HashTable* table, char* key, char* value) {
  unsigned int index = HashTable_hash_code(key);
  HashTableNode* node = table->array[index];

  if (node == NULL) {
    table->array[index] = HashTable_create_node(key, value);
  }
  else {
    while (node) {
      if (node->next == NULL) {
        node->next = HashTable_create_node(key, value);
        break;
      }
      node = node->next;
    }
  }
}


void HashTable_remove(HashTable* table, char *key) {
  unsigned int index = HashTable_hash_code(key);
  HashTableNode* node = table->array[index];
  HashTableNode** aux = &table->array[index];

  while (node) {
    if (strcmp(node->key, key) == 0) {
      (*aux) = node->next;
      free(node);
      return;
    }

    aux = &(*aux)->next;
    node = node->next;
  }
}


char* HashTable_search(HashTable* table, char* key) {
  unsigned int index = HashTable_hash_code(key);
  HashTableNode* node = table->array[index];

  while (node) {
    if (strcmp(node->key, key) == 0) {
      return node->value;
    }
    node = node->next;
  }

  // isso pode?
  return "";
}


#endif