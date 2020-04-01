#include <iostream>
#include <deque>
#include <map>
#include <vector>
using namespace std;

enum
{
    NPREF = 2,     // number of preifx words
    MAXGEN = 10000 // maximum words generated
};

typedef deque<string> Prefix;
map<Prefix, vector<string>> statetab; // preifx -> suffixes

// add: add word to suffix list, update prefix
void add(Prefix &prefix, const string &s)
{
    if (prefix.size() == NPREF)
    {
        statetab[prefix].push_back(s);
        prefix.pop_front();
    }
    prefix.push_back(s);
}

// build: read input words, build state table
void build(Prefix &prefix, istream &in)
{
    string buf;

    while (in >> buf)
        add(prefix, buf);
}

string NOWWORD("\n"); // cannot appear as real word

// generate: produce output, one word per line
void generate(int nwords)
{
    Prefix prefix;
    int i;

    for (i = 0; i < NPREF; i++) // reset initial prefix
        add(prefix, NOWWORD);

    for (i = 0; i < nwords; i++)
    {
        vector<string> &suf = statetab[prefix];
        const string &w = suf[rand() % suf.size()];
        if (w == NOWWORD)
            break;
        cout << w << " ";
        prefix.pop_front(); // advance
        prefix.push_back(w);
    }
}

int main()
{
    int nwords = MAXGEN;
    Prefix prefix; // current input prefix

    for (int i = 0; i < NPREF; i++) // set up initial prefix
        add(prefix, NOWWORD);
    build(prefix, cin);
    add(prefix, NOWWORD);
    generate(nwords);
    return 0;
}
