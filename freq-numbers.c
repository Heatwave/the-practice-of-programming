#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define IN 1
#define OUT 0

typedef struct IntegerList IntegerList;

struct IntegerList
{
    int data;
    size_t count;
    IntegerList *next;
};

typedef struct FloatList FloatList;

struct FloatList
{
    double data;
    size_t count;
    FloatList *next;
};

IntegerList *appendToIntegerList(IntegerList *list, int num)
{
    IntegerList *p, *pre;
    p = pre = list;

    while (p != NULL)
    {
        if (p->data == num)
        {
            p->count += 1;
            return list;
        }
        pre = p;
        p = p->next;
    }

    p = (IntegerList *)malloc(sizeof(IntegerList));
    p->data = num;
    p->count = 1;
    p->next = NULL;

    if (pre == NULL)
    {
        return p;
    }
    else
    {
        pre->next = p;
        return list;
    }
}

FloatList *appendToFloatlist(FloatList *list, double num)
{
    FloatList *p, *pre;
    p = pre = list;

    while (p != NULL)
    {
        if (p->data == num)
        {
            p->count += 1;
            return list;
        }
        pre = p;
        p = p->next;
    }

    p = (FloatList *)malloc(sizeof(FloatList));
    p->data = num;
    p->count = 1;
    p->next = NULL;

    if (pre == NULL)
    {
        return p;
    }
    else
    {
        pre->next = p;
        return list;
    }
}

void numbersCount()
{
    IntegerList *ilist = NULL;
    FloatList *flist = NULL;

    int c, numInteger, numFloat, inNumber, isdecimals;
    char cBuffer[BUFSIZ];
    int cBufferPos = 0;

    int state = OUT;
    numInteger = numFloat = 0;
    inNumber = OUT;
    isdecimals = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t')
        {
            state = OUT;
            if (inNumber == IN)
            {
                if (isdecimals)
                {
                    ++numFloat;
                    flist = appendToFloatlist(flist, atof(cBuffer));
                }
                else
                {
                    ++numInteger;
                    ilist = appendToIntegerList(ilist, atoi(cBuffer));
                }
            }

            inNumber = OUT;
            isdecimals = 0;
            cBufferPos = 0;
        }
        else if (inNumber == IN && !isdigit(c))
        {
            if (c == '.' && isdecimals == 0)
            {
                isdecimals = 1;
                cBuffer[cBufferPos++] = c;
            }
            else
                inNumber = OUT;
        }
        else if (state == OUT)
        {
            memset(cBuffer, 0, BUFSIZ);
            state = IN;
            if (isdigit(c))
                inNumber = IN;
            cBuffer[cBufferPos++] = c;
        }
        else
        {
            cBuffer[cBufferPos++] = c;
        }
    }

    while (ilist != NULL)
    {
        printf("%d count: %zu\n", ilist->data, ilist->count);
        ilist = ilist->next;
    }

    while (flist != NULL)
    {
        printf("%f count: %zu\n", flist->data, flist->count);
        flist = flist->next;
    }

    printf("integer: %d float: %d\n", numInteger, numFloat);
}

int main()
{
    numbersCount();
    return 0;
}
