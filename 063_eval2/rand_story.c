#include "rand_story.h"
#include "string.h"
#include <stdio.h>

//seperate file according to the line, read each line into lines
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

//free memory in lines
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

//replace each lines' blanks with random "cat" from cats
// if cats == null, replace blank with cat
void replaceEachLine(char** line,catarray_t * cats){
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
                const char* content = chooseWord(category,cats);
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

//replace each lines' blanks with random "cat" from cats and allow backward reference
// if cats == null, replace blank with cat
void replaceEachLineWithBackWard(char** line,catarray_t * cats,history_t* history){
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
                const char* content;
                //judge the whether use backward reference
                if(isInteger(category)){
                    int backIndex = atoi(category);
                    if(backIndex > history->n_words){
                        fprintf(stderr,"reference out of boundary!");
                        exit(EXIT_FAILURE);
                    }
                    content = getContentFromHistory(*history,backIndex);
                }else{
                    content = chooseWord(category,cats);
                }
                //save content to history
                history->words = realloc(history->words,sizeof(char*)*(history->n_words+1));
                history->words[history->n_words] = content;
                history->n_words++;

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

//replace each lines' blanks with random "cat" from cats and allow backward reference and no repeat
// if cats == null, replace blank with cat
void replaceEachLineWithBackWardNoRepeat(char** line,catarray_t * cats,history_t* history){
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
                const char* content;
                //judge the whether use backward reference
                if(isInteger(category)){
                    int backIndex = atoi(category);
                    if(backIndex > history->n_words){
                        fprintf(stderr,"reference out of boundary!");
                        exit(EXIT_FAILURE);
                    }
                    content = getContentFromHistory(*history,backIndex);
                }else{
                    //if choose from cats, should remove the chosen content in cats
                    content = chooseWord(category,cats);   
                    removeContent(content,category,cats);
                }
                //save content to history
                history->words = realloc(history->words,sizeof(char*)*(history->n_words+1));
                history->words[history->n_words] = content;
                history->n_words++;

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
//remove the corresponding content of category from catarray_t
void removeContent(const char * content,char * category,catarray_t* cats){

    for(int i = 0;i<cats->n;i++){
        if(strcmp(cats->arr[i].name,category) == 0){
            for(int j = 0;j<cats->arr[i].n_words;j++){
                if(strcmp(cats->arr[i].words[j],content)==0){
                    int index = j+1;
                    while(index < cats->arr[i].n_words){
                        cats->arr[i].words[index-1] =  cats->arr[i].words[index];
                        index++;
                    }
                    cats->arr[i].n_words--;
                    return;
                }
            }
        }
    }

}



// According to the backIndex(start from 1), get history content
const char* getContentFromHistory(history_t history,int backIndex){
    int len = history.n_words;
    return history.words[len-backIndex];
}

//judge if str is a backward reference
bool isInteger(char * str){
    int index = 0;
    int hasNoZero = false;
    while(str[index]!='\0'){
        if(str[index]>'9' || str[index]<'0'){
            return false;
        }
        if(str[index]<='9' && str[index]>='1'){
            hasNoZero = true;
        }
        index++;
    }
    return hasNoZero;
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

// get category from name
category_t * getCategoryByName(char * name,catarray_t array){
    if(array.n == 0) return NULL;
    for(int i =0 ;i<array.n;i++){
        if(strcmp(array.arr[i].name,name)==0){
            return &(array.arr[i]);
        }
    }
    return NULL;
}

// free catarray_t array
void freeCatarray(catarray_t array){
    for(size_t i = 0;i<array.n;i++){
        free(array.arr[i].words);
    }
    free(array.arr);
}

// save one category content to corresponding category in array
void saveCatToArray(catarray_t* array,char * catName,char * catContent){
    //don't have catName before
    int n = array->n;
     //find category according to categoryName, add catContent
    category_t * catGroup = getCategoryByName(catName,*array);
    if(catGroup == NULL){
        (*array).arr = realloc((*array).arr,(n+1)*sizeof(category_t));
        (*array).arr[n].name = catName;
        (*array).arr[n].n_words = 1;
        (*array).arr[n].words = malloc(sizeof(char*)*1);
        (*array).arr[n].words[0] = catContent;
        (*array).n++;
        n++;
    }else{//has catName before
        int len = (*catGroup).n_words;
        (*catGroup).words = realloc((*catGroup).words,sizeof(char*)*(len+1));
        (*catGroup).words[len] = catContent;
        (*catGroup).n_words++;
    }
}

// save all category content from lines to corresponding category in array
void saveAllCatToArray(lines_t lines,catarray_t* array){
    char * catName;
    char * catContent;
    char* pre;
    for(size_t i = 0 ;i<lines.len;i++){
        //get CatName
        pre = lines.lines[i];
        catName = strsep(&(lines.lines[i]),":");
        if(lines.lines[i] == NULL){
            fprintf(stderr,"No : find!");
            exit(EXIT_FAILURE);
        }
        catContent = lines.lines[i];
        
        lines.lines[i] = pre;
        saveCatToArray(array,catName,catContent);
    }
}
