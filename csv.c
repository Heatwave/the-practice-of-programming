#include <stdlib.h>
#include <string.h>

#include "csv.h"

enum
{
    NOMEM = -2 // out of memory signal
};

static char *line = NULL;   // input chars
static char *sline = NULL;  // line copy used by split
static int maxline = 0;     // size of line[] and sline[]
static char **field = NULL; // field pointers
static int maxfield = 0;    // size of field[]
static int nfield = 0;      // number of fields in field[]

static char fieldsep[] = ","; // field separator chars

static void reset(void);
static int endofline(FILE *fin, int c);
static int split(void);
static char *advquoted(char *p);

// csvgetline: get one line, grow as needed
// sample input: "LU",86.25,"11/4/1998","2:19PM",+4.0625
char *csvgetline(FILE *fin)
{
    int i, c;
    char *newl, *news;
    if (line == NULL)
    { // allocate on first call
        maxline = maxfield = 1;
        line = (char *)malloc(maxline);
        sline = (char *)malloc(maxline);
        field = (char **)malloc(maxfield * sizeof(field[0]));
        if (line == NULL || sline == NULL || field == NULL)
        {
            reset();
            return NULL; // out of memory
        }
    }
    for (i = 0; (c = getc(fin)) != EOF && !endofline(fin, c); i++)
    {
        if (i >= maxline - 1)
        {                 // grow line
            maxline *= 2; // double current size
            newl = (char *)realloc(line, maxline);
            news = (char *)realloc(sline, maxline);
            if (newl == NULL || news == NULL)
            {
                reset();
                return NULL; // out of memory
            }
            line = newl;
            sline = news;
        }
        line[i] = c;
    }
    line[i] = '\0';
    if (split() == NOMEM)
    {
        reset();
        return NULL; // out of memory
    }
    return (c == EOF && i == 0) ? NULL : line;
}

// reset: set variables back to starting values
static void reset(void)
{
    free(line); // free(NULL) permitted by ANSI C
    free(sline);
    free(field);
    line = NULL;
    sline = NULL;
    field = NULL;
    maxline = maxfield = nfield = 0;
}

// endofline: check for and consume \r, \n, \r\n, or EOF
static int endofline(FILE *fin, int c)
{
    int eol;
    eol = (c == '\r' || c == '\n');
    if (c == '\r')
    {
        c = getc(fin);
        if (c != '\n' && c != EOF)
            ungetc(c, fin); // read too far; put c back
    }
    return eol;
}

// split: split line into fields
static int split(void)
{
    char *p, **newf;
    char *sepp; // pointer to temporary separator character
    int spec;   // temporary separator character

    nfield = 0;
    if (line[0] == '\0')
        return 0;
    strcpy(sline, line);
    p = sline;

    do
    {
        if (nfield >= maxfield)
        {
            maxfield *= 2; // double current size
            newf = (char **)realloc(field, maxfield * sizeof(field[0]));
            if (newf == NULL)
                return NOMEM;
            field = newf;
        }
        if (*p == '"')
            sepp = advquoted(++p); // skip initial quote
        else
            sepp = p + strcspn(p, fieldsep);
        spec = sepp[0];
        sepp[0] = '\0'; // terminate field
        field[nfield++] = p;
        p = sepp + 1;
    } while (spec == ',');
    return nfield;
}

// advquoted: quoted field; return pointer to next separator
static char *advquoted(char *p)
{
    int i, j;
    for (i = j = 0; p[j] != '\0'; i++, j++)
    {
        if (p[j] == '"' && p[++j] != '"')
        {
            // copy up to next separator or \0
            int k = strcspn(p + j, fieldsep);
            memmove(p + i, p + j, k);
            i += k;
            j += k;
            break;
        }
        p[i] = p[j];
    }
    p[i] = '\0';
    return p + j;
}

// csvfield: return pointer to n-th field
char *csvfield(int n)
{
    if (n < 0 || n >= nfield)
        return NULL;
    return field[n];
}

// csvnfield: return number of fields
int csvnfield(void)
{
    return nfield;
}

// csvtest main: test CSV library
int main(int argc, char const *argv[])
{
    int i;
    char *line;
    while ((line = csvgetline(stdin)) != NULL)
    {
        printf("line = '%s'\n", line);
        for (i = 0; i < csvnfield(); i++)
            printf("field[%d] = '%s'\n", i, csvfield(i));
    }
    printf("%d %s\n", csvnfield(), csvfield(0));
    return 0;
}
