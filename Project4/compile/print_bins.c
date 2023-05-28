#include <stdio.h>
#include "../include/vector.h"
#include "internal.h"

INTERNAL void I_print_binaries(unsigned char* VEC) {
  if (PRINT_BINARIES) {
    for (int i = 0; i < vector_size(VEC); i++) {
      printf("%02X ", VEC[i]);
    }
    printf("\n");
  }
}