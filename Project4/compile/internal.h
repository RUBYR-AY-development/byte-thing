// internal definitions

#ifndef _INTERNAL_H_
#define _INTERNAL_H_
#define INTERNAL extern

typedef unsigned char* bytes_vec;

typedef struct {
  unsigned char* bin;
  int size;
} COMPILE_LINE_RET;


/*
* INTERNAL CALLS
*/

INTERNAL void I_cleanup_bytes(unsigned char* VEC);

#endif