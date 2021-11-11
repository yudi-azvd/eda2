#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct Node_q
{
  int value;
  struct Node_q *next;
} Node_q;

typedef struct Queue
{
  int size;
  Node_q *head, *tail;
} Queue;

Queue *Queue_create()
{
  Queue *q = (Queue *)calloc(1, sizeof(Queue));
  q->head = NULL;
  q->tail = NULL;
  return q;
}

void Queue_destroy(Queue *q)
{
  Node_q *aux = q->head, *node = q->head;

  while (node != NULL)
  {
    node = node->next;
    free(aux);
    aux = node;
  }

  q->head = q->tail = NULL;
  free(q);
}

int Queue_empty(Queue *q)
{
  return q->head == NULL;
}

void Queue_enq(Queue *q, int value)
{
  Node_q *node = (Node_q *)calloc(1, sizeof(Node_q));
  node->value = value;
  node->next = NULL;

  if (q->head == NULL)
  {
    q->head = node;
    q->tail = node;
  }
  else
  {
    node->next = q->head;
    q->head = node;
  }
}

int Queue_deq(Queue *q)
{
  Node_q *to_remove = q->head;
  int value = to_remove->value;

  if (to_remove->next == NULL)
  {
    q->head = NULL;
    q->tail = NULL;
  }
  else
  {
    q->head = to_remove->next;
  }

  free(to_remove);
  return value;
}

#endif // QUEUE_H_INCLUDED