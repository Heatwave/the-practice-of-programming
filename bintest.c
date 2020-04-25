#include <stdio.h>
#include <stdlib.h>

#define MyType int

int compareMyType(const void *a, const void *b)
{
    if (*(MyType *)a < *(MyType *)b)
        return -1;
    if (*(MyType *)a > *(MyType *)b)
        return 1;
    return 0;
}

int main()
{
    int i, key, nelem, arr[1000];
    while (scanf("%d %d", &key, &nelem) != EOF)
    {
        for (i = 0; i < nelem; i++)
            arr[i] = 2 * i + 1;
        int *res = bsearch(&key, arr, nelem, sizeof(int), compareMyType);
        printf("%d\n", *res);
    }
    return 0;
}
