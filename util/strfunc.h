#ifndef STRING_FUNCTIONS
#define STRING_FUNCTIONS

//trim string from whitespaces \r, \n; Returns NULL if reaches end of string
char* trimLeft(char* string);
char* trimRight(char* string);
char* trimBoth(char* string);
void toLowerCase(char* string);

#endif