#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdbool.h>


typedef struct llNode{
    void* object;
    struct llNode* next;
} llNode;

typedef struct LinkedList{
    llNode* node;
} LinkedList;




LinkedList* linkedListCreate();
void linkedListDestroy(LinkedList* list);
int linkedListAdd(LinkedList* list, void* object);
//if n is greater than the length of the list, it returns NULL, else it returns the removed object pointer
void* linkedListRemove(LinkedList* list, unsigned int n);
void* linkedListGet(LinkedList* list, unsigned int n);
void linkedListForEach(LinkedList* list, void (*f)(void*));
void linkedListFreeObjects(LinkedList* list);
bool linkedListContains(LinkedList* list, bool (*predicate)(void*));
//compares every object with compare and returns the first fit or NULL if it reaches the end of the list
void* linkedListGetByAttribute(LinkedList* list, bool (*predicate)(void*));
void* linkedListGetByComparison(LinkedList *list, void* that, bool (*equals)(void*, void*));
void linkedListAppend(LinkedList* first, LinkedList* last);
int linkedListLength(LinkedList* list);
bool linkedListEmpty(LinkedList* list);

#endif