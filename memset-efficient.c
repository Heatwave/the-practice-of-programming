#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

void *memset_simple(void *ptr, int value, size_t num)
{
    size_t i;
    char *p;
    p = (char *)ptr;
    for (i = 0; i < num; i++)
        p[i] = value;
    return ptr;
}

void *memset_efficient(void *ptr, int value, size_t num)
{
    size_t i;
    char *p;
    p = (char *)ptr;
    for (i = 0; i + 4 < num; i += 4)
    {
        p[i] = value;
        p[i + 1] = value;
        p[i + 2] = value;
        p[i + 3] = value;
    }
    if (i < num)
    {
        for (; i < num; ++i)
        {
            p[i] = value;
        }
    }
    return ptr;
}

void *memset_wordsize(void *ptr, int value, size_t num)
{
    int *p = (int *)ptr;

    value = value & 0xFF;

    int leftShift = sizeof(int) * 2;

    int res;

    size_t intSize = num / sizeof(int);
    size_t shiftCount = sizeof(int) / sizeof(char) - 1;
    size_t i;
    for (i = 0; i < intSize; ++i)
    {
        res = value;
        for (int j = 0; j < shiftCount; ++j)
            res = (res << leftShift) + value;
        *(p + i) = res;
    }
    if (i < num)
    {
        char *pc = (char *)ptr;
        for (; i < num; ++i)
            pc[i] = value;
    }

    return ptr;
}

void memset_test(void *(*fn)(void *, int, size_t))
{
    int big = 1024 * 256;
    char *s0 = (char *)malloc(sizeof(char) * big);
    char *s1 = (char *)malloc(sizeof(char) * big);

    int offset[30];
    for (int i = 0; i < 30; ++i)
    {
        offset[i] = i;
    }

    int c[6] = {0, 1, 0x7F, 0x80, 0xFF, 0x11223344};

    int n[49];
    int nPos = 0;
    n[nPos++] = 0;

    for (int i = 1; i <= 16; ++i)
    {
        int base = 2;
        int power = i - 1;
        while (power-- > 0)
            base *= 2;

        n[nPos++] = base - 1;
        n[nPos++] = base;
        n[nPos++] = base + 1;
    }

    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 30; ++j)
        {
            for (int k = 0; k < 49; ++k)
            {
                // printf("i: %d\tj: %d\tk: %d\n", i, j, k);
                int val = 0;
                if (c[i] == 0)
                    val = 1;

                for (int sPos = 0; sPos < big; ++sPos)
                {
                    s0[sPos] = val;
                }
                for (int sPos = 0; sPos < big; ++sPos)
                {
                    if (sPos >= offset[j] && sPos < (offset[j] + n[k]) && n[k] > 0)
                        s1[sPos] = c[i];
                    else
                        s1[sPos] = val;
                }

                fn(s0 + offset[j], c[i], sizeof(char) * n[k]);

                for (int sPos = 0; sPos < big; ++sPos)
                {
                    // printf("c[%d]: %d\toffset[%d]: %d\tn[%d]: %d\ts0[%d]: %d\ts1[%d]: %d\n", i, c[i], j, offset[j], k, n[k], sPos, s0[sPos], sPos, s1[sPos]);
                    assert(s0[sPos] == s1[sPos]);
                }
            }
        }
    }
}

int main()
{
    const int SIZE = 1234;
    char *s = (char *)malloc(sizeof(char) * SIZE);

    for (int i = 0; i < SIZE; ++i)
        s[i] = 1;

    char val = 0x1;

    memset_wordsize(s + 20, val, 512);

    for (int i = 0; i < SIZE; ++i)
    {
        if (i < 20)
            assert(s[i] == 1);
        else if (i < 512 + 20)
            assert(s[i] == val);
        else
            assert(s[i] == 1);
    }

    // const int n = 20;
    // char test[n] = {0};
    // for (int i = 0; i < n; ++i)
    //     printf("test[%d]: %d\t%X\n", i, test[i], test[i]);
    // memset_wordsize(test, 287454020, sizeof(char) * n);
    // for (int i = 0; i < n; ++i)
    //     printf("test[%d]: %d\t%X\n", i, test[i], test[i]);

    clock_t before;
    double elapsed;

    before = clock();
    memset_test(memset_simple);
    elapsed = clock() - before;
    printf("memset_simple used %.3f seconds\n", elapsed / CLOCKS_PER_SEC);

    before = clock();
    memset_test(memset_efficient);
    elapsed = clock() - before;
    printf("memset_efficient used %.3f seconds\n", elapsed / CLOCKS_PER_SEC);

    before = clock();
    memset_test(memset_wordsize);
    elapsed = clock() - before;
    printf("memset_wordsize used %.3f seconds\n", elapsed / CLOCKS_PER_SEC);

    before = clock();
    memset_test(memset);
    elapsed = clock() - before;
    printf("memset used %.3f seconds\n", elapsed / CLOCKS_PER_SEC);

    return 0;
}
