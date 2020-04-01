#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

/* scmp: string compare of *p1 and *p2 */
int scmp(const void *p1, const void *p2)
{
    char *v1, *v2;

    v1 = *(char **)p1;
    v2 = *(char **)p2;
    return strcmp(v1, v2);
}

int main(int argc, char const *argv[])
{
    char *str[N] = {"int", "scmp", "const", "void", "p", "q", "char", "v", "return", "strcmp"};
    qsort(str, N, sizeof(str[0]), scmp);

    for (size_t i = 0; i < N; i++)
        printf("%s ", str[i]);
    return 0;
}
