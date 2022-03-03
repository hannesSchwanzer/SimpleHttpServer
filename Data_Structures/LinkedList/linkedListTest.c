#include "linkedList.h"
#include "../../util/cUnit.h"

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>


/*
void linkedListFreeObjects(LinkedList* list);
//compares every object with compare and returns the first fit or NULL if it reaches the end of the list
void* linkedListGetByComparison(LinkedList *list, void* that, bool (*equals)(void*, void*));
*/
int sum;

bool llEquals(LinkedList* ll1, LinkedList* ll2)
{
    llNode* n1 = ll1->node;
    llNode* n2 = ll2->node;
    while(n1!=NULL || n2!=NULL)
    {
        if (n1->object!=n2->object) return false;
        n1=n1->next;
        n2=n2->next;
    }
    return ((n1==NULL) == (n2==NULL));
}

bool prediacte1(void* number)
{
    return *((int*) number) == 2;
}

bool prediacte2(void* number)
{
    return *((int*) number) == 4;
}

void summ(void* n)
{
    sum += *(int*) n;
}

void printInt(void* n)
{
    //if(n==NULL) return;
    printf("%d\n", *(int*)n); 
}

int main()
{
    LinkedList* ll1 = linkedListCreate();
    int i1 = 1;
    int i2 = 2;

    LinkedList* ll2 = linkedListCreate();
    int i3 = 3;
    linkedListAdd(ll2, &i3);

    LinkedList* ll_empty = linkedListCreate();

    printf("Testing 'Add':\n");
    assertIntEq("", 0, linkedListAdd(ll1, NULL));
    assertIntEq("", 1, linkedListAdd(ll1, &i1));
    assertIntEq("", 2, linkedListAdd(ll1, &i2));
    printf("Completed.\n");

    printf("Testing 'Get':\n");
    assertTrue("", linkedListGet(ll1, 0) == NULL);
    assertIntEq("", i1, * (int*)linkedListGet(ll1, 1));
    assertTrue("",linkedListGet(ll1, -1) == NULL);
    assertTrue("",linkedListGet(ll1, 4) == NULL);
    assertTrue("", linkedListGet(ll_empty, 3) == NULL);
    printf("Completed.\n");
    
    printf("Testing 'Length':\n");
    assertIntEq("", 3, linkedListLength(ll1));
    assertIntEq("", 0, linkedListLength(ll_empty));
    printf("Completed.\n");

    printf("Testing 'Contais':\n");
    assertTrue("", linkedListContains(ll1, prediacte1));
    assertFalse("", linkedListContains(ll1, prediacte2));
    assertFalse("", linkedListContains(ll_empty, prediacte1));
    printf("Completed.\n");
    
    printf("Testing 'GetByAttribut':\n");
    assertTrue("", linkedListGetByAttribute(ll1, prediacte1) == &i2);
    assertTrue("", linkedListGetByAttribute(ll1, prediacte2) == NULL);
    assertTrue("", linkedListGetByAttribute(ll_empty, prediacte1) == NULL);
    printf("Completed.\n");

    printf("Testing 'Append':\n");
    assertTrue("", linkedListLength(ll_empty) == 0);
    linkedListAppend(ll1, ll_empty);
    assertIntEq("", 3, linkedListLength(ll1));
    linkedListAppend(ll1,ll2);
    assertIntEq("", 4, linkedListLength(ll1));
    linkedListAppend(ll_empty, ll_empty);
    assertIntEq("", 0, linkedListLength(ll_empty));
    printf("Completed.\n");

    printf("Testing 'forEach':\n");
    sum = 0;
    linkedListForEach(ll1, summ);
    assertIntEq("", i1+i2+i3, sum);
    sum = 0;
    linkedListForEach(ll2, summ);
    assertIntEq("", i3, sum);
    sum = 0;
    linkedListForEach(ll_empty, summ);
    assertIntEq("", 0, sum);
    printf("Completed.\n");

    printf("Testing 'remove':\n");
    assertTrue("", linkedListRemove(ll_empty, 1) == NULL);
    assertTrue("", linkedListRemove(ll_empty, -1) == NULL);
    assertTrue("", linkedListRemove(ll1, 0) == NULL);
    assertIntEq("", 3, linkedListLength(ll1));
    assertTrue("", linkedListRemove(ll1, 1) == &i2);
    assertIntEq("", 2, linkedListLength(ll1));
    assertTrue("", linkedListRemove(ll1, 0) == &i1);
    assertIntEq("", 1, linkedListLength(ll1));
    assertTrue("", linkedListRemove(ll1, 0) == &i3);
    assertIntEq("", 0, linkedListLength(ll1));
    printf("Completed.");
}