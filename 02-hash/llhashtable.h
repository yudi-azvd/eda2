#ifndef LLHASHTABLE_H_INCLUDED
#define LLHASHTABLE_H_INCLUDED

// Linked List LLHashTable <string, string>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LLHASHTABLE_INITIAL_CAPACITY 3


typedef struct LLHashTableNode {
  char *key;
  char* value;
  struct LLHashTableNode* next;
} LLHashTableNode;


typedef struct LLHashTable {
  int capacity;
  struct LLHashTableNode *array[LLHASHTABLE_INITIAL_CAPACITY];
} LLHashTable;



LLHashTable* LLHashTable_create() {
  LLHashTable* ht = (LLHashTable*) calloc(1, sizeof (LLHashTable));
  ht->capacity = LLHASHTABLE_INITIAL_CAPACITY;
  return ht;
}


void LLHashTable_destroy(LLHashTable* ht) {
  int i;
  LLHashTableNode* node = NULL, *tmp = NULL;
  for (i = 0; i < ht->capacity; ++i) {
    node = ht->array[i];
    while (node) {
      tmp = node->next;
      free(node);
      node = tmp;
    }
  }

  free(ht);
}


LLHashTableNode* LLHashTable_create_node(char *key, char *value) {
  LLHashTableNode* node = (LLHashTableNode*) calloc(1, sizeof(LLHashTableNode));
  node->key = key;
  node->value = value;
  return node;
}


/* djb2 */
unsigned int LLHashTable_hash(char* key) {
  unsigned long hash = 5381;
  unsigned int c;

  while ((c = *key++)) {
    hash = (hash << 5) + hash + c;
  }

  return hash % LLHASHTABLE_INITIAL_CAPACITY;
}


void HashTable_insert(LLHashTable* ht, char* key, char* value) {
  unsigned int index = LLHashTable_hash(key);
  LLHashTableNode* node = ht->array[index];

  if (node == NULL) {
    ht->array[index] = LLHashTable_create_node(key, value);
  }
  else {
    while (node) {
      if (node->next == NULL) {
        node->next = LLHashTable_create_node(key, value);
        break;
      }
      node = node->next;
    }
  }
}


void LLHashTable_remove(LLHashTable* ht, char *key) {
  unsigned int index = LLHashTable_hash(key);
  LLHashTableNode* node = ht->array[index];
  LLHashTableNode** aux = &ht->array[index];

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


char* HashTable_search(LLHashTable* ht, char* key) {
  unsigned int index = LLHashTable_hash(key);
  LLHashTableNode* node = ht->array[index];

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