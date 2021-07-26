#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 1000000
#define ABSENT '\0'
#define PRESENT '1'


int count_present_records(char* records, int len) {
  int count = 0;
  for (int i = 0; i < len; i++) {
    count += (records[i] == PRESENT);
  }
  return count;
}

int main() {
  // char* records = (char*) calloc(MAX_RECORDS, sizeof(char));
  char* records;
  int number_of_records, record;

  scanf("%d\n", &number_of_records);
  records = (char*) calloc(number_of_records, sizeof(char));

  while (number_of_records--) {
    scanf("%d", &record);
    records[record] = PRESENT;
  }

  printf("%d\n", count_present_records(records, MAX_RECORDS));
  free(records);

  return 0;
}