#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// any functions you want your main to use

#endif
// struct for read lines
struct lines_tag
{
    char **lines;
    size_t len;
};

typedef struct lines_tag lines_t;

// struct for choose history
struct history_tag
{
    const char **words;
    size_t n_words;
};

typedef struct history_tag history_t;

// seperate file according to the line, read each line into lines
lines_t readFile(FILE *f);

// free memory in lines
void freeLines(lines_t lines);

// replace blank with content
int replaceBlank(char **line, int beginIndex, int endIndex, const char *content);

// remove '\n' from a line
void removeNewLine(char *line);

// get category from name
category_t *getCategoryByName(char *name, catarray_t array);

// free catarray_t array
void freeCatarray(catarray_t array);

// save one category content to corresponding category in array
void saveCatToArray(catarray_t *array, char *catName, char *catContent);

// save all category content from lines to corresponding category in array
void saveAllCatToArray(lines_t lines, catarray_t *array);

// According to the backIndex(start from 1), get history content
const char *getContentFromHistory(history_t history, int backIndex);

// judge if str is a backward reference
bool isInteger(char *str);

// remove the corresponding content of category from catarray_t
void removeContent(const char *content, char *category, catarray_t *cats);


// replace each lines' blanks with random cat from cats and allow backward reference and no repeat, then print new line
//  if cats == null, replace blank with cat
void replaceEachLineWithBackWardNoRepeatForAll(char **line, catarray_t *cats, history_t *history, bool backward, bool noRepeat);
