#include <stdio.h>

int main() {
  char answer[4];
  int triages_count = 0, question_counter = 0, yes_count = 0;
  int had_triage_for_this_round = 0;
  const int YES_THRESHOLD = 2, QUESTION_LIMIT = 10;

  while (scanf("%s", answer) != EOF) {
    ++question_counter;

    if (answer[0] == 's') {
      ++yes_count;

      if (yes_count >= YES_THRESHOLD && !had_triage_for_this_round) {
        ++triages_count;
        had_triage_for_this_round = 1;
      }
    }

    if (question_counter == QUESTION_LIMIT) {
      question_counter = 0;
      yes_count = 0;
      had_triage_for_this_round = 0;
    }
  }
  
  printf("%d\n", triages_count);
  return 0;
}