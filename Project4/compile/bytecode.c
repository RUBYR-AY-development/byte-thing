#include <stdio.h>
#include <string.h>
#include "internal.h"
#include "../include/vector.h"


/*
* translates the starting string into manageable bytecodes
*/

INTERNAL unsigned char* _I_txt_to_bytecode(const char* LINE, size_t* iter) {
  size_t input_len = strlen(LINE);
  unsigned char* orig_bytes = calloc(input_len, sizeof(unsigned char));

  while (*LINE != '\0') {

    if (strncmp(LINE, "PRINT", 5) == 0) {
      orig_bytes[*iter] = 0xFF;
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

INTERNAL void I_elaborate_bytecode(unsigned char** VEC, unsigned char* orig_bytes, size_t* iter) {
  // unsigned char** VEC -- the bytes that this function fills into
  // unsigned char* orig_bytes -- the original bytes that was created by _I_txt_to_bytecode

  // referencing VEC by 'VEC' will return the address of VEC
  // *VEC will return the actual VEC

  for (int i = 0; i < *iter; i++) {
    unsigned char CHR = orig_bytes[i];

    switch (CHR) {
      default:
        vector_add(VEC, unsigned char, CHR);
        break;
    }
  }
}