#include "lisp.h"

struct EnvStack* child(struct EnvStack* back) {
  struct EnvStack* es = (struct EnvStack*)malloc(sizeof(struct EnvStack));
  es->here = (struct Env*)malloc(sizeof(struct Env));
  es->here->next = NULL;
  es->back = back;
  return es;
}

void set_var(struct Env* e, char* k, struct Object* v) {
  while (e->next != NULL) e = e->next;
  e->var = k;
  e->val = v;
  e->next = (struct Env*)malloc(sizeof(struct Env));
  e->next->next = NULL;
}

struct Object* get_var(struct Env* e, char* k) {
  for (; e->next != NULL; e = e->next)
    if (strcmp(e->var, k) == 0)
      return e->val;
  return NULL;
}

struct Object* get_var_from_env(struct EnvStack* es, char* sym) {
  struct Object* res;
  while (es != NULL) {
    if ((res = get_var(es->here, sym)) != NULL)
      return res;
    es = es->back;
  }
  return NULL;
}
