#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void memsetTest()
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

                memset(s0 + offset[j], c[i], sizeof(char) * n[k]);

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
    memsetTest();
    return 0;
}
