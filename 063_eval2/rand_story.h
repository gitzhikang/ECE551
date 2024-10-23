#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
#include <stdio.h>
#include <stdlib.h>
//any functions you want your main to use

#endif
//struct for read lines
struct lines_tag
{
    char ** lines;
    size_t len;
};

typedef struct lines_tag lines_t;

//read lines from file
lines_t readFile(FILE* f);

//free memory in lines
void freeLines(lines_t lines);

//replace each lines' blanks with "cat"
void replaceEachLine(char** line);

//replace blank with content
int replaceBlank(char** line,int beginIndex,int endIndex, const char * content);

//remove '\n' from a line
void removeNewLine(char * line);


