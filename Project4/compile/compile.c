#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compile.h"
#include "internal.h"


static unsigned char* L_compile_line(const char* LINE) {
  I_txt_to_bytecode(LINE);

  // create new markers with those bytes
  create_vector(unsigned char, ret); // the bytecodes returned
  I_elaborate_bytecode(&ret, orig_bytes, &iter);


  I_cleanup_bytes(ret);
  I_print_binaries(ret);

  free(orig_bytes);
  return ret;
}

API unsigned char* L_compile(const char** LINES_VEC) {
  // gather binaries
  create_vector(unsigned char*, binaries);

  for (int i = 0; i < vector_size(LINES_VEC); i++) {
    unsigned char* line_ret = L_compile_line(LINES_VEC[i]);

    vector_add(&binaries, unsigned char*, line_ret);
  }

  return binaries;
}

API void L_compile_cleanup(unsigned char* BINARIES) {
  vector_free(BINARIES);
}