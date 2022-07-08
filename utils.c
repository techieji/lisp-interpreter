#include "lisp.h"

void die(int error_code, char* error_msg) {
  printf("ERROR: %s", error_msg);
  exit(error_code);
}
