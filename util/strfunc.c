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

char* StringFind(char* str1, char* str2)
{
    //printf("Eintritrr\n");
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    //printf("Laenge\n");
    if(len2 == 0) return str1;
    for(int i = 0; i < len1-len2+1; i++)
    {
        //printf("%d:\n",i);
        for(int j = 0; j < len2; j++)
        {
            //printf("\t%d\n",j);
            if(str1[i+j]!=str2[j]) break;
            if(j==len2-1) return str1+i;
        }
    }

    return NULL;
}

