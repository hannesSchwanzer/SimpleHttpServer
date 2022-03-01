#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdbool.h>


typedef struct LinkedList{
    void* object;
    struct LinkedList* next;
} LinkedList;



LinkedList* linkedListCreate();
void linkedListDestroy(LinkedList* list);
void linkedListAdd(LinkedList* list, void* object);
//if n is greater than the length of the list, it returns NULL, else it returns the removed object pointer
void* linkedListRemove(LinkedList* list, unsigned int n);
void* linkedListGet(LinkedList* list, unsigned int n);
void linkedListForEach(LinkedList* list, void (*f)(void*));
void linkedListFreeObjects(LinkedList* list);
bool linkedListContains(LinkedList* list, bool (*predicate)(void*));
//compares every object with compare and returns the first fit or NULL if it reaches the end of the list
void* linkedListGetByAttribut(LinkedList* list, bool (*predicate)(void*));
void* linkedListGetByComparison(LinkedList *list, void* that, bool (*equals)(void*, void*));

#endif