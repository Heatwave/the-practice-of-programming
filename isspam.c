#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "eprintf.h"

#define NPAT 6
#define NSTART 1024

char *pat[NPAT];                     // patterns
int patlen[NPAT];                    // length of pattern
int starting[UCHAR_MAX + 1][NSTART]; // pats starting with char
int nstarting[UCHAR_MAX + 1];        // number of such patterns

void buildStructures()
{
    int i;
    unsigned char c;
    for (i = 0; i < NPAT; i++)
    {
        c = pat[i][0];
        if (nstarting[c] >= NSTART)
            eprintf("too many patterns (>=%d) begin '%c'", NSTART, c);
        starting[c][nstarting[c]++] = i;
        patlen[i] = strlen(pat[i]);
    }
}

// isspam: test mesg for occurrence of any pat
int isspam(char *mesg)
{
    int i, j, k;
    unsigned char c;

    for (j = 0; (c = mesg[j]) != '\0'; j++)
    {
        for (i = 0; i < nstarting[c]; i++)
        {
            k = starting[c][i];
            if (memcmp(mesg + j, pat[k], patlen[k]) == 0)
            {
                printf("spam: match for '%s'\n", pat[k]);
                return 1;
            }
        }
    }
    return 0;
}

int main()
{
    pat[0] = "buy!";
    pat[1] = "big bucks";
    pat[2] = "best pictures";
    pat[3] = "pretty girls";
    pat[4] = "beautiful woman";
    pat[5] = "big boob";

    buildStructures();

    // for (int i = 0; i < UCHAR_MAX; ++i)
    // {
    //     if (nstarting[i] > 0)
    //         printf("nstarting[%d]: %d\n", i, nstarting[i]);
    // }

    char *mesg = "buy! now!";
    printf("'%s' is spam? %s\n", mesg, isspam(mesg) == 1 ? "yes" : "no");
    return 0;
}
