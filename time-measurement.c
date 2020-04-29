#include <time.h>
#include <stdio.h>

void long_running_function()
{
    size_t sum = 0;
    for (size_t i = 0; i < 1024 * 1024; ++i)
    {
        sum += i;
    }
}

void short_running_function()
{
    size_t sum = 0;
    for (size_t i = 0; i < 1024; ++i)
    {
        sum += i;
    }
}

int main()
{
    clock_t before;
    double elapsed;

    before = clock();
    long_running_function();
    elapsed = clock() - before;
    printf("long_running_function used %.3f seconds\n", elapsed / CLOCKS_PER_SEC);

    before = clock();
    int i = 0;
    for (i = 0; i < 1000; i++)
    {
        short_running_function();
    }
    elapsed = (clock() - before) / (double)i;
    printf("short_running_function used %.3f seconds\n", elapsed / CLOCKS_PER_SEC);
    return 0;
}
