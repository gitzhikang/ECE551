#include "rand_story.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char** argv){
    bool skipUsed = false;
    if(argc == 4){
        if(strcmp(argv[1],"-n")!=0){
            fprintf(stderr,"-n filename filename!\n");
            exit(EXIT_FAILURE);
        }
        skipUsed = true;
    }
    if(argc < 3 || argc > 4){
        fprintf(stderr,"please input fileName!\n");
        exit(EXIT_FAILURE);
    }
    const char * fileNameCat;
    const char* fileNameStory;
    if(argc == 3){
        fileNameCat = argv[1];
        fileNameStory = argv[2];
    }else if(argc == 4){
        fileNameCat = argv[2];
        fileNameStory = argv[3];
    }
    
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
         replaceEachLineWithBackWardNoRepeatForAll(&(linesStory.lines[i]),&array,history,true,skipUsed);
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