#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "list.h"

typedef struct DICTIONARY_NODE
{
	char* key;
	void* value;
}DictionaryNode;

typedef struct DICTIONARY
{
	List* list;
}Dictionary;

DictionaryNode* Init_DictionaryNode(char* key, void* value);

void Destroy_DictionaryNode(void* node);


Dictionary* Init_Dictionary();

void Destroy_Dictionary(Dictionary* dic);

void Push_Dictionary(Dictionary* dic, char* key, void* value);

void Pop_Dictionary(Dictionary* dic);

void Set_Dictionary(Dictionary* dic, char* key, void* value);

void* Find_Dictionary(Dictionary* dic, char* key);

void Foreach_Dictionary(Dictionary* dic, void (*func)(void*));

#endif

