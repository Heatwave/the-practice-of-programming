#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int factorial(int n)
{
    int fac;
    fac = 1;
    while (n > 0)
        fac *= n--;
    return fac;
}

void printCharPerLine(char *s)
{
    if (strlen(s) < 1)
        return;

    int i = 0;
    do
    {
        putchar(s[i++]);
        putchar('\n');
    } while (s[i] != '\0');
}

void myStrCpy(char *dest, char *src)
{
    int i;

    for (i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = src[i];
}

void myStrnCpy(char *dest, char *src, int n)
{
    if (n <= 0)
        return;

    while (n > 0 && *src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
        n--;
    }
}

void numericalCompareison(int i, int j)
{
    if (i > j)
        printf("%d is greater than %d.\n", i, j);
    else if (i < j)
        printf("%d is smaller than %d.\n", i, j);
    else
        printf("%d is equal to %d.\n", i, j);
}

void characterClassTest(char c)
{
    c = (char)toupper(c);
    if (c >= 'A' && c <= 'Z')
    {
        if (c <= 'L')
            printf("first half of alphabet\n");
        else
            printf("second half of alphabet\n");
    }
}

int main()
{
    int n = factorial(3);
    printf("%d\n", n);
    n = factorial(0);
    printf("%d\n", n);
    n = factorial(-1);
    printf("%d\n", n);
    n = factorial(99);
    printf("%d\n", n);

    printCharPerLine("123");
    printCharPerLine("");
    printCharPerLine("asdzxcqwe\nasdqwe");

    char *src = "hello world";
    char dest[100];
    myStrCpy(dest, src);
    printf("mystrcpy: %s\n", dest);
    strcpy(dest, src);
    printf("strcpy: %s\n", dest);

    src = "123";
    myStrCpy(dest, src);
    printf("mystrcpy: %s\n", dest);
    strcpy(dest, src);
    printf("strcpy: %s\n", dest);

    src = "";
    myStrCpy(dest, src);
    printf("myStrCpy: %s\n", dest);
    strcpy(dest, src);
    printf("strcpy: %s\n", dest);

    src = "hello";
    myStrnCpy(dest, src, 5);
    printf("myStrnCpy: %s\n", dest);
    strncpy(dest, src, 5);
    printf("strncpy: %s\n", dest);

    characterClassTest('a');
    characterClassTest('Z');
    return 0;
}
