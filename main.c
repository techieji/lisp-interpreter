#include "lisp.h"

int main() {
  char* input = "(define a 5)";
  print_repr(parse(&input));
  return 0;
  /*
  while (true) {
    char* input = (char*)malloc(256 * sizeof(char));
    printf("> ");
    fflush(stdout);
    fgets(input, 256, stdin);
    // print_repr(run(parse(&input), child(NULL)));
    print_repr(parse(&input));
    printf("\n");
  }
  return 0;*/
}
