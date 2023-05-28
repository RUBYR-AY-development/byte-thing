/*
* Cleanup unecessary '0x00's
*/
#include <stdio.h>
#include "internal.h"
#include "../include/vector.h"

INTERNAL void I_cleanup_bytes(bytes_vec VEC) {
  for (int i = 0; i < vector_size(VEC); i++) {
    char CHR = VEC[i];

    if (CHR == 0x00) {
      vector_remove(VEC, i);
    }
  }
}