#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENTS_SIZE 100


typedef struct student_t {
  int score;
  char name[20];
} student_t;


void print_students(student_t* students, int size) {
  int i;
  for (i = 0; i < size; ++i)
    printf("%s %d\n", students[i].name, students[i].score);
}


int cmpscore(const void* s1, const void* s2) {
  student_t* student1 = (student_t*) s1;
  student_t* student2 = (student_t*) s2;
  return student1->score < student2->score;
}


int cmpname(const void* s1, const void* s2) {
  student_t* student1 = (student_t*) s1;
  student_t* student2 = (student_t*) s2;
  return strcmp(student1->name, student2->name);
}


void sort_by_name(student_t* students, int size) {
  qsort(students, size, sizeof(student_t), cmpname);
}


void sort_by_score(student_t* students, int size) {
  qsort(students, size, sizeof(student_t), cmpscore);
}


int main() {
  int i, instance = 1, number_of_students;
  student_t students[STUDENTS_SIZE];

  while (scanf("%d\n", &number_of_students) != EOF) {
    i = 0;
    while (i < number_of_students) {
      scanf("%s %d\n", students[i].name, &students[i].score);
      ++i;
    }

    sort_by_name(students, number_of_students);
    sort_by_score(students, number_of_students);

    printf("Instancia %d\n", instance);
    printf("%s\n", students[number_of_students-1].name);
    ++instance;
  }

  return 0;
}