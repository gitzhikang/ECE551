#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int getLargestFrequence(int * alphaCount, int size, FILE * file) {
  int c;
  while ((c = fgetc(file)) != EOF) {
    if (isalpha(c)) {
      alphaCount[c - 'a']++;
    }
  }
  int max = 0;
  int ans = -1;
  for (int i = 0; i < size; i++) {
    if (alphaCount[i] > max) {
      max = alphaCount[i];
      ans = i;
    }
  }
  return ans;
}

int decipher(int mostchar) {
  int ans = 0;
  if (mostchar >= 4) {
    ans = mostchar - 4;
  }
  else {
    ans = 26 + mostchar - 4;
  }
  return ans;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt inputfilename");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Open File Fail");
    return EXIT_FAILURE;
  }
  int alpha[26] = {0};
  int mostchar = getLargestFrequence(alpha, 26, f);
  int key = decipher(mostchar);
  fclose(f);
  printf("%d\n", key);
  return 1;
}
