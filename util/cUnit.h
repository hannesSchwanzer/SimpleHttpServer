#ifndef _CUNIT_
#define _CUNIT_

#include <stdbool.h>

#define assertIntEq(m,v1,v2)(assertIntEqLine(__LINE__,m,v1,v2))
bool assertIntEqLine(int line,char* message, int expected, int found);

#define assertTrue(m,v)(assertTrueLine(__LINE__,m,v))
bool assertTrueLine(int line,char* message, bool val);

#define assertFalse(m,v)(assertTrueLine(__LINE__,m,!(v)))

#endif