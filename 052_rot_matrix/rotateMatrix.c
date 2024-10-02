#include <stdio.h>
#include <stdlib.h>

void roteMatrix(char arr[][10], int size) {
  int leftUprow = 0;
  int leftUpcol = 0;
  int rightDownrow = size - 1;
  int rightDowncol = size - 1;
  while (leftUprow < rightDownrow) {
    for (int i = 0; i < rightDownrow - leftUprow; i++) {
      char temp = arr[leftUprow][leftUpcol + i];
      arr[leftUprow][leftUpcol + i] = arr[rightDownrow - i][leftUpcol];
      arr[rightDownrow - i][leftUpcol] = arr[rightDownrow][rightDowncol - i];
      arr[rightDownrow][rightDowncol - i] = arr[leftUprow + i][rightDowncol];
      arr[leftUprow + i][rightDowncol] = temp;
    }
    leftUprow++;
    leftUpcol++;
    rightDownrow--;
    rightDowncol--;
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Please input one text file\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Can't open file\n");
    exit(EXIT_FAILURE);
  }
  char originMatrix[10][10];
  int row = 0;
  int col = 0;
  int c = 0;
  while ((c = fgetc(f)) != EOF) {
    if (row >= 10) {
      fprintf(stderr, "the length of row exceed the 10!\n");
      exit(EXIT_FAILURE);
    }
    if (c == '\n') {
      if (col < 10) {
        fprintf(stderr, "One row doesn't reache 10 length!\n");
        exit(EXIT_FAILURE);
      }
      row++;
      col = 0;
      continue;
    }
    if (col >= 10) {
      fprintf(stderr, "One row exceed the 10 length!\n");
      exit(EXIT_FAILURE);
    }
    originMatrix[row][col++] = c;
  }

  roteMatrix(originMatrix, 10);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", originMatrix[i][j]);
    }
    printf("\n");
  }
  fclose(f);
}
