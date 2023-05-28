#include <stdio.h>
#include "vm.h"
#include "internal.h"
#include "../bytecodes.h"

static void execute_function(_LINE_STATE* LINE_STATE) {
  if (LINE_STATE->CURRENT_FUNC == BYTECODE_PRINT) {
    
  }
}

API void L_bytecode_vm(unsigned char** BINARIES) {
  for (int i = 0; i < vector_size(BINARIES); i++) {
    // each line
    unsigned char* LINE_BINS = BINARIES[i];

    // line state
    create_vector(unsigned char*, CURRENT_FUNC_PARAMS);

    _LINE_STATE LINE_STATE = {
      0, // in string
      0, // reading func parameters
      0x00, // current function
      vector_create(), // current func parameter -- byte collection
      vector_create(),// current string -- byte collection
    };

    
    for (int CHR_PLC = 0; CHR_PLC < vector_size(LINE_BINS); CHR_PLC++) {
      unsigned char CHR = LINE_BINS[CHR_PLC];
      
      switch (CHR) {
        // ascii symbols
        case BYTECODE_DOUBLEQUOTE:
          LINE_STATE.IN_STRING = LINE_STATE.IN_STRING ^ 1;

          if (LINE_STATE.IN_STRING == 0 && LINE_STATE.READING_FUNC_PARAMS == 1) {
            LINE_STATE.CURRENT_FUNC_PARAM = LINE_STATE.CURRENT_STR;
          }

          // reset current_str
          if (LINE_STATE.IN_STRING == 1 && vector_size(LINE_STATE.CURRENT_STR) > 0) {
            vector_free(LINE_STATE.CURRENT_STR);
            LINE_STATE.CURRENT_STR = vector_create();
          }
          
          break;

        case BYTECODE_COMMA:
          if (LINE_STATE.READING_FUNC_PARAMS) {
            vector_add(CURRENT_FUNC_PARAMS, unsigned char*, LINE_STATE.CURRENT_FUNC_PARAM);

            // reset
            vector_free(LINE_STATE.CURRENT_FUNC_PARAM);
            LINE_STATE.CURRENT_FUNC_PARAM = vector_create();
          }
          break;

        // special symbols
        case BYTECODE_FUNC_CALL_ENTRANCE:
          // reading the parameters now
          LINE_STATE.READING_FUNC_PARAMS = 1;
          break;

        case BYTECODE_FUNC_CALL_EXIT:
          if (vector_size(LINE_STATE.CURRENT_FUNC_PARAM) > 0) {
            vector_add(CURRENT_FUNC_PARAMS, unsigned char*, LINE_STATE.CURRENT_FUNC_PARAM);
          }

          // execute the function
          execute_function(&LINE_STATE);

          // reset current_func_params
          if (vector_size(*CURRENT_FUNC_PARAMS) > 0) {
            vector_free(CURRENT_FUNC_PARAMS);
            CURRENT_FUNC_PARAMS = vector_create();
          }
          break;

        // builtin funcs
        case BYTECODE_PRINT:
          LINE_STATE.CURRENT_FUNC = BYTECODE_PRINT;
          break;


        // default
        default:
          if (LINE_STATE.IN_STRING == 1) {
            vector_add(&LINE_STATE.CURRENT_STR,unsigned char*, CHR);
            break;
          }
          if (LINE_STATE.READING_FUNC_PARAMS == 1) {
            vector_add(&LINE_STATE.CURRENT_FUNC_PARAM, unsigned char*, CHR);
            break;
          }
          break;
      }
    }

    vector_free(LINE_STATE.CURRENT_STR);
    vector_free(CURRENT_FUNC_PARAMS);
  }
}