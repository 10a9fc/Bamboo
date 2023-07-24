#include "dictionary.h"

DictionaryNode* Init_DictionaryNode(char* key, void* value)
{
    DictionaryNode* ret = malloc(sizeof(DictionaryNode));
    int len = strlen(key);

    ret->key = malloc(len + 1);
    memcpy(ret->key, key, len);
    ret->key[len] = '\0';

    ret->value = value;

    return ret;
}

void Destroy_DictionaryNode(void* node)
{
    DictionaryNode* v = node;
    free(v->key);

    free(v);
}


Dictionary* Init_Dictionary()
{
    Dictionary* ret = malloc(sizeof(Dictionary));
    ret->list = Init_List(10);

    return ret;
}

void Destroy_Dictionary(Dictionary* dic)
{
    Foreach_List(dic->list, Destroy_DictionaryNode);

    Destroy_List(dic->list);
    free(dic);
}

void Push_Dictionary(Dictionary* dic, char* key, void* value)
{
    Push_List(dic->list, Init_DictionaryNode(key, value));
}

void Pop_Dictionary(Dictionary* dic)
{
    Destroy_DictionaryNode(At_List(dic->list, Size_List(dic->list) - 1));
    Pop_List(dic->list);
}

void Set_Dictionary(Dictionary* dic, char* key, void* value)
{
    for (int i = 0; i < Size_List(dic->list); ++i)
    {
        DictionaryNode* node = At_List(dic->list, i);

        if (strcmp(node->key, key) == 0)
        {
            node->value = value;
            return;
        }
    }
}

void* Find_Dictionary(Dictionary* dic, char* key)
{
    for (int i = 0; i < Size_List(dic->list); ++i)
    {
        DictionaryNode* node = At_List(dic->list, i);

        if (strcmp(node->key, key) == 0)
        {
            return node->value;
        }
    }
    return NULL;
}

void Foreach_Dictionary(Dictionary* dic, void (*func)(void*))
{
    for (int i = 0; i < dic->list->size; ++i)
    {
        func(((DictionaryNode*)At_List(dic->list, i))->value);
    }
}

