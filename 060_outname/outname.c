#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  size_t len = strlen(inputName);
  char * outName = malloc(sizeof(*outName) * (len + 7));
  strcpy(outName, inputName);
  strcat(outName, ".counts");
  return outName;
}
