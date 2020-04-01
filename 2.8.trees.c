#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Namevel Namevel;
struct Namevel
{
    char *name;
    int value;
    Namevel *left;  // lesser
    Namevel *right; // greater
};

// insert: insert newp in treep, return treep
Namevel *insert(Namevel *treep, Namevel *newp)
{
    int cmp;
    if (treep == NULL)
        return newp;
    cmp = strcmp(newp->name, treep->name);
    if (cmp == 0)
    {
        printf("insert: duplicate entry %s ignored", newp->name);
        return NULL;
    }
    else if (cmp < 0)
    {
        treep->left = insert(treep->left, newp);
    }
    else
    {
        treep->right = insert(treep->right, newp);
    }
    return treep;
}

// lookup: look up name in tree treep
Namevel *lookup(Namevel *treep, char *name)
{
    int cmp;
    if (treep == NULL)
        return NULL;
    cmp = strcmp(name, treep->name);
    if (cmp == 0)
        return treep;
    else if (cmp < 0)
        return lookup(treep->left, name);
    else
        return lookup(treep->right, name);
}

// nrlookup: non-recursively look up name in tree treep
Namevel *nrlookup(Namevel *treep, char *name)
{
    int cmp;
    while (treep != NULL)
    {
        cmp = strcmp(name, treep->name);
        if (cmp == 0)
            return treep;
        else if (cmp < 0)
            treep = treep->left;
        else
            treep = treep->right;
    }
    return NULL;
}

// applyinorder: inorder application of fn to treep
void applyinorder(Namevel *treep, void (*fn)(Namevel *, void *), void *arg)
{
    if (treep == NULL)
        return;
    applyinorder(treep->left, fn, arg);
    (*fn)(treep, arg);
    applyinorder(treep->right, fn, arg);
}

// applypostorder: postorder application of fn to treep
void applypostorder(Namevel *treep, void (*fn)(Namevel *, void *), void *arg)
{
    if (treep == NULL)
        return;
    applypostorder(treep->left, fn, arg);
    applypostorder(treep->right, fn, arg);
    (*fn)(treep, arg);
}

void printree(Namevel *treep, void *arg)
{
    char *fmt = (char *)arg;
    // printf("%s %x\n", treep->name, treep->value);
    printf(fmt, treep->name, treep->value);
}

int main(int argc, char const *argv[])
{
    Namevel *nvtree = malloc(sizeof(Namevel));
    nvtree->name = "b";
    nvtree->value = 1;
    nvtree->left = NULL;
    nvtree->right = NULL;

    Namevel *nvtreeleft = malloc(sizeof(Namevel));
    nvtreeleft->name = "c";
    nvtreeleft->value = 2;
    nvtreeleft->left = NULL;
    nvtreeleft->right = NULL;

    Namevel *nvtreeright = malloc(sizeof(Namevel));
    nvtreeright->name = "a";
    nvtreeright->value = 0;
    nvtreeright->left = NULL;
    nvtreeright->right = NULL;

    nvtree = insert(nvtree, nvtreeleft);
    nvtree = insert(nvtree, nvtreeright);

    applyinorder(nvtree, printree, "%s: %x\n");
    return 0;
}
