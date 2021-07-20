#include <stdio.h>

#define MAX_RECORDS 1000000
#define ABSENT '0'
#define PRESENT '1'


void reset_records(char* records, int len) {
  for (int i = 0; i < len; i++) {
    records[i] = ABSENT;
  }
}

int count_present_records(char* records, int len) {
  int count = 0;
  for (int i = 0; i < len; i++) {
    count += (records[i] == PRESENT);
  }
  return count;
}

int main() {
  char records[MAX_RECORDS];
  int number_of_records, record;

  scanf("%d\n", &number_of_records);
  reset_records(records, MAX_RECORDS);

  while (number_of_records--) {
    scanf("%d", &record);
    records[record] = PRESENT;
  }

  printf("%d\n", count_present_records(records, MAX_RECORDS));

  return 0;
}