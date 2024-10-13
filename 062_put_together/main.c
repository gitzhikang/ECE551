#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  char * curr = NULL;
  counts_t * ans = createCounts();
  size_t lineLen = 0;
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "can't open key file");
    exit(EXIT_FAILURE);
  }
  while (getline(&curr, &lineLen, f) >= 0) {
    int index = 0;
    while (curr[index] != '\n') {
      index++;
    }
    curr[index] = '\0';
    char * getVal = lookupValue(kvPairs, curr);
    addCount(ans, getVal);
  }
  free(curr);
  fclose(f);
  return ans;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc <= 2) {
    fprintf(stderr, "Wrong argc numbers!");
    exit(EXIT_FAILURE);
  }
  const char * kvName = argv[1];
  kvarray_t * kv = readKVs(kvName);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      fprintf(stderr, "can't open output file");
      exit(EXIT_FAILURE);
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    fclose(f);
    //free the memory for outName and c
    freeCounts(c);
    free(outName);
  }

  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
