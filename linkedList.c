#include "linkedList.h"

LinkedListNode* Init_LinkedListNode(void* elem)
{
    LinkedListNode* ret = malloc(sizeof(LinkedListNode));
    ret->elem = elem;
    ret->next = NULL;
    ret->pre = NULL;
    return ret;
}

void Destroy_LinkedListNode(void* node)
{
    LinkedListNode* v = node;
    //v->elem = NULL;

    free(v);
}


LinkedList* Init_LinkedList()
{
    LinkedList* ret = malloc(sizeof(LinkedList));
    ret->size = 0;
    ret->head = Init_LinkedListNode(NULL);
    ret->tail = ret->head;

    return ret;
}

void Destroy_LinkedList(LinkedList* list)
{
    LinkedListNode* cur = list->head;
    LinkedListNode* pre = NULL;
    while (cur != NULL)
    {
        pre = cur;
        cur = cur->next;
        Destroy_LinkedListNode(pre);
    }

    free(list);
}

void PushFront_LinkedList(LinkedList* list, void* elem)
{
    if (list->size == 0)
    {
        list->head->elem = elem;
        list->size += 1;
        return;
    }

    LinkedListNode* newNode = Init_LinkedListNode(elem);
    newNode->next = list->head;
    list->head->pre = newNode;
    list->head = newNode;
    list->size += 1;
}

void PushBack_LinkedList(LinkedList* list, void* elem)
{
    if (list->size == 0)
    {
        list->tail->elem = elem;
        list->size += 1;
        return;
    }

    LinkedListNode* newNode = Init_LinkedListNode(elem);
    newNode->pre = list->tail;
    list->tail->next = newNode;
    list->tail = newNode;
    list->size += 1;
}

void PopFront_LinkedList(LinkedList* list)
{
    if (list->size == 1)
    {
        list->head->elem = NULL;
        list->size -= 1;
        return;
    }

    LinkedListNode* newHead = list->head->next;
    Destroy_LinkedListNode(list->head);
    list->head = newHead;
    list->size -= 1;
}

void PopBack_LinkedList(LinkedList* list)
{
    if (list->size == 1)
    {
        list->tail->elem = NULL;
        list->size -= 1;
    }

    LinkedListNode* newHead = list->tail->pre;
    Destroy_LinkedListNode(list->tail);
    list->tail = newHead;
    list->size -= 1;
}

void* Front_LinkedList(LinkedList* list)
{
    return list->head->elem;
}

void* Back_LinkedList(LinkedList* list)
{
    return list->tail->elem;
}

void Foreach_LinkedList(LinkedList* list, void(*func)(void*))
{
    if (list->size == 0)
    {
        return;
    }

    LinkedListNode* cur = list->head;

    while (cur != NULL)
    {
        func(cur->elem);
        cur = cur->next;
    }
}


