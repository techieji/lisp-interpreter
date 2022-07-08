#include "lisp.h"

bool is_special_form(struct Object* sym) {
  return sym->type == SYMBOL &&
    (strcmp(sym->str, "if") == 0 ||
     strcmp(sym->str, "cond") == 0 ||
     strcmp(sym->str, "define") == 0);  // Continue...
}

struct Object* run(struct Object* tree, struct EnvStack* es) {
  switch (tree->type) {
    case PAIR:
      if (is_special_form(tree->pair->car))
        return run_special_form(tree, es);
      struct Object* fn = run(tree->pair->car, es);
      struct Object* args = (struct Object*)malloc(sizeof(struct Object));
      args->type = NIL;
      for (struct Object* p = tree->pair->cdr; p->type != NIL; p = p->pair->cdr)
        iappend(args, run(p, es));
      return call(fn->func, args, es);
    case SYMBOL:
      return get_var_from_env(es, tree->str);
    case BOOL:
    case INT:
    case FLOAT:
    case STRING:
      return tree;
    default:
      return NULL;   // FUNCTION and NIL aren't going to be seen
  }
}

struct Object* run_special_form(struct Object* tree, struct EnvStack* es) {
  return tree;  // FIXME: finish
}
