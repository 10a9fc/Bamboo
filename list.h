#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LIST
{
	int size;
	int capacity;
	void** head;
}List;

List* Init_List(int capacity);

void Destroy_List(List* list);

void Push_List(List* list, void* elem);

void Pop_List(List* list);

void* At_List(List* list, int index);

void Foreach_List(List* list, void(*func)(void*));

int Size_List(List* list);

#endif // !LIST_H
