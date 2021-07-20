#include <stdio.h>
#include <string.h>

#define LINE_LENGTH 1000
#define MAX_LINES 1000

void move_cursor_down(char text[MAX_LINES][LINE_LENGTH], int* row, int* col);
void move_cursor_up  (char text[MAX_LINES][LINE_LENGTH], int* row, int* col);
void adjust_cursor_if_out_of_bounds(char text[MAX_LINES][LINE_LENGTH], int* row, int* col, int* last_col);


int main() {
  int number_of_lines, row, col, last_col;
  int line_index = 0, i;
  char command = '\0';
  char text[MAX_LINES][LINE_LENGTH];

  // o scanf deve consumir o '\n' também
  scanf("%d\n", &number_of_lines);
  i = number_of_lines;

  while (i--) {
    fgets(text[line_index], LINE_LENGTH, stdin);
    text[line_index][strlen(text[line_index])-1] = '\0'; // remover o '\n'
    line_index++;
  }

  scanf("%d %d\n", &row, &col);
  // printf("%d %d\n", row, col);
  row--;
  col--;

  while (scanf("%c\n", &command) != EOF) {
    if (command == 'j')
      move_cursor_down(text, &row, &col);
    else if (command == 'k')
      move_cursor_up(text, &row, &col);
    
    adjust_cursor_if_out_of_bounds(text, &row, &col, &last_col);

    printf("%d %d %c\n", row+1, col+1, text[row][col]);
  }

  // for (i = 0; i < number_of_lines; i++) {
  //   printf("%s\n", text[i]);
  // }

  return 0;
}


void move_cursor_up(char text[MAX_LINES][LINE_LENGTH], int* row, int* col) {
  if (*row - 1 >= 0)
    *row = *row - 1;
}

void move_cursor_down(char text[MAX_LINES][LINE_LENGTH], int* row, int* col) {
  if (*row + 1 < MAX_LINES)
    *row = *row + 1;
}

void adjust_cursor_if_out_of_bounds(char text[MAX_LINES][LINE_LENGTH], int* row, int* col, int* last_col) {
  int line_length = strlen(text[*row]);
  // -2 por causa do '\n'
  if (*col > line_length-1) {
    *last_col = *col;
    *col = *last_col > line_length-1 ? line_length-1:*last_col;
  }
  else {
    *col = *last_col;
  }
}
