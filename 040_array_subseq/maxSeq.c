#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n) {
  if (array == NULL) {
    return 0;
  }
  int pre = INT_MIN;
  size_t currentCount = 0;
  size_t maxCount = 0;
  for (int i = 0; i < n; i++) {
    if (array[i] > pre) {
      currentCount++;
      pre = array[i];
    }
    else {
      if (currentCount > maxCount) {
        maxCount = currentCount;
      }
      pre = array[i];
      currentCount = 1;
    }
  }
  if (currentCount > maxCount) {
    return currentCount;
  }
  return maxCount;
}
