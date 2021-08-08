#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include <stdlib.h>

// start-copy

typedef struct Node {
  int data;
  Node* prev;
  Node* next;
} Node;

typedef struct List {
  Node* head;
  Node* tail;
} List;


List* create_list() {
  List* ls = (List*) calloc(1, sizeof(List));
  ls->head = NULL;
  ls->tail = NULL;
  return ls;
}


void destroy_list(List* ls) {
  Node* node = ls->head;
  Node* aux = node;
  while (node != NULL) {
    node = node->next;
    free(aux);
    aux = node;
  }
  free(ls);
}


void add_head(List* ls, int data) {
  Node* new_head = (Node*) calloc(1, sizeof(Node));
  new_head->data = data;
  new_head->prev = NULL;
  
  if (ls->head == NULL) {
    new_head->next = NULL;
    ls->head = new_head;
    ls->tail = new_head;
  }
  else {
    new_head->next = ls->head;
    ls->head->prev = new_head;
    ls->head = new_head;
  }
}


int remove_head(List* ls) {
  Node* curr_head = ls->head;
  int data = 0;

  if (curr_head == NULL)
    return 0;

  data = curr_head->data;
  if (curr_head->next == NULL) {
    free(curr_head);
    ls->head = NULL;
    ls->tail = NULL;
  }
  else { // mais de um nó
    ls->head = curr_head->next;
    ls->head->prev = NULL;
    free(curr_head);
  }

  return data;
}


int list_size(List* ls) {
  Node* node = ls->head;
  int size = 0;
  while (node != NULL) {
    ++size;
    node = node->next;
  }
  return size;
}


void add_tail(List* ls, int data) {
  Node* new_tail = (Node*) calloc(1, sizeof(Node));
  new_tail->data = data;
  new_tail->next = NULL;

  if (ls->tail == NULL) {
    ls->head = new_tail;
    new_tail->prev = NULL;
  }
  else {
    ls->tail->next = new_tail;
    new_tail->prev = ls->tail;
  }
  
  ls->tail = new_tail;
}


int remove_tail(List* ls) {
  Node* curr_tail = ls->tail;
  int data = 0;

  if (curr_tail == NULL)
    return data;
  
  data = curr_tail->data;
  if (curr_tail->prev == NULL) {
    ls->head = NULL;
    ls->tail = NULL;
    free(curr_tail);
  }
  else {
    ls->tail = curr_tail->prev;
    free(curr_tail);
    ls->tail->next = NULL;
  }

  return data;    // 3234324
}

// end-copy

#endif
