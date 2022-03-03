#include "cUnit.h"
#include <stdio.h>
#include <stdbool.h>



bool assertIntEqLine(int line,char* message, int expected, int found){
  if (expected!=found){
      printf("AssertionFailedError:\n");
      printf("  (%d) fail: %s, expected [%d] found [%d]\n",line,message,expected,found);
      fflush(stdout);
      return false;
  }
  return true;
}

bool assertTrueLine(int line,char* message, bool val){
    if (!val){
      printf("AssertionFailedError:\n");
      printf("\t(%d) fail: %s\n",line,message);
      fflush(stdout);
    }
    return val;
}