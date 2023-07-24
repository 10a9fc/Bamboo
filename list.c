#include "list.h"

List* Init_List(int capacity)
{
    List* ret = malloc(sizeof(List));
    ret->size = 0;
    ret->capacity = capacity;
    ret->head = malloc(sizeof(void*) * capacity);
    return ret;
}

void Destroy_List(List* list)
{
    free(list->head);

    free(list);
}

void Push_List(List* list, void* elem)
{
    if (list->size == list->capacity)
    {
        void** newHead = malloc(sizeof(void*) * list->capacity * 2);
        memcpy(newHead, list->head, sizeof(void*) * list->size);
        free(list->head);
        list->head = newHead;
        list->capacity *= 2;
    }

    list->head[list->size++] = elem;
}

void Pop_List(List* list)
{
    list->head[--list->size] = NULL;
}

void* At_List(List* list, int index)
{
    return list->head[index];
}

void Foreach_List(List* list, void(*func)(void*))
{
    for (int i = 0; i < list->size; ++i)
    {
        func(list->head[i]);
    }
}

int Size_List(List* list)
{
    return list->size;
}

