#include <stdio.h>
#include <stdlib.h>

#include "eprintf.h"

#define NCODE 16
#define NSTACK 128

typedef struct Symbol Symbol;
typedef struct Tree Tree;

struct Symbol
{
    int value;
    char *name;
};

struct Tree
{
    int op;         // operation code
    int value;      // value if number
    Symbol *symbol; // Symbol entry if variable
    Tree *left;
    Tree *right;
};

typedef union Code Code;
union Code {
    void (*op)(void); // function if operator
    int value;        // value if number
    Symbol *symbol;   // Symbol entry if variable
};

Code code[NCODE];
int stack[NSTACK];
int stackp;
int pc; // program counter

enum // operation codes, Tree.op
{
    NUMBER,
    VARIABLE,
    ADD,
    DIVIDE,
    MAX,
    ASSIGN
};

void pushop(void)
{
    stack[stackp++] = code[pc++].value;
}

void pushsymop(void)
{
    stack[stackp++] = code[pc++].symbol->value;
}

void addop(void)
{
    int left = stack[--stackp];
    int right = stack[--stackp];
    stack[stackp++] = left + right;
}

void divop(void)
{
    int right = stack[--stackp];
    int left = stack[--stackp];
    if (right == 0)
        eprintf("divide %d by zero", left);
    stack[stackp++] = left / right;
}

void maxop(void)
{
    int right = stack[--stackp];
    int left = stack[--stackp];
    stack[stackp++] = left > right ? left : right;
}

void storesymop(void)
{
    int val = stack[--stackp];
    code[pc++].symbol->value = val;
    stack[stackp++] = val;
}

/* generate: generate instructions by walking tree */
int generate(int codep, Tree *t)
{
    switch (t->op)
    {
    case NUMBER:
        code[codep++].op = pushop;
        code[codep++].value = t->value;
        return codep;
    case VARIABLE:
        code[codep++].op = pushsymop;
        code[codep++].symbol = t->symbol;
        return codep;
    case ADD:
        codep = generate(codep, t->left);
        codep = generate(codep, t->right);
        code[codep++].op = addop;
        return codep;
    case DIVIDE:
        codep = generate(codep, t->left);
        codep = generate(codep, t->right);
        code[codep++].op = divop;
        return codep;
    case MAX:
        codep = generate(codep, t->left);
        codep = generate(codep, t->right);
        code[codep++].op = maxop;
        return codep;
    case ASSIGN:
        codep = generate(codep, t->right);
        code[codep++].op = storesymop;
        code[codep++].symbol = t->left->symbol;
        return codep;
    default:
        eprintf("unknown op: %d", t->op);
        break;
    }
    return -1;
}

/* eval: version 3: evaluate expression from generated code */
int eval(Tree *t)
{
    pc = generate(0, t);
    code[pc].op = NULL;

    stackp = 0;
    pc = 0;

    while (code[pc].op != NULL)
    {
        (*code[pc++].op)();
    }
    return stack[0];
}

int main()
{
    Symbol *sym_a = (Symbol *)malloc(sizeof(Symbol));
    sym_a->name = "a";
    sym_a->value = 0;

    Symbol *sym_b = (Symbol *)malloc(sizeof(Symbol));
    sym_b->name = "b";
    sym_b->value = 3;

    Symbol *sym_c = (Symbol *)malloc(sizeof(Symbol));
    sym_c->name = "c";
    sym_c->value = 4;

    Tree *t = (Tree *)malloc(sizeof(Tree));
    t->op = ASSIGN;

    t->left = (Tree *)malloc(sizeof(Tree));
    t->left->op = VARIABLE;
    t->left->symbol = (Symbol *)malloc(sizeof(Symbol));
    t->left->symbol = sym_a;

    t->right = (Tree *)malloc(sizeof(Tree));
    t->right->op = MAX;

    t->right->left = (Tree *)malloc(sizeof(Tree));
    t->right->left->op = VARIABLE;
    t->right->left->symbol = sym_b;

    t->right->right = (Tree *)malloc(sizeof(Tree));
    t->right->right->op = DIVIDE;

    t->right->right->left = (Tree *)malloc(sizeof(Tree));
    t->right->right->left->op = VARIABLE;
    t->right->right->left->symbol = sym_c;

    t->right->right->right = (Tree *)malloc(sizeof(Tree));
    t->right->right->right->op = NUMBER;
    t->right->right->right->value = 2;

    int res = eval(t);
    printf("res: %d\n", res);
    return 0;
}
