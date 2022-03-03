#ifndef DICTIONARY
#define DICTIONARY

#include "../LinkedList/linkedList.h"

#define STANDARD_HASHSIZE 101

typedef struct Dictionary
{
    int hashsize;
    LinkedList** store;
} Dictionary;

typedef struct DictNode
{
    char* key;
    char* value;
} DictNode;


void dictionary_init(Dictionary* dict, int hashsize);
void dictionary_destroy(Dictionary* dict);
void dictionary_add(Dictionary* dict, char* key, char* value);
char* dictionary_getValue(Dictionary* dict, char* key);
LinkedList* dictionary_getAllNodes(Dictionary* dict);
long int stringHash(int hashsize, char* string);
void dictionary_print(Dictionary* dict);


#endif