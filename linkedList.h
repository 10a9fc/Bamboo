#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LINKED_LIST_NODE
{
	void* elem;
	struct LINKED_LIST_NODE* next;
	struct LINKED_LIST_NODE* pre;
}LinkedListNode;

typedef struct LINKED_LIST
{
	int size;
	LinkedListNode* head;
	LinkedListNode* tail;
}LinkedList;


LinkedListNode* Init_LinkedListNode(void* elem);

void Destroy_LinkedListNode(void* node);


LinkedList* Init_LinkedList();

void Destroy_LinkedList(LinkedList* list);

void PushFront_LinkedList(LinkedList* list, void* elem);

void PushBack_LinkedList(LinkedList* list, void* elem);

void PopFront_LinkedList(LinkedList* list);

void PopBack_LinkedList(LinkedList* list);

void* Front_LinkedList(LinkedList* list);

void* Back_LinkedList(LinkedList* list);

void Foreach_LinkedList(LinkedList* list, void(*func)(void*));

#endif // !
