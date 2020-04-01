#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Namevel Namevel;
struct Namevel
{
    char *name;
    int value;
};

struct NVtab
{
    int nval;         // current number of values
    int max;          // allocated number of values
    Namevel *namevel; // array of name-value pairs
} nvtab;

enum
{
    NVINIT = 1,
    NVGROW = 2
};

// addname: add new name and value to nvtab
int addname(Namevel newname)
{
    Namevel *nvp;
    if (nvtab.namevel == NULL) // first time
    {
        nvtab.namevel = (Namevel *)malloc(NVINIT * sizeof(Namevel));
        if (nvtab.namevel == NULL)
            return -1;
        nvtab.max = NVINIT;
        nvtab.nval = 0;
    }
    else if (nvtab.nval >= nvtab.max) // grow
    {
        nvp = (Namevel *)realloc(nvtab.namevel, (NVGROW * nvtab.max) * sizeof(Namevel));
        if (nvp == NULL)
            return -1;
        nvtab.max *= NVGROW;
        nvtab.namevel = nvp;
    }
    nvtab.namevel[nvtab.nval] = newname;
    return nvtab.nval++;
}

// delname: remove first matching nameval from nvtab
int delname(char *name)
{
    int i;
    for (i = 0; i < nvtab.nval; i++)
    {
        if (strcmp(nvtab.namevel[i].name, name) == 0)
        {
            memmove(nvtab.namevel + i, nvtab.namevel + i + 1, (nvtab.nval - (i + 1)) * sizeof(Namevel));
            nvtab.nval--;
            return 1;
        }
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    Namevel nv;
    nv.name = "abc";
    nv.value = 1;
    addname(nv);
    nv.name = "def";
    nv.value = 2;
    addname(nv);
    nv.name = "ghi";
    nv.value = 3;
    addname(nv);
    printf("%s %d\n", nvtab.namevel->name, nvtab.namevel->value);
    printf("%s %d\n", nvtab.namevel[1].name, nvtab.namevel[1].value);
    printf("%s %d\n", nvtab.namevel[2].name, nvtab.namevel[2].value);
    printf("nval: %d max: %d\n", nvtab.nval, nvtab.max);
    delname("abc");
    printf("nval: %d max: %d\n", nvtab.nval, nvtab.max);
    return 0;
}
