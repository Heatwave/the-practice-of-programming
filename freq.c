#include <stdio.h>
#include <ctype.h>
#include <limits.h>

unsigned long count[UCHAR_MAX + 1];

/* freq main: display byte frequency counts */
void freq()
{
    int c;
    while ((c = getchar()) != EOF)
        count[c]++;
    for (c = 0; c <= UCHAR_MAX; ++c)
        if (count[c] != 0)
            printf("%.2x %c %lu\n", c, isprint(c) ? c : '-', count[c]);
}

int main()
{
    freq();
    return 0;
}
