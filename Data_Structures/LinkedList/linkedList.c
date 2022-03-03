#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

LinkedList* linkedListCreate()
{
    LinkedList* list = malloc(sizeof(LinkedList));
    return list;
}

llNode* llNodeCreate() {
    llNode* node = malloc(sizeof(llNode));
    node->next = NULL;
    node->object = NULL;
    return node;
}

void linkedListDestroyNode(llNode* node);
void linkedListDestroy(LinkedList* list)
{
    if (list == NULL) return;
    linkedListDestroyNode(list->node);
    free(list);
}

void linkedListDestroyNode(llNode* node)
{
    if (node == NULL) return;
    linkedListDestroyNode(node->next);
    free(node);
}


int linkedListAdd(LinkedList* list, void* object)
{
    llNode* newNode = llNodeCreate();
    newNode->object = object;
    llNode* node = list->node;
    if(node == NULL) {
        list->node = newNode;
        return 0;
    }

    int i;
    for(i=1;node->next != NULL;node=node->next, i++);

    //if (node->object == NULL) {
    //    node->object = object;
    //} else {
    //    LinkedList* newItem = linkedListCreate();
    //    newItem->object = object;
    //    node->next = newItem;
    //    i++;
    //}
    node->next = newNode;
    return i;
}


void* linkedListRemove(LinkedList* list, unsigned int n)
{
    if (list->node == NULL) return NULL;

    llNode* node = list->node;

    if (n==0)
    {
        void* object = node->object;
        list->node = node->next;
        free(node);
        return object;
    }

    llNode* lastNode = NULL;

    for(unsigned int i=0;i<n;i++)
    {
        if (node == NULL || node->next == NULL) return NULL;
        lastNode = node;
        node=node->next;
    }
    lastNode->next = node->next;
    void* object = node->object;
    free(node);
    return object;

    //if (linkedListEmpty(list)) return NULL;
    ////1 Element
    //if (n == 0) {
    //    void* object = list->object;
    //    if(list->next == NULL) {
    //        list->object = NULL;
    //    } else {
    //        list->next = list->next->next;
    //        list->object = list->next->object;
    //    }
    //    return object;
//
    //}
//
    //LinkedList* lastNode = NULL;
    //LinkedList* node = list;
    //for(unsigned int i=0;i<n;i++)
    //{
    //    if (node == NULL || node->next == NULL) return NULL;
    //    lastNode = node;
    //    node=node->next;
    //}
    //lastNode->next = node->next;
    //void* object = node->object;
    //free(node);
    //return object;
}

void* linkedListGet(LinkedList* list, unsigned int n)
{
    llNode* node = list->node;
    for(unsigned int i=0;i<n;i++)
    {
        if (node == NULL || node->next == NULL) return NULL;
        node=node->next;
    }
    return node->object;

}

void linkedListForEach(LinkedList* list, void (*f)(void*))
{
    llNode* node = list->node;
    while (node!=NULL)
    {
        if(node->object!=NULL) f(node->object);
        node = node->next;
    }
}

bool llNodeContains(llNode* node, bool (*predicate)(void*))
{
    if (node == NULL) return false;
    bool isTrue = node->object == NULL ? false : predicate(node->object);
    return isTrue || llNodeContains(node->next, predicate);
}

bool linkedListContains(LinkedList* list, bool (*predicate)(void*))
{
    return llNodeContains(list->node, predicate);   
}


void* llNodeGetByAttribute(llNode* node, bool (*prediacte)(void*))
{
    if (node == NULL) return NULL;
    bool isTrue = (node->object == NULL) ? false : prediacte(node->object);
    return isTrue ? node->object : llNodeGetByAttribute(node->next, prediacte);
}

void* linkedListGetByAttribute(LinkedList* list, bool (*prediacte)(void*))
{
    return llNodeGetByAttribute(list->node, prediacte);
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

void* llNodeGetByComparison(llNode* node, void* that, bool (*equals)(void*, void*))
{
    if (node == NULL) return NULL;
    if (equals(node->object,that)) return node->object;
    return llNodeGetByComparison(node->next, that, equals);
}

void* linkedListGetByComparison(LinkedList *list, void* that, bool (*equals)(void*, void*))
{
    return llNodeGetByComparison(list->node, that, equals);
}

void linkedListAppend(LinkedList* first, LinkedList* last)
{
    if (linkedListEmpty(last)) return;
    if (linkedListEmpty(first)) {
        first->node = last->node;
        return;
    } 
    
    llNode* pos = first->node;
    while(pos!=NULL && pos->next!= NULL)
    {
        pos = pos->next;
    }
    pos->next = last->node;
}

int linkedListLength(LinkedList* list)
{
    int size = 0;
    for(llNode* l = list->node; l!=NULL; l=l->next)
    {
        size++;
    }
    return size;
}

bool linkedListEmpty(LinkedList* list)
{
    llNode* node = list->node;
    return node == NULL;
}
