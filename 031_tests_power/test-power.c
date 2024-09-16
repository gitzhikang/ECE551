#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);
void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = power(x, y);
  if (ans == expected_ans) {
    return;
  }
  else {
    exit(EXIT_FAILURE);
  }
}

unsigned power_correct(unsigned x, unsigned y) {
  unsigned ans = 1;
  for (int i = 0; i < y; i++) {
    ans *= x;
  }
  return ans;
}

int main(void) {
  run_check(0, 0, 1);
  run_check(0, 1, 0);
  run_check(0, 2, 0);
  run_check(1, 1, 1);
  run_check(1, 2, 1);
  run_check(2, 1, 2);
  run_check(2, 2, 4);
  //run_check(2, 64, power_correct(2, 64));
  //run_check(2, 31, power_correct(2, 31));
  run_check(11, 0, 1);
  //run_check(power_correct(2, 31), 1, power_correct(2, 31));
  //run_check(1, power_correct(2, 31), 1);
  //run_check(0, power_correct(2, 31), 0);
  printf("success!");
  return EXIT_SUCCESS;
}
