#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compile.h"
#include "internal.h"

#define PRINT_BINARIES 1


static COMPILE_LINE_RET L_compile_line(const char* LINE) {
  size_t input_len = strlen(LINE);
  unsigned char* orig_bytes = calloc(input_len, sizeof(unsigned char));

  size_t iter = 0;

  while (*LINE != '\0') {

    if (strncmp(LINE, "PRINT", 5) == 0) {
      orig_bytes[iter] = 0xFF;
      LINE += 5;
    }
    else {
      // Normal character
      orig_bytes[iter] = *LINE;
      LINE++;
    }
    iter++;
  }

  // create new markers with those bytes
  create_vector(unsigned char, ret); // the bytecodes returned

  for (int i = 0; i < iter; i++) {
    unsigned char CHR = orig_bytes[i];

    switch (CHR) {
      default:
        vector_add(&ret, unsigned char, CHR);
        break;
    }
  }

  I_cleanup_bytes(ret);

  // final step: reallocation

  if (PRINT_BINARIES) {
    for (int i = 0; i < vector_size(ret); i++) {
      printf("%02X ", ret[i]);
    }
    printf("\n");
  }

  // finish return val
  COMPILE_LINE_RET line_ret = { ret,vector_size(ret)};
  return line_ret;
}

API unsigned char* L_compile(const char** LINES_VEC) {
  size_t total_vec_size = 0;
  // get size of everything
  for (int i = 0; i < vector_size(LINES_VEC); i++) {
    total_vec_size += strlen(LINES_VEC[i]);
  }

  // gather binaries
  unsigned char* binaries = calloc(total_vec_size, sizeof(unsigned char));

  for (int i = 0; i < vector_size(LINES_VEC); i++) {
    COMPILE_LINE_RET line_ret = L_compile_line(LINES_VEC[i]);
    // reallocate
    binaries = realloc(binaries, (total_vec_size - (strlen(LINES_VEC[i]) - line_ret.size)) * sizeof(unsigned char));

    binaries[i] = line_ret.bin;
  }
}

API void L_compile_cleanup(unsigned char* BINARIES) {

}