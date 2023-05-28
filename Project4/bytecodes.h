#ifndef _BYTECODES_H_
#define _BYTECODES_H_

// bytecodes for special symbols for the compiled version of the code lines (char*)
#define BYTECODE_FUNC_CALL          0x81
#define BYTECODE_PRINT              0x82
#define BYTECODE_FUNC_CALL_ENTRANCE 0x83
#define BYTECODE_FUNC_CALL_EXIT     0x84

// ascii symbols
#define BYTECODE_LEFT_PAREN         0x28
#define BYTECODE_RIGHT_PAREN        0x29
#define BYTECODE_WHITESPACE         0x20
#define BYTECODE_DOUBLEQUOTE        0x22
#define BYTECODE_COMMA              0x2C

#endif