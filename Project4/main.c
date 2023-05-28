#include <stdio.h>
#include <stdlib.h>
#include "include/vector.h"
#include "include/_getline.h"
#include "compile/compile.h"
#include "vm/vm.h"

#define READ_FAIL 1
#define READ_SUCCESS 0


int main(int argc, char* argv[]) {
  FILE* test_file = fopen("test.txt", "r");
  create_vector(char*, file_lines);

  if (test_file != NULL) {
    // read
    /*
    * this code is currently bugged its so annoying
    
    char* line = NULL;
    size_t line_len = 0;
    size_t read;

    while ((read = getline(&line, &line_len, test_file)) != EOF) {
      vector_add(&file_lines, char*, &line);
    }

    for (int i = 0; i < vector_size(file_lines); i++) {
      printf("%s",file_lines[i]);
    }
    */

    vector_add(&file_lines, char*, "PRINT (\"HELLO WORLD\", \"aye\")");
    //vector_add(&file_lines, char*, "0123456789");
    // compile
    unsigned char** bins = L_compile(file_lines);
    L_bytecode_vm(bins); // start vm

    // cleanup
    L_compile_cleanup(bins);

    fclose(test_file);
    //free(line);
    vector_free(file_lines);

    exit(READ_SUCCESS);
  }
  else {
    vector_free(file_lines);
    exit(READ_FAIL);
  }
}