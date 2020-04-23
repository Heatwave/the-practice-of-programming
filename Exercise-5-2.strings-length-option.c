#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "eprintf.h"

#define DEFAULT_MINLEN 4

/* strings: extract printable strings from stream */
void strings(char *name, FILE *fin, int minLen)
{
    if (minLen < 0)
        minLen = DEFAULT_MINLEN;

    int c, i;
    char buf[BUFSIZ];

    do
    {
        for (i = 0; (c = getc(fin)) != EOF;)
        {
            if (!isprint(c))
                break;
            buf[i++] = c;
            if (i >= BUFSIZ)
                break;
        }
        if (i >= minLen) /* print if long enough */
            printf("%s:%.*s\n", name, i, buf);
    } while (c != EOF);
}

/* strings main: find printable strings in files */
int main(int argc, char *argv[])
{
    int i;
    FILE *fin;
    setprogname("strings");
    if (argc == 1)
        eprintf("usage: strings [-l (min length)] filenames");
    else
    {
        int minLen = -1;
        i = 1;
        if (strcmp(argv[i], "-l") == 0)
        {
            ++i;
            minLen = atoi(argv[i]);
            ++i;
        }
        for (; i < argc; i++)
        {
            if ((fin = fopen(argv[i], "rb")) == NULL)
                weprintf("can't open %s:", argv[i]);
            else
            {
                strings(argv[i], fin, minLen);
                fclose(fin);
            }
        }
    }
    return 0;
}
