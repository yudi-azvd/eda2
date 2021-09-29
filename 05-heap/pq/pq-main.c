#include <stdio.h>

typedef struct student_t {
  char name[5];
  int id;
} student_t;

typedef student_t item_t;

// #define less(a, b) (a.id < b.id)

#include "pq.h"

#define MAX_STUDENTS 6

int read_students(student_t studs[MAX_STUDENTS]) {
  int i, n_students;
  scanf("%d", &n_students);

  for (i = 0; i < n_students; i++)
    scanf("%d %s", &studs[i].id, studs[i].name);
  
  return n_students;
}

void print_students(student_t* studs, int size) {
  for (size_t i = 0; i < size; i++)
    printf("> %3d: %s\n", studs[i].id, studs[i].name);
}

void print_student(student_t s) {
  printf("Student -> %3d: %s\n", s.id, s.name);
}

int main() {
  int n;
  PQ* pq = PQ_create(MAX_STUDENTS);

  while (scanf("%d", &n) != EOF) {
    PQ_insert(pq, n);
  }

  while (!PQ_empty(pq)) {
    printf("%d\n", PQ_del_max(pq));
  }

  PQ_destroy(pq);
  return 0;
}