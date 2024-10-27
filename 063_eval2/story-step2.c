#include "rand_story.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char** argv){
    if(argc!=2){
        fprintf(stderr,"please input fileName!\n");
        exit(EXIT_FAILURE);
    }
    const char * fileName = argv[1];
    FILE* f = fopen(fileName,"r");
    if(f==NULL){
        fprintf(stderr,"file doesn't exist!\n");
        exit(EXIT_FAILURE);
    }
    //read to lines
    lines_t lines = readFile(f);
    //initial ans
    catarray_t array;
    array.n = 0;
    array.arr = NULL;
    //save cat to ans
    saveAllCatToArray(lines,&array);
    printWords(&array);
    //free memory
    freeLines(lines);
    freeCatarray(array);
    fclose(f);
}