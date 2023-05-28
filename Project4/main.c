#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/vector.h"
#include "compile/compile.h"

#define READ_FAIL 1
#define READ_SUCCESS 0

// MSVC doesn't have getline for C
int getline(char** lineptr, size_t* n, FILE* stream)
{
  static char line[256];
  char* ptr;
  unsigned int len;

  if (lineptr == NULL || n == NULL)
  {
    errno = 22;
    return -1;
  }

  if (ferror(stream))
    return -1;

  if (feof(stream))
    return -1;

  fgets(line, 256, stream);

  ptr = strchr(line, '\n');
  if (ptr)
    *ptr = '\0';

  len = strlen(line);

  if ((len + 1) < 256)
  {
    ptr = realloc(*lineptr, 256);
    if (ptr == NULL)
      return(-1);
    *lineptr = ptr;
    *n = 256;
  }

  strcpy(*lineptr, line);
  return(len);
}


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

    vector_add(&file_lines, char*, "PRINT \"HELLO WORLD\"");
    vector_add(&file_lines, char*, "0123456789");
    // compile
    unsigned char* bins = L_compile(file_lines);

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