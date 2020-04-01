#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Namevel Namevel;
struct Namevel
{
    char *name;
    int value;
};

/* nvcmp: compare two Nameval names */
int nvcmp(const void *va, const void *vb)
{
    const Namevel *a, *b;

    a = (Namevel *)va;
    b = (Namevel *)vb;
    return strcmp(a->name, b->name);
}

/* lookup: use bsearch to find name in tab; return index */
int lookup(char *name, Namevel tab[], int ntab)
{
    Namevel key, *np;

    key.name = name;
    key.value = 0; /* unused; anything will do */
    np = (Namevel *)bsearch(&key, tab, ntab, sizeof(tab[0]), nvcmp);

    if (np == NULL)
        return -1;
    else
        return np - tab;
}

int main()
{
    Namevel htmlchars[] = {
        "AElig",
        0x00c6,
        "Aacute",
        0x00c1,
        "Acirc",
        0x00c2,
        "Zeta",
        0x03b6,
    };

    int index = lookup("Acirc", htmlchars, 4);
    printf("Acirc index: %d\n", index);

    index = lookup("Abcd", htmlchars, 4);
    printf("Abcd index: %d", index);

    return 0;
}
