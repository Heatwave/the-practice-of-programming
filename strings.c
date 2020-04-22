#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MINLEN 100

static char *name = NULL; // program name ofr messages

/* setprogname: set stored name of program */
void setprogname(char *str)
{
    name = strdup(str);
}

/* strings: extract printable strings from stream */
void strings(char *name, FILE *fin)
{
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
        if (i >= MINLEN) /* print if long enough */
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
        printf("usage: strings filenames");
    else
    {
        for (i = 1; i < argc; i++)
        {
            if ((fin = fopen(argv[i], "rb")) == NULL)
                printf("can't open %s:", argv[i]);
            else
            {
                strings(argv[i], fin);
                fclose(fin);
            }
        }
    }
    return 0;
}
