#ifndef __TODOLIST_H
#define __TODOLIST_H

#include "dynamicArray.h"
#include "type.h"
#include <stdio.h>

Task* createTask (int priority, char *desc);

void saveList(DynArr *heap, FILE *filePtr);

void loadList(DynArr *heap, FILE *filePtr);

void printList(DynArr *heap);

void deleteList(DynArr *heap);

#endif
