#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum ObjectType {
  BOOL,
  INT,
  FLOAT,
  STRING,
  SYMBOL,
  FUNCTION,
  PAIR,
  NIL
};

struct Object {
  enum ObjectType type;
  union {
    bool b;
    int* i;
    double* f;
    char* str;
    struct Function* func;
    struct Pair* pair;
  };
};

struct Pair {
  struct Object* car;
  struct Object* cdr;
};

struct Function {
  struct Object* args;
  struct Object* code;
};

struct Env {
  char* var;
  struct Object* val;
  struct Env* next;
};

struct EnvStack {
  struct Env* here;
  struct EnvStack* back;
};

// Parsing

struct Object* parse(char**);
struct Object* parse_literal(char**);

// Environment

struct EnvStack* child(struct EnvStack*);
void set_var(struct Env*, char*, struct Object*);
struct Object* get_var(struct Env*, char*);
struct Object* get_var_from_env(struct EnvStack*, char*);

// Execution

bool is_special_form(struct Object*);
struct Object* run(struct Object*, struct EnvStack*);
struct Object* run_special_form(struct Object*, struct EnvStack*);

// STL

struct Pair* cons(struct Object*, struct Object*);
struct Object* call(struct Function*, struct Object*, struct EnvStack*);
void print_repr(struct Object*);
bool is_list(struct Object*);

void iappend(struct Object*, struct Object*);

// Utils

void die(int, char*);
