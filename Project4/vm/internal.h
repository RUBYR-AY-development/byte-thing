#ifndef _VM_INTERNAL_H_
#define _VM_INTERNAL_H_
#define INTERNAL extern
#include "../include/vector.h"


/*
* MACROS
*/

#define PRINT_OUTPUT 1

/*
* DEFINE TYPES
*/

typedef struct {
  int IN_STRING;
  int READING_FUNC_PARAMS;
  unsigned char CURRENT_FUNC;
  unsigned char* CURRENT_FUNC_PARAM; // vector
  unsigned char* CURRENT_STR; // vector
} _LINE_STATE;

/*
* INTERNAL CALLS
*/

INTERNAL void I_execute_func();

#endif