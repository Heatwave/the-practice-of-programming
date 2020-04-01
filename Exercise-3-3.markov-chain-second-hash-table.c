#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

enum
{
    NPREF = 2,     // number of preifx words
    NHASH = 8192,  // size of state hash table array
    MAXGEN = 10000 // maximum words generated
};

enum
{
    MULTIPLIER = 31
};

typedef struct Word Word;
struct Word
{
    char *word;
    Word *next;
};
Word *wordstab[NHASH]; // hash table of words

// hash: compute hash value of string
unsigned int hashword(char *str)
{
    unsigned int h;
    unsigned char *p;
    h = 0;
    for (p = (unsigned char *)str; *p != '\0'; p++)
        h = MULTIPLIER * h + *p;
    return h % NHASH;
}

// lookup: find word in wordstab, with optional create
Word *lookupword(char *word, int create)
{
    int h;
    Word *wordp;

    h = hashword(word);
    for (wordp = wordstab[h]; wordp != NULL; wordp = wordp->next)
        if (strcmp(word, wordp->word) == 0)
            return wordp;
    if (create)
    {
        wordp = (Word *)malloc(sizeof(Word));
        wordp->word = word; // assumed allocated elsewhere
        wordp->next = wordstab[h];
        wordstab[h] = wordp;
    }
    return wordp;
}

typedef struct State State;
typedef struct Suffix Suffix;
struct State // prefix + suffix list
{
    Word *pref[NPREF]; // prefix words
    Suffix *suf;       // list of suffixes
    State *next;       // next in hash table
};
struct Suffix // list of suffixes
{
    Word *word;   // suffix
    Suffix *next; // next in list of suffixes
};
State *statetab[NHASH]; // hash table of states

// hash: compute hash value for array of NPREF strings
unsigned int hash(Word *s[NPREF])
{
    unsigned int h;
    unsigned char *p;
    int i;

    h = 0;
    for (i = 0; i < NPREF; i++)
        for (p = (unsigned char *)s[i]->word; *p != '\0'; p++)
            h = MULTIPLIER * h + *p;
    return h % NHASH;
}

// lookup: search for prefix; create if requested.
// returns pointer if present or created; NULL if not.
// creation doesn't strdup so strings mustn't change later.
State *lookup(Word *prefix[NPREF], int create)
{
    int i, h;
    State *sp = NULL;

    h = hash(prefix);
    for (sp = statetab[h]; sp != NULL; sp = sp->next)
    {
        for (i = 0; i < NPREF; i++)
            if (prefix[i] != sp->pref[i])
                break;
        if (i == NPREF) // found it
            return sp;
    }
    if (create)
    {
        sp = (State *)malloc(sizeof(State));
        for (i = 0; i < NPREF; i++)
            sp->pref[i] = lookupword(prefix[i]->word, 1);
        sp->suf = NULL;
        sp->next = statetab[h];
        statetab[h] = sp;
    }
    return sp;
}

// addsuffix: add to state. suffix must not change later
void addsuffix(State *sp, Word *suffixword)
{
    Suffix *suf;
    suf = (Suffix *)malloc(sizeof(Suffix));
    suf->word = suffixword;
    suf->next = sp->suf;
    sp->suf = suf;
}

// add: add word to suffix list, update prefix
void add(Word *prefix[NPREF], char *suffix)
{
    State *sp;
    sp = lookup(prefix, 1); // create if not found
    Word *suffixword = lookupword(suffix, 1);
    addsuffix(sp, suffixword);
    // move the words down the prefix
    memmove(prefix, prefix + 1, (NPREF - 1) * sizeof(prefix[0]));
    prefix[NPREF - 1] = suffixword;
}

// build: read input, build prefix table
void build(Word *prefix[NPREF], FILE *f)
{
    char buf[100], fmt[10];
    // create a format string; %s could overflow buf
    sprintf(fmt, "%%%ds", sizeof(buf) - 1);
    while (fscanf(f, fmt, buf) != EOF)
        add(prefix, strdup(buf));
}

char NOWWORD[] = "\n"; // cannot appear as real word

// generate: produce output
void generate(int nwords)
{
    State *sp;
    Suffix *suf;
    Word *prefix[NPREF], *w;
    int i, nmatch;

    for (i = 0; i < NPREF; i++) // reset initial prefix
        prefix[i] = lookupword(NOWWORD, 1);

    for (i = 0; i < nwords; i++)
    {
        sp = lookup(prefix, 0);
        nmatch = 0;
        for (suf = sp->suf; suf != NULL; suf = suf->next)
            if (rand() % ++nmatch == 0) // probability = 1/nmatch
                w = suf->word;
        if (strcmp(w->word, NOWWORD) == 0)
            break;
        printf("%s ", w->word);
        memmove(prefix, prefix + 1, (NPREF - 1) * sizeof(prefix[0]));
        prefix[NPREF - 1] = w;
    }
}

// markov main: markov-chain random text generation
int main(int argc, char const *argv[])
{
    clock_t t;
    t = clock();

    int i, nwords = MAXGEN;
    Word *prefix[NPREF]; // current input prefix

    for (i = 0; i < NPREF; i++) // set up initial prefix
        prefix[i] = lookupword(NOWWORD, 1);
    build(prefix, stdin);
    add(prefix, NOWWORD);
    generate(nwords);

    t = clock() - t;
    printf("\nIt took %d clocks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);

    return 0;
}
