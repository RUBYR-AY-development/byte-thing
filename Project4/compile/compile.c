#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compile.h"

#define PRINT_BINARIES 1

typedef struct {
  unsigned char* bin;
  int size;
} COMPILE_LINE_RET;

static COMPILE_LINE_RET L_compile_line(const char* LINE) {
  size_t input_len = strlen(LINE);
  unsigned char* ret = calloc(input_len, sizeof(unsigned char));

  size_t iter = 0;

  while (*LINE != '\0') {

    if (strncmp(LINE, "PRINT", 5) == 0) {
      ret[iter] = 0xFF;
      LINE += 5;
    }
    else {
      // Normal character
      ret[iter] = *LINE;
      LINE++;
    }
    iter++;
  }

  // remove the 0x00's
  size_t count = 0;
  for (int i = 0; i < iter; i++) {
    if (ret[i] == 0x00) {
      count++;
    }
  }
  input_len -= count;

  
  int size_set = input_len;


  int in_string = 0;
  int in_numeric = 0;

  for (int i = 0; i < iter; i++) {
    char CHR = ret[i];

    switch (CHR) {
      case 0xFF:
        size_set++;

        break;
    }
  }

  // final step: reallocation
  ret = realloc(ret, size_set * sizeof(unsigned char));


  if (PRINT_BINARIES) {
    for (int i = 0; i < iter; i++) {
      printf("%02X ", ret[i]);
    }
    printf("\n");
  }

  // finish return val
  COMPILE_LINE_RET line_ret = { ret,iter };
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