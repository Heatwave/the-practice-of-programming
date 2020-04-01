#include <string.h>
#include <stdio.h>

typedef struct Namevel Namevel;
struct Namevel
{
    char *name;
    int value;
};

/* lookup: binary search for name in tab; return index */
int lookup(char *name, Namevel tab[], int ntab)
{
    int low, high, mid, cmp;
    low = 0;
    high = ntab - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        cmp = strcmp(name, tab[mid].name);
        if (cmp < 0)
            high = mid - 1;
        else if (cmp > 0)
            low = mid + 1;
        else /* found match */
            return mid;
    }
    return -1; /* no match */
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
