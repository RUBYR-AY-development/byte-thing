// internal definitions for the compiler

#ifndef _INTERNAL_H_
#define _INTERNAL_H_
#define INTERNAL extern
#include "../include/vector.h"


/*
* MACROS
*/

#define PRINT_BINARIES 1

// creates 'line_ret' variable that will be used by the main code piece
#define I_return_line_ret(ret) COMPILE_LINE_RET line_ret = { ret,vector_size(ret) };

// size_t iter & unsigned char* orig_bytes will be used by the main code piece compile.c
#define I_txt_to_bytecode(LINE, iter_addr)                      \
  size_t iter = 0;                                              \
  unsigned char* orig_bytes = _I_txt_to_bytecode(LINE, &iter);

// MACRO CONSTANTS

// bytecodes for special symbols for the compiled version of the code lines (char*)
#define BYTECODE_PRINT 0xFF

/*
* DEFINE TYPES
*/

typedef unsigned char* bytes_vec;

typedef struct {
  unsigned char* bin;
  int size;
} COMPILE_LINE_RET;


/*
* INTERNAL CALLS
*/

INTERNAL void I_cleanup_bytes(unsigned char* VEC);
INTERNAL void I_print_binaries(unsigned char* VEC);
INTERNAL unsigned char* _I_txt_to_bytecode(const char* LINE);
INTERNAL void I_elaborate_bytecode(unsigned char* VEC, size_t* iter);

#endif