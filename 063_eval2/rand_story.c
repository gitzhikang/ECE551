#include "rand_story.h"
#include "string.h"
#include <stdio.h>
lines_t readFile(FILE* f){
    char ** lines = NULL;
    char * curr = NULL;
    size_t linecaps = 0;
    size_t index = 0;
    while (getline(&curr,&linecaps,f)>=0)
    {
        lines = realloc(lines,(index+1)*sizeof(*lines));
        removeNewLine(curr);
        lines[index] = curr;
        curr = NULL;
        index++;
    }
    free(curr);
    lines_t ans;
    ans.len = index;
    ans.lines = lines;
    return ans;
}

void freeLines(lines_t lines){
    for(size_t i = 0;i<lines.len;i++){
        free(lines.lines[i]);
    }
    free(lines.lines);
}

//replace blank with content(function will return a new line)
int replaceBlank(char** line,int beginIndex,int endIndex, const char * content){
    int oldLineLen = strlen(*line);
    int contentLen = strlen(content);
    int newLineLen = oldLineLen - (endIndex-beginIndex+1) + contentLen;
    char* newLine = malloc(sizeof(char)*(newLineLen+1));
    int newLineIndex = 0;
    int returnIndex = 0;
    while(newLineIndex<beginIndex){
         newLine[newLineIndex] = (*line)[newLineIndex];
         newLineIndex++;
    }
    for(int i =0 ;i<contentLen;i++){
        newLine[newLineIndex++] = content[i];
    }
    returnIndex = newLineIndex;
    for(int i = endIndex+1;i<oldLineLen;i++){
        newLine[newLineIndex++] = (*line)[i];
    }
    free(*line);
    newLine[newLineIndex] = '\0';
    *line = newLine;
    return returnIndex;
}

//replace each lines' blanks with "cat"
void replaceEachLine(char** line){
    int index = 0;
    int beginBlank = -1;
    int endBlank = -1;
    char * category = NULL;
    while((*line)[index]!='\0'){
        if((*line)[index] == '_'){
            if(beginBlank == -1 && endBlank == -1){
                beginBlank = index;
                index++;
            }else if(endBlank == -1){
                endBlank = index;
                category = malloc((endBlank-beginBlank)*sizeof(char));
                strncpy(category,*line+beginBlank+1,endBlank-beginBlank-1);
                category[endBlank-beginBlank-1] = '\0';
                const char* content = chooseWord(category,NULL);
                index = replaceBlank(line,beginBlank,endBlank,content);
                beginBlank = -1;
                endBlank = -1;
                free(category);
            }
        }else{
            index++;
        }
    }
    if(beginBlank != -1 && endBlank == -1){
        fprintf(stderr,"%s does not has a pair of _",*line);
    }
    printf("%s\n",*line);
}

//remove '\n' from a line
void removeNewLine(char * line){
    int index = 0;
    while(line[index]!='\0'){
        if(line[index] == '\n'){
            line[index] = '\0';
            return;
        }
        index++;
    }
}
