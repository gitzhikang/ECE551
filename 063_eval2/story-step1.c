#include "rand_story.h"
#include <stdio.h>
#include <stdlib.h>
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
    //read file to lines
    lines_t lines = readFile(f);
    //replace each block in each line
    for(size_t i = 0 ;i<lines.len;i++){
        replaceEachLine(&(lines.lines[i]),NULL);
    }
    //free memory
    freeLines(lines);
    fclose(f);
}