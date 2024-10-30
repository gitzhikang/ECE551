#include "rand_story.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char** argv){
    if(argc!=3){
        fprintf(stderr,"please input fileName!\n");
        exit(EXIT_FAILURE);
    }
    const char * fileNameCat = argv[1];
    const char* fileNameStory = argv[2];
    FILE* fCat = fopen(fileNameCat,"r");
    if(fCat==NULL){
        fprintf(stderr,"file doesn't exist!\n");
        exit(EXIT_FAILURE);
    }
    FILE* fStory = fopen(fileNameStory,"r");
    if(fStory==NULL){
        fprintf(stderr,"file doesn't exist!\n");
        exit(EXIT_FAILURE);
    }
    // save cat into array
    lines_t linesCat = readFile(fCat);
    catarray_t array;
    array.n = 0;
    array.arr = NULL;
    saveAllCatToArray(linesCat,&array);
    
    //replace blank according to the array
    lines_t linesStory = readFile(fStory);
    history_t* history = malloc(sizeof(*history));
    history->n_words = 0;
    history->words=NULL;
    for(size_t i = 0 ;i<linesStory.len;i++){
        replaceEachLineWithBackWard(&(linesStory.lines[i]),&array,history);
        replaceEachLineWithBackWardNoRepeatForAll(&(linesStory.lines[i]),&array,history,true,false);
    }
    //free memory
    freeLines(linesCat);
    freeCatarray(array);
    fclose(fCat);
    free(history->words);
    free(history);
    freeLines(linesStory);
    fclose(fStory);
}