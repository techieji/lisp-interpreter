#include "lisp.h"

struct Object* parse(char** sp) {
  struct Object* tree = (struct Object*)malloc(sizeof(struct Object));
  //tree->type = PAIR;
  //tree->pair = (struct Pair*)malloc(sizeof(struct Pair));
  tree->type = NIL;
  while (**sp != ')') {
    switch (**sp) {
      case ' ':
        (*sp)++;
        break;
      case '(':
        (*sp)++;
        iappend(tree, parse(sp));
        break;
      default:
        iappend(tree, parse_literal(sp));
    }
  }
  return tree;
}

struct Object* parse_literal(char** sp) {
  struct Object* o = (struct Object*)malloc(sizeof(struct Object));
  if (**sp == '"') { // String
    (*sp)++;
    o->type = STRING;
    int i;
    for (i = 0; *(*sp + i) != '"'; i++);
    o->str = (char*)malloc((i + 1) * sizeof(char));
    strncpy(o->str, *sp, i);
    *sp += i;
  } else if (isdigit(**sp)) { // Number: (int or float)
    char c;
    int i;
    bool is_int = true;
    for (i = 0, c = **sp; isdigit(c) || c == '.'; i++, c = *(*sp + i))
      if (c == '.')
        is_int = false;
    if (is_int) {
      o->type = INT;
      o->i = (int*)malloc(sizeof(int));
      *(o->i) = atoi(*sp);
    } else {
      o->type = FLOAT;
      o->f = (double*)malloc(sizeof(double));
      *(o->f) = atof(*sp);
    }
    *sp += i;
  } else { // Symbol
    o->type = SYMBOL;
    int i;
    for (i = 0; *(*sp + i) != ' '; i++);
    o->str = (char*)malloc((i + 1) * sizeof(char));
    *sp += i;
  }
  return o;
}
