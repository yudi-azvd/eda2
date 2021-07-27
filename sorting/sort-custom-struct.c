#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_SIZE 100


typedef struct record_t {
  int number;       // aa
  char string[20];  // bb
} record_t;


void print_records(record_t* records, int size) {
  int i;
  for (i = 0; i < size; ++i)
    // printf("%s %d\n", records[i].string, records[i].number);
    printf("%d %s\n", records[i].number, records[i].string);
}


int cmpint(const void* r1, const void* r2) {
  record_t* record1 = (record_t*) r1;
  record_t* record2 = (record_t*) r2;
  return record1->number - record2->number;
}


int cmpname(const void* r1, const void* r2) {
  record_t* record1 = (record_t*) r1;
  record_t* record2 = (record_t*) r2;
  return strcmp(record1->string, record2->string);
}


void sort_by_name(record_t* records, int size) {
  qsort(records, size, sizeof(record_t), cmpname);
}


void sort_by_score(record_t* records, int size) {
  qsort(records, size, sizeof(record_t), cmpint);
}


void special_sort(record_t* records, int size) {
  sort_by_name(records, size);
  sort_by_score(records, size);
}


int main() {
  int i, instance = 1, number_of_records;
  record_t records[VECTOR_SIZE];

  while (scanf("%d\n", &number_of_records) != EOF) {
    i = 0;
    while (i < number_of_records) {
      scanf("%s %d\n", records[i].string, &records[i].number);
      ++i;
    }

    special_sort(records, number_of_records);

    printf("--- Instancia %d ---\n", instance);
    print_records(records, number_of_records);
    printf("\n");
    ++instance;
  }


  return 0;
}