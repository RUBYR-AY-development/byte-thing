#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "_getline.h"

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