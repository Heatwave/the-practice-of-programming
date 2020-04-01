#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Namevel Namevel;
struct Namevel
{
    void *value;
    Namevel *next; // in list
};

// newitem: create new item from name and value
Namevel *newitem(void *value)
{
    Namevel *newp;
    newp = (Namevel *)malloc(sizeof(Namevel));
    newp->value = value;
    newp->next = NULL;
    return newp;
}

// addfront: add newp to front of listp
Namevel *addfront(Namevel *listp, Namevel *newp)
{
    newp->next = listp;
    return newp;
}

// addend: add newp to end of listp
Namevel *addend(Namevel *listp, Namevel *newp)
{
    Namevel *p;

    if (listp == NULL)
        return newp;
    for (p = listp; p->next != NULL; p = p->next)
        ;
    p->next = newp;
    return listp;
}

// apply: execute fn for each element of listp
void apply(Namevel *listp, void (*fn)(Namevel *, void *), void *arg)
{
    for (; listp != NULL; listp = listp->next)
        (*fn)(listp, arg); // call the function
}

// printnv: print the name and value using format in arg
void printnv(Namevel *p, void *arg)
{
    char *fmt;

    fmt = (char *)arg;
    printf(fmt, p->value);
}

int main(int argc, char const *argv[])
{
    Namevel *nvlist = newitem((void *)0);

    printf("%d\n", nvlist->value);

    nvlist = addend(nvlist, newitem((void *)1));
    nvlist = addfront(nvlist, newitem((void *)2));
    apply(nvlist, printnv, "%x\n");
    return 0;
}
