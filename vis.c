#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int showHexadecimal = 0;

    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            showHexadecimal = 1;
        }
    }

    int c;

    while ((c = getchar()) != EOF)
    {
        if (showHexadecimal && (c <= 32 || c > 126))
            printf("\\X%X", c);
        else
            putchar(c);
    }

    return 0;
}
