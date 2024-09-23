#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);
void checkAns(int * array, size_t n, size_t t_ans) {
  size_t ans = maxSeq(array, n);

  if (ans == t_ans) {
    return;
  }
  else {
    exit(EXIT_FAILURE);
  }
}
int main(void) {
  int myArray[10] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  checkAns(myArray, 10, 4);
  int * myArray1 = NULL;
  checkAns(myArray1, 0, 0);
  //checkAns(myArray1, 10, 0);
  int myArray2[] = {1, 2, 3, 4, 5, 6, 7};
  checkAns(myArray2, 7, 7);
  int myArray3[] = {7, 6, 5, 4, 3, 2, 1};
  checkAns(myArray3, 7, 1);
  int myArray4[] = {9, 7, 10, 10, 12, 14, 1, 2};
  checkAns(myArray4, 8, 3);
  int myArray5[] = {-1, -2, -3, -4, 0, 1, 2, 3, 4};
  checkAns(myArray5, 9, 6);
  int myArray6[4] = {0, 0, 0, 0};
  checkAns(myArray6, 4, 1);

  return EXIT_SUCCESS;
}
