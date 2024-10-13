#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "%s can't open!", fname);
    exit(EXIT_FAILURE);
  }
  char ** lines = NULL;
  char * curr = NULL;
  size_t linecap;
  size_t i = 0;
  while (getline(&curr, &linecap, f) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  kvarray_t * ans = malloc(sizeof(kvarray_t));
  ans->length = i;
  ans->list = malloc(sizeof(kvpair_t) * i);
  const char * seperator = "=";
  for (size_t j = 0; j < i; j++) {
    char * pre = lines[j];
    char * token = strsep(&lines[j], seperator);
    ans->list[j].key = token;
    size_t len = strlen(lines[j]);
    if (len == 0) {
      fprintf(stderr, "Wrong format");
      exit(EXIT_FAILURE);
    }
    if (len > 0 && lines[j][len - 1] == '\n') {
      lines[j][len - 1] = '\0';
    }
    ans->list[j].val = lines[j];
    lines[j] = pre;
  }
  free(lines);
  fclose(f);
  return ans;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    free(pairs->list[i].key);
  }
  free(pairs->list);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->list[i].key, pairs->list[i].val);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    if (strcmp(pairs->list[i].key, key) == 0) {
      return pairs->list[i].val;
    }
  }
  return NULL;
}
