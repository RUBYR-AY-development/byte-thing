// internal definitions for the compiler

#ifndef _CMP_INTERNAL_H_
#define _CMP_INTERNAL_H_
#define INTERNAL extern
#include "../include/vector.h"
#include "../bytecodes.h"

/*
* MACROS
*/

#define PRINT_BINARIES 1

// size_t iter & unsigned char* orig_bytes will be used by the main code piece compile.c
#define I_txt_to_bytecode(LINE, iter_addr)                      \
  size_t iter = 0;                                              \
  unsigned char* orig_bytes = _I_txt_to_bytecode(LINE, &iter);


/*
* DEFINE TYPES
*/

typedef unsigned char* bytes_vec;

typedef struct {
  int IN_FUNC_CALL;
  int IN_STRING;
} BYTECODE_STATE;


/*
* INTERNAL CALLS
*/

INTERNAL void I_cleanup_bytes(unsigned char* VEC);
INTERNAL void I_print_binaries(unsigned char* VEC);
INTERNAL unsigned char* _I_txt_to_bytecode(const char* LINE);
INTERNAL void I_elaborate_bytecode(unsigned char* VEC, size_t* iter);

#endif