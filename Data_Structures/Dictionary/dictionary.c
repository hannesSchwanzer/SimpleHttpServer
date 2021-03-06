#include "dictionary.h"
#include "../LinkedList/linkedList.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void dictionary_init(Dictionary* dict, int hashsize)
{
    dict->hashsize = hashsize;
    dict->store = malloc(hashsize * sizeof(LinkedList*));
}

void freeDictNode(void* node)
{
    if (node == NULL) return;
    DictNode* n = (DictNode*) node;
    free(n->key);
    free(n->value);
    free(n);
}

void dictionary_destroy(Dictionary* dict)
{
    for (int i=0; i<dict->hashsize; i++)
    {
        if (dict->store[i] == NULL) continue;
        linkedListForEach(dict->store[i], freeDictNode);
        linkedListDestroy(dict->store[i]);
    }
    free(dict->store);
}

bool dictNodeKeyEquals(void* this, void* that)
{
    if(this == NULL || that == NULL) return false;
    DictNode* thisNode = this;
    char* thatString = that;
    return strcmp(thisNode->key,thatString)==0;
}

void dictionary_add(Dictionary* dict, char* key, char* value)
{
    long int stringhash = stringHash(dict->hashsize, key);
    
    if (dict->store[stringhash] == NULL)
    {
        dict->store[stringhash] = linkedListCreate();
    }

    LinkedList* ll = dict->store[stringhash];
    DictNode* node = linkedListGetByComparison(ll, key, dictNodeKeyEquals);
    if (node == NULL)
    {
        DictNode* n = malloc(sizeof(DictNode));

        n->key = malloc((strlen(key)+1)*sizeof(char));
        strcpy(n->key, key);
        n->value = malloc((strlen(value)+1)*sizeof(char));
        strcpy(n->value, value);
        linkedListAdd(ll, n);
    } 
    else 
    {
        node->value = realloc(node->value, (strlen(value)+1)*sizeof(char));
        strcpy(node->value, value);
    }

}

char* dictionary_getValue(Dictionary* dict, char* key)
{
    long int stringhash = stringHash(dict->hashsize, key);
    
    if (dict->store[stringhash] == NULL) return NULL;
    
    LinkedList* ll = dict->store[stringhash];
    DictNode* node = linkedListGetByComparison(ll, key, dictNodeKeyEquals);;
    if (node == NULL) return NULL;
    return node->value;
}

const int p = 53;
long int stringHash(int hashsize, char* string)
{
    long int hash_value = 0;
    int pow = 1;
    for(int i=0; i<(long int) strlen(string);i++)
    {
        hash_value = (hash_value + (string[i] - 'A' + 1) * pow) % hashsize;
        pow = (pow * p) % hashsize;
    }
    return hash_value;
}

LinkedList* dictionary_getAllNodes(Dictionary* dict)
{
    LinkedList* ll = linkedListCreate();
    for(int i=0; i<dict->hashsize; i++)
    {
        if (dict->store[i] == NULL) continue;
        linkedListAppend(ll, dict->store[i]);

    }
    return ll;
}

void printNode(void* n)
{
    if (n == NULL) {
        //printf("NULL\n");
        return;
    }
    DictNode* node = n;
    printf("%s: %s\n", node->key, node->value);
}

void dictionary_print(Dictionary* dict)
{
    LinkedList* ll = dictionary_getAllNodes(dict);
    linkedListForEach(ll, printNode);
}
