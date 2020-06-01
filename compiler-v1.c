#include <stdio.h>
#include <stdlib.h>

#include "eprintf.h"

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

enum // operation codes, Tree.op
{
    NUMBER,
    VARIABLE,
    ADD,
    DIVIDE,
    MAX,
    ASSIGN
};

/* eval: version 1: evaluate tree expression */
int eval(Tree *t)
{
    int left, right;

    switch (t->op)
    {
    case NUMBER:
        return t->value;
    case VARIABLE:
        return t->symbol->value;
    case ADD:
        return eval(t->left) + eval(t->right);
    case DIVIDE:
        left = eval(t->left);
        right = eval(t->right);
        if (right == 0)
            eprintf("divide %d by zero", left);
        return left / right;
    case MAX:
        left = eval(t->left);
        right = eval(t->right);
        return left > right ? left : right;
    case ASSIGN:
        t->left->symbol->value = eval(t->right);
        return t->left->symbol->value;
    default:
        eprintf("unknown op: %d", t->op);
        break;
    }
    return -1;
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
    t->right->left->symbol = (Symbol *)malloc(sizeof(Symbol));
    t->right->left->symbol = sym_b;

    t->right->right = (Tree *)malloc(sizeof(Tree));
    t->right->right->op = DIVIDE;

    t->right->right->left = (Tree *)malloc(sizeof(Tree));
    t->right->right->left->op = VARIABLE;
    t->right->right->left->symbol = sym_c;
    t->right->right->left->left = NULL;
    t->right->right->left->right = NULL;

    t->right->right->right = (Tree *)malloc(sizeof(Tree));
    t->right->right->right->op = NUMBER;
    t->right->right->right->value = 2;
    t->right->right->right->left = NULL;
    t->right->right->right->right = NULL;

    int res = eval(t);
    printf("res: %d\n", res);
    return 0;
}
