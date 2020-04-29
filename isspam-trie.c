#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

#define NPAT 6      // existing patterns
#define NSTART 1024 // max of patterns begin with the same two characters

char *pat[NPAT];  // patterns
int patlen[NPAT]; // length of pattern

typedef struct Trie Trie;
struct Trie
{
    int patterns[NSTART];
    size_t patternSize;
    Trie *children[UCHAR_MAX + 1];
};

Trie *initTrie()
{
    Trie *trie = (Trie *)malloc(sizeof(Trie));
    trie->patternSize = 0;

    for (int i = 0; i < UCHAR_MAX + 1; ++i)
    {
        trie->children[i] = NULL;
    }

    return trie;
}

Trie *buildPatternTrie()
{
    Trie *trie = initTrie();

    unsigned char c0, c1;
    for (int i = 0; i < NPAT; ++i)
    {
        c0 = tolower(pat[i][0]);
        c1 = tolower(pat[i][1]);

        Trie *child = NULL;
        if (trie->children[c0] == NULL)
        {
            child = initTrie();
            trie->children[c0] = child;
        }

        if (trie->children[c0]->children[c1] == NULL)
        {
            child = initTrie();
            trie->children[c0]->children[c1] = child;
        }

        child = trie->children[c0]->children[c1];
        child->patterns[child->patternSize++] = i;
    }

    return trie;
}

// isspam: test mesg for occurrence of any pat
int isspam(Trie *trie, char *mesg)
{
    int j, k;
    unsigned char c0;
    unsigned char c1;

    for (j = 0; (c0 = tolower(mesg[j])) != '\0' && (c1 = tolower(mesg[j + 1])) != '\0'; j++)
    {
        if (trie->children[c0] != NULL && trie->children[c0]->children[c1] != NULL)
        {
            Trie *child = trie->children[c0]->children[c1];
            for (size_t i = 0; i < child->patternSize; ++i)
            {
                k = child->patterns[i];
                if (memcmp(mesg + j, pat[k], patlen[k]) == 0)
                {
                    printf("spam: match for '%s'\n", pat[k]);
                    return 1;
                }
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
    pat[3] = "Pretty girls";
    pat[4] = "beautiful woman";
    pat[5] = "big boob";

    Trie *trie = buildPatternTrie();

    char *mesg = "buy! now!";
    printf("'%s' is spam? %s\n", mesg, isspam(trie, mesg) == 1 ? "yes" : "no");

    mesg = "there are lots of pRetty girls, come on!";
    printf("'%s' is spam? %s\n", mesg, isspam(trie, mesg) == 1 ? "yes" : "no");

    mesg = "TOP secret";
    printf("'%s' is spam? %s\n", mesg, isspam(trie, mesg) == 1 ? "yes" : "no");
    return 0;
}
