#ifndef _VM_H_
#define _VM_H_
#define API extern
#include <stdio.h>
#include "../include/vector.h"

API void L_bytecode_vm(unsigned char** BINARIES);

#endif