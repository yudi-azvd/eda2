#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 1000000
#define PRESENT '1'
#define ABSENT 0

/*
  1 ≤ N ≤ 10^5
  Para cada elemento Vi, 0 ≤ Vi ≤ 10^6
*/
int main() {
  char records[MAX_RECORDS] = {[0 ... MAX_RECORDS-1] = ABSENT};
  int nrecords, record, present_records = 0;

  scanf("%d\n", &nrecords);

  while (nrecords--) {
    scanf("%d\n", &record);

    if (records[record] == ABSENT) {
      records[record] = PRESENT;
      ++present_records;
    }
  }

  printf("%d\n", present_records);

  return 0;
}