#include <stdio.h>

typedef struct student_t {
  char name[5];
  int id;
} student_t;

typedef student_t item_t;

#define less(a, b) (a.id < b.id)

#include "pq-indexed.h"

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
    printf("> %2d: %s\n", studs[i].id, studs[i].name);
}

void print_students_pq(student_t* studs, PQIndexed* pq) {
  int stud_index;
  printf("\nPQ:\n");
  for (int i = 1; i <= pq->size; i++) {
    stud_index = pq->pq[i];
    printf("Student %2d %2d | %2d: %s\n", i, stud_index, studs[stud_index].id, studs[stud_index].name);
  }
}

void print_student(student_t s) {
  printf("Student -> %2d: %s\n", s.id, s.name);
}

int main() {
  int student_index = 0, i = 0, n_students = 0;
  student_t stu, students[MAX_STUDENTS];
  PQIndexed* pq = PQIndexed_create(students, MAX_STUDENTS);

  n_students = read_students(students);

  while (scanf("%d", &student_index) != EOF) {
    PQIndexed_insert(pq, student_index);
  }

  print_students_pq(students, pq);
  printf("\n");

  while (!PQIndexed_empty(pq)) {
    print_student(students[PQIndexed_del_max(pq)]);
  }

  // print_students(students, n_students);

  PQIndexed_destroy(pq);
  return 0;
}