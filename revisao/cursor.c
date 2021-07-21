#include <stdio.h>
#include <string.h>

#define LINE_LENGTH 1000
#define MAX_LINES 1000

void move_cursor_down(char text[MAX_LINES][LINE_LENGTH], int* row, const int number_of_lines);
void move_cursor_up  (char text[MAX_LINES][LINE_LENGTH], int* row);
void adjust_cursor_horizontally(char text[MAX_LINES][LINE_LENGTH], int* row, int* col, int* last_max_col);


int main() {
  int number_of_lines, row, col, last_max_col;
  int line_index = 0, i;
  char command = '\0';
  char text[MAX_LINES][LINE_LENGTH];

  scanf("%d\n", &number_of_lines);
  i = number_of_lines;

  while (i--) {
    fgets(text[line_index], LINE_LENGTH, stdin);
    text[line_index][strlen(text[line_index])-1] = '\0';
    line_index++;
  }

  scanf("%d %d\n", &row, &col);
  row--;
  col--;
  last_max_col = col;

  while (scanf("%c\n", &command) != EOF) {
    if (command == 'j')
      move_cursor_down(text, &row, number_of_lines);
    else if (command == 'k')
      move_cursor_up(text, &row);
    
    adjust_cursor_horizontally(text, &row, &col, &last_max_col);

    printf("%d %d %c\n", row+1, col+1, text[row][col]);
  }

  return 0;
}


void move_cursor_up(char text[MAX_LINES][LINE_LENGTH], int* row) {
  if (*row - 1 >= 0)
    *row = *row - 1;
}

void move_cursor_down(char text[MAX_LINES][LINE_LENGTH], int* row, const int number_of_lines) {
  if (*row + 1 < number_of_lines)
    *row = *row + 1;
}

void adjust_cursor_horizontally(
  char text[MAX_LINES][LINE_LENGTH],
  int* row,
  int* col,
  int* last_max_col
) {
  int line_length = strlen(text[*row]);
  if (*col > line_length-1) {
    *last_max_col = *col;
    *col = line_length-1;
  }
  else {
    *col = *last_max_col > line_length-1 
      ? line_length-1 < 0 
        ? 0
        : line_length-1
      : *last_max_col;
  }
}
