#ifndef _COMPILE_H_
#define _COMPILE_H_
#define API extern
#include "../include/vector.h"
#include <stdio.h>

API unsigned char* L_compile(const char** LINES_VEC);
API void L_compile_cleanup(unsigned char* BINARIES);

#endif