#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Namevel Namevel;
struct Namevel
{
    char *name;
    int value;
    Namevel *next; // in list
};

// newitem: create new item from name and value
Namevel *newitem(char *name, int value)
{
    Namevel *newp;
    newp = (Namevel *)malloc(sizeof(Namevel));
    newp->name = name;
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

// lookup: sequential search for name in listp
Namevel *lookup(Namevel *listp, char *name)
{
    for (; listp != NULL; listp = listp->next)
        if (strcmp(name, listp->name) == 0)
            return listp;
    return NULL; // no match
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
    printf(fmt, p->name, p->value);
}

// inccounter: increment counter *arg
void inccounter(Namevel *p, void *arg)
{
    int *ip;
    // p is unused
    ip = (int *)arg;
    (*ip)++;
}

// freeall: free all elements of listp
void freeall(Namevel *listp)
{
    Namevel *next;
    for (; listp != NULL; listp = next)
    {
        next = listp->next;
        // assumes name is freed elsewhere
        free(listp);
    }
}

// delitem: delete first "name" from listp
Namevel *delitem(Namevel *listp, char *name)
{
    Namevel *p, *prev;
    prev = NULL;
    for (p = listp; p != NULL; p = p->next)
    {
        if (strcmp(name, p->name) == 0)
        {
            if (prev == NULL)
                listp = p->next;
            else
                prev->next = p->next;
            free(p);
            return listp;
        }
        prev = p;
    }
    printf("delitem: %s not in list", name);
    return NULL;
}

Namevel *copy(Namevel *listp)
{
    Namevel *newp = NULL;
    for (; listp != NULL; listp = listp->next)
        newp = addend(newp, newitem(listp->name, listp->value));

    return newp;
}

Namevel *merge(Namevel *listp, Namevel *newp)
{
    listp = addend(listp, newp);
    return listp;
}

Namevel *split(Namevel **listp, int point)
{
    Namevel *p = *listp, *prev = *listp;
    if (point == 0)
    {
        *listp = NULL;
        return p;
    }
    while (point > 0 && p != NULL)
    {
        prev = p;
        p = p->next;
        point--;
    }
    prev->next = NULL;
    return p;
}

Namevel *insertbefore(Namevel *listp, Namevel *newp, char *name)
{
    Namevel *p, *prev;
    prev = NULL;
    for (p = listp; p != NULL; p = p->next)
    {
        if (strcmp(name, p->name) == 0)
        {
            if (prev == NULL)
                listp = addfront(listp, newp);
            else
            {
                prev->next = newp;
                newp->next = p;
            }
            return listp;
        }
        prev = p;
    }
    printf("insertbefore: %s not in list", name);
    return NULL;
}

Namevel *insertafter(Namevel *listp, Namevel *newp, char *name)
{
    Namevel *p;
    for (p = listp; p != NULL; p = p->next)
    {
        if (strcmp(name, p->name) == 0)
        {
            if (p->next == NULL)
                listp = addend(listp, newp);
            else
            {
                newp->next = p->next;
                p->next = newp;
            }
            return listp;
        }
    }
    printf("insertafter: %s not in list", name);
    return NULL;
}

Namevel *reverserecursive(Namevel *prev, Namevel *listp)
{
    if (listp == NULL)
        return prev;
    Namevel *next = listp->next;
    listp->next = prev;
    return reverserecursive(listp, next);
}

Namevel *reverse(Namevel *listp)
{
    if (listp == NULL || listp->next == NULL)
        return listp;
    Namevel *p = reverse(listp->next);
    listp->next->next = listp;
    listp->next = NULL;
    return p;
}

Namevel *reverseiteratively(Namevel *listp)
{
    Namevel *prev = NULL;
    while (listp != NULL)
    {
        Namevel *next = listp->next;
        listp->next = prev;
        prev = listp;
        listp = next;
    }
    return prev;
}

int main(int argc, char const *argv[])
{
    Namevel *nvlist = newitem("abc", 0);
    nvlist = addend(nvlist, newitem("def", 1));
    apply(nvlist, printnv, "%s: %x\n");

    int n = 0;
    apply(nvlist, inccounter, &n);
    printf("%d elements in nvlist\n", n);

    Namevel *newlist = copy(nvlist);
    apply(newlist, printnv, "%s: %x\n");

    nvlist = delitem(nvlist, "abc");
    apply(nvlist, printnv, "%s: %x\n");

    n = 0;
    apply(nvlist, inccounter, &n);
    printf("%d elements in nvlist\n", n);

    nvlist = merge(nvlist, newlist);
    apply(nvlist, printnv, "%s: %x\n");

    n = 0;
    apply(nvlist, inccounter, &n);
    printf("%d elements in nvlist\n", n);

    Namevel *splitlist = split(&nvlist, 2);
    printf("nvlist: \n");
    apply(nvlist, printnv, "%s: %x\n");
    printf("splitlist: \n");
    apply(splitlist, printnv, "%s: %x\n");

    nvlist = insertbefore(nvlist, newitem("ghi", 2), "def");
    printf("nvlist: \n");
    apply(nvlist, printnv, "%s: %x\n");

    nvlist = insertafter(nvlist, newitem("jkl", 3), "abc");
    printf("nvlist: \n");
    apply(nvlist, printnv, "%s: %x\n");

    nvlist = reverse(nvlist);
    printf("nvlist after reverse: \n");
    apply(nvlist, printnv, "%s: %x\n");

    nvlist = reverseiteratively(nvlist);
    printf("nvlist after reverseiteratively: \n");
    apply(nvlist, printnv, "%s: %x\n");

    freeall(newlist);
    freeall(nvlist);
    return 0;
}
