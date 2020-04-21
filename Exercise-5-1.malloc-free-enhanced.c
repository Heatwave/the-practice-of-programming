#include <stdio.h>
#include <stdlib.h>

static size_t mallocCount = 0;

void *mallocEnhanced(size_t size)
{
    printf("(mallocEnhanced): allocate %zu memory\n", size);
    mallocCount += 1;
    return malloc(size);
}

void freeEnhanced(void *data)
{
    printf("(freeEnhanced): free memory on address %p\n", data);
    mallocCount -= 1;
    free(data);
}

int main()
{
    int *i = (int *)mallocEnhanced(sizeof(int));
    freeEnhanced(i);
    int *j = (int *)mallocEnhanced(sizeof(int));
    *j = 1;
    if (mallocCount > 0)
        printf("memory leaked!\n");
    return 0;
}
