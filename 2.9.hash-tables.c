#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NHASH 102400

typedef struct Namevel Namevel;
struct Namevel
{
    char *name;
    int value;
    Namevel *next; // in chain
};
Namevel *symtab[NHASH]; // a symbol table

enum
{
    MULTIPLIER = 31
};

// hash: compute hash value of string
unsigned int hash(char *str)
{
    unsigned int h;
    unsigned char *p;
    h = 0;
    for (p = (unsigned char *)str; *p != '\0'; p++)
        h = MULTIPLIER * h + *p;
    return h % NHASH;
}

// lookup: find name in symtab, with optional create
Namevel *lookup(char *name, int create, int value)
{
    int h;
    Namevel *sym;

    h = hash(name);
    for (sym = symtab[h]; sym != NULL; sym = sym->next)
        if (strcmp(name, sym->name) == 0)
            return sym;
    if (create)
    {
        sym = (Namevel *)malloc(sizeof(Namevel));
        sym->name = name; // assumed allocated elsewhere
        sym->value = value;
        sym->next = symtab[h];
        symtab[h] = sym;
    }
    return sym;
}

int main(int argc, char const *argv[])
{
    printf("%d\n", symtab[2] == NULL);
    printf("%d\n", hash("shit"));
    return 0;
}
