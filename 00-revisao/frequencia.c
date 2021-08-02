#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 100000
#define PRESENT '1'

int count_present_records(char* records, int len) {
  int count = 0;
  for (int i = 0; i < len; i++) {
    count += (records[i] == PRESENT);
  }
  return count;
}

/*
  1 ≤ N ≤ 10^5
  Para cada elemento Vi, 0 ≤ Vi ≤ 10^6
*/
int main() {
  char records[MAX_RECORDS] = {[0 ... MAX_RECORDS-1] = 0};
  int nrecords, record;

  scanf("%d\n", &nrecords);

  while (nrecords--) {
    scanf("%d\n", &record);
    records[record] = PRESENT;
  }

  printf("%d\n", count_present_records(records, MAX_RECORDS));

  return 0;
}