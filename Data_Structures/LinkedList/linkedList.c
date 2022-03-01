#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

LinkedList* linkedListCreate()
{
    LinkedList* list = malloc(sizeof(LinkedList));
    *list = (LinkedList) {
        NULL, NULL
    };
    return list;
}

void linkedListDestroy(LinkedList* list)
{
    if (list == NULL) return;
    linkedListDestroy(list->next);
    free(list);
}

void linkedListAdd(LinkedList* list, void* object)
{
    LinkedList* node = list;
    for(;node->next!=NULL;node=node->next);
    LinkedList* newItem = linkedListCreate();
    newItem->object = object;
    node->next = newItem;
}


void* linkedListRemove(LinkedList* list, unsigned int n)
{
    LinkedList* lastNode = list;
    LinkedList* node = list->next;
    for(unsigned int i=0;i<n;i++)
    {
        if (node == NULL || node->next == NULL) return NULL;
        lastNode = node;
        node=node->next;
    }
    if (node == NULL) return NULL;

    lastNode->next = node->next;
    void* object = node->object;
    free(node);
    return object;
}

void* linkedListGet(LinkedList* list, unsigned int n)
{
    LinkedList* node = list->next;
    for(unsigned int i=0;i<n;i++)
    {
        if (node == NULL || node->next == NULL) return NULL;
        node=node->next;
    }
    return node->object;

}

void linkedListForEach(LinkedList* list, void (*f)(void*))
{
    if (list == NULL) return;
    f(list->object);
    linkedListForEach(list->next, f);
}

bool linkedListContains(LinkedList* list, bool (*compare)(void*))
{
    if (list == NULL) return false;
    return compare(list->object) || linkedListContains(list->next, compare);
}

void* linkedListGetByAttribut(LinkedList* list, bool (*compare)(void*))
{
    if (list == NULL) return NULL;
    return compare(list->object) ? list->object : linkedListGetByAttribut(list->next, compare);
}


void freeObjects(void* pointer)
{
    if (pointer == NULL) return;
    free(pointer);
}

void linkedListFreeObjects(LinkedList* list)
{
    linkedListForEach(list, freeObjects);
}
