#include "stdio.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char buffer[] = "ABCDEF";
  memcpy(buffer + 2, buffer, 4);
  printf("%s\n", buffer);
  return EXIT_SUCCESS;
}
