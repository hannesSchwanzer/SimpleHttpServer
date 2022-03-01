#include "strfunc.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>


char* trimLeft(char* string)
{
    char* pointerPos = string;
    int strSize = strlen(string);
    int pos = 0;
    while ((pos<strSize) && (*pointerPos == '\n' || *pointerPos == '\r' || *pointerPos == ' '))
    {
        pos++;
        pointerPos++;
    }
    return pointerPos;
}

char* trimRight(char* string)
{
    int strSize = strlen(string);
    char* pointerPos = string+strSize-1;
    int pos = 0;
    while ((pos<strSize) && (*pointerPos == '\n' || *pointerPos == '\r' || *pointerPos == ' '))
    {
        pos++;
        *pointerPos = '\0';
        pointerPos--;
    }
    return string;
}


char* trimBoth(char* string)
{
    char* result = trimRight(string);
    return trimLeft(result);
}

void toLowerCase(char* string)
{
    int strSize = strlen(string);

    for(int i=0;i<strSize;i++)
    {
        string[i] = tolower(string[i]);
    }
}
