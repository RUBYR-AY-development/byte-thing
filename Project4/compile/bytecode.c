#include <stdio.h>
#include <string.h>
#include "internal.h"
#include "../include/vector.h"


/*
* translates the starting string into manageable bytecodes.
* This generates a collection of bytes that are simple translations as a starting
* point for I_elaborate_bytecode.
*/

INTERNAL unsigned char* _I_txt_to_bytecode(const char* LINE, size_t* iter) {
  size_t input_len = strlen(LINE);
  unsigned char* orig_bytes = calloc(input_len, sizeof(unsigned char));

  while (*LINE != '\0') {

    if (strncmp(LINE, "PRINT", 5) == 0) {
      orig_bytes[*iter] = BYTECODE_PRINT;
      LINE += 5;
    }
    else {
      // Normal character
      orig_bytes[*iter] = *LINE;
      LINE++;
    }
    (*iter)++;
  }

  return orig_bytes;
}


/*
* modifies the existing bytecodes to make it more readable
*/

INTERNAL void I_elaborate_bytecode(bytes_vec* VEC, unsigned char* orig_bytes, size_t* iter) {
  // unsigned char** VEC -- the bytes that this function fills into
  // unsigned char* orig_bytes -- the original bytes that was created by _I_txt_to_bytecode

  // referencing VEC by 'VEC' will return the address of VEC
  // *VEC will return the actual VEC

  BYTECODE_STATE STATE = {
    0, // in function call
    0 // in string
  };


  for (int i = 0; i < *iter; i++) {
    unsigned char CHR = orig_bytes[i];

    switch (CHR) {
      case BYTECODE_WHITESPACE:
        if (STATE.IN_STRING == 1) {
          vector_add(VEC, unsigned char, BYTECODE_WHITESPACE);
        }
        break;

      case BYTECODE_DOUBLEQUOTE:
        STATE.IN_STRING = STATE.IN_STRING ^ 1;
        break;

      case BYTECODE_LEFT_PAREN:
        if (i > 0 && (*VEC)[i - 1] == BYTECODE_FUNC_CALL) {
          vector_add(VEC, unsigned char, BYTECODE_FUNC_CALL_ENTRANCE);
          STATE.IN_FUNC_CALL = 1;
          break;
        }
        vector_add(VEC, unsigned char, BYTECODE_LEFT_PAREN);
        break;

      case BYTECODE_RIGHT_PAREN:
        if (STATE.IN_FUNC_CALL) {
          vector_add(VEC, unsigned char, BYTECODE_FUNC_CALL_EXIT);
          STATE.IN_FUNC_CALL = 0;
          break;
        }
        vector_add(VEC, unsigned char, BYTECODE_RIGHT_PAREN);
        break;

      // special symbols
      case BYTECODE_PRINT:
        vector_add(VEC, unsigned char, BYTECODE_PRINT);
        vector_add(VEC, unsigned char, BYTECODE_FUNC_CALL);
        break;


      // default
      default:
        vector_add(VEC, unsigned char, CHR);
        break;
    }
  }


}