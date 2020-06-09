#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const size_t COUNT = 10000000;

#define LOOP(CODE)                      \
    {                                   \
        t0 = clock();                   \
        for (i = 0; i < COUNT; i++)     \
        {                               \
            CODE;                       \
        }                               \
        printf("%7lu\n", clock() - t0); \
    }

int main()
{
    clock_t t0;
    int i;

    int j = 0;
    LOOP(j++)

    j = 0;
    LOOP(++j)

    int i1 = 0, i2 = 1, i3 = 2;
    LOOP(i1 = i2 + i3)

    LOOP(i1 = i3 - i2)

    LOOP(i1 = i2 * i3)

    LOOP(i1 = i3 / i2)

    LOOP(i1 = i3 % i2)

    LOOP(free(malloc(sizeof(int))))

    return 0;
}
