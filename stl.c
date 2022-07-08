#include "lisp.h"

struct Pair* cons(struct Object* car, struct Object* cdr) {
  struct Pair* p = (struct Pair*)malloc(sizeof(struct Pair));
  p->car = car;
  p->cdr = cdr;
  return p;
}

struct Object* call(struct Function* fn, struct Object* args, struct EnvStack* es) {
  struct EnvStack* this = child(es);
  struct Object* argnames = fn->args;
  // Add checking for loop below
  for (; args->type != NIL; args = args->pair->cdr, argnames = argnames->pair->cdr)
    set_var(this->here, argnames->pair->car->str, args->pair->car);
  struct Object* o = run(fn->code, es);
  free(this);
  return o;
}

unsigned int quoted = 0;
void print_repr(struct Object* o) {
  switch (o->type) {
    case BOOL:
      if (o->b) printf("#t"); else printf("#f");
      break;
    case INT:
      printf("%d", *o->i);
      break;
    case FLOAT:
      printf("%f", *o->f);
      break;
    case STRING:
      printf("\"%s\"", o->str);
      break;
    case SYMBOL:
      if (!quoted) printf("'");
      printf("%s", o->str);
      break;
    case FUNCTION:
      printf("#<function>");
      break;
    case NIL:
    case PAIR:
      if (is_list(o)) {
        bool ran = false;
        if (!quoted++) printf("'");
        printf("(");
        quoted = true;
        for (; o->type == PAIR; o = o->pair->cdr) {
          ran = true;
          print_repr(o->pair->car);
          printf(" ");
        }
        if (ran) printf("\b");
        printf(")");
      } else {
        if (!quoted++) printf("'");
        printf("(");
        print_repr(o->pair->car);
        printf(" . ");
        print_repr(o->pair->cdr);
        printf(")");
      }
      quoted--;
  }
}

bool is_list(struct Object* l) {
  while (l->type == PAIR) l = l->pair->cdr;
  return l->type == NIL;
}

void iappend(struct Object* pair, struct Object* o) {
  while (pair->type != NIL) pair = pair->pair->cdr;
  pair->type = PAIR;
  pair->pair = (struct Pair*)malloc(sizeof(struct Pair));
  pair->pair->car = o;
  pair->pair->cdr = (struct Object*)malloc(sizeof(struct Object));
  pair->pair->cdr->type = NIL;
}
