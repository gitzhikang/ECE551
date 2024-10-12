#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(counts_t));
  counts->len = 0;
  counts->list = NULL;
  counts->unknown_count = -1;
  return counts;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    if (c->unknown_count == -1) {
      c->unknown_count = 1;
    }
    else {
      c->unknown_count++;
    }
    return;
  }
  if (c->list == NULL) {
    c->list = malloc(sizeof(one_count_t));
    c->list[0].str = name;
    c->list[0].count = 1;
    c->len = 1;
    return;
  }
  for (int i = 0; i < c->len; i++) {
    if (strcmp(c->list[i].str, name) == 0) {
      c->list[i].count++;
      return;
    }
  }
  c->list = realloc(c->list, (c->len + 1) * sizeof(one_count_t));
  c->len++;
  c->list[c->len - 1].str = name;
  c->list[c->len - 1].count = 1;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->len; i++) {
    fprintf(outFile, "%s: %d\n", c->list[i].str, c->list[i].count);
  }
  if (c->unknown_count != -1)
    fprintf(outFile, "<unknown>: %d\n", c->unknown_count);
}

void freeCounts(counts_t * c) {
  //WRITE ME
  /*for (int i = 0; i < c->len; i++) {
    free(c->list[i].str);
    }*/
  free(c->list);
  free(c);
}
