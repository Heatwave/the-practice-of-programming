#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "eprintf.h"

int match(char *regexp, char *text);
int matchhere(char *regexp, char *text);
int matchstar(int c, char *regexp, char *text);

// match: search for regexp anywhere in text
int match(char *regexp, char *text)
{
    if (regexp[0] == '^')
        return matchhere(regexp + 1, text);
    do
    { // must look even if string is empty
        if (matchhere(regexp, text))
            return 1;
    } while (*text++ != '\0');
    return 0;
}

// matchhere: search for regexp at beginning of text
int matchhere(char *regexp, char *text)
{
    if (regexp[0] == '\0')
        return 1;
    if (regexp[1] == '*')
        return matchstar(regexp[0], regexp + 2, text);
    if (regexp[0] == '$' && regexp[1] == '\0')
        return *text == '\0';
    if (*text != '\0' && (regexp[0] == '.' || regexp[0] == *text))
        return matchhere(regexp + 1, text + 1);
    return 0;
}

// matchstar: search for c*regexp at beginning of text
int matchstar(int c, char *regexp, char *text)
{
    do
    { // a * matches zero or more instances
        if (matchhere(regexp, text))
            return 1;
    } while (*text != '\0' && (*text++ == c || c == '.'));

    // leftmost longest search for c*regexp
    // char *t;
    // for (t = text; *t != '\0' && (*t == c || c == '.'); t++)
    //     ;
    // do
    // { // matches zero or more
    //     if (matchhere(regexp, t))
    //         return 1;
    // } while (t-- > text);
    return 0;
}

// grep: search for regexp in file
int grep(char *regexp, FILE *f, char *name)
{
    int n, nmatch;
    char buf[BUFSIZ];

    nmatch = 0;
    while (fgets(buf, sizeof buf, f) != NULL)
    {
        n = strlen(buf);
        if (n > 0 && buf[n - 1] == '\n')
            buf[n - 1] = '\0';
        if (match(regexp, buf))
        {
            nmatch++;
            if (name != NULL)
                printf("%s:", name);
            printf("%s\n", buf);
        }
    }
    return nmatch;
}

// grep main: search for regexp in files
int main(int argc, char *argv[])
{
    int i, nmatch;
    FILE *f;
    setprogname("grep");
    if (argc < 2)
        eprintf("usage: grep regexp [file ...]");
    nmatch = 0;
    if (argc == 2)
    {
        if (grep(argv[1], stdin, NULL))
            nmatch++;
    }
    else
    {
        for (i = 2; i < argc; i++)
        {
            f = fopen(argv[i], "r");
            if (f == NULL)
            {
                weprintf("can't open %s:", argv[i]);
                continue;
            }
            if (grep(argv[1], f, argc > 3 ? argv[i] : NULL) > 0)
                nmatch++;
            fclose(f);
        }
    }
    return nmatch == 0;
}