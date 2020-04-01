#include <stdio.h>
#include <stdlib.h>

#define LENGTH_OF_ARRAY(array) (sizeof(array) / sizeof(array[0]))

#define Error(Str) FatalError(Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

#define ElementType int

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

struct Node
{
    ElementType element;
    PtrToNode next;
};

int isEmpty(Stack s)
{
    return s->next == NULL;
}

void push(ElementType x, Stack s)
{
    PtrToNode newCell;

    newCell = malloc(sizeof(struct Node));
    if (newCell == NULL)
        Error("Must use createStack first");
    else
    {
        newCell->element = x;
        newCell->next = s->next;
        s->next = newCell;
    }
}

void pop(Stack s)
{
    PtrToNode FirstCell;

    if (isEmpty(s))
        Error("Empty Stack");
    else
    {
        FirstCell = s->next;
        s->next = s->next->next;
        free(FirstCell);
    }
}

void makeEmpty(Stack s)
{
    if (s == NULL)
        Error("Must use createStack first");
    else
        while (!isEmpty(s))
            pop(s);
}

Stack createStack()
{
    Stack s;

    s = malloc(sizeof(struct Node));
    if (s == NULL)
        FatalError("Out of Memory!!!");
    s->next = NULL;
    makeEmpty(s);
    return s;
}

/* swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j)
{
    int temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* quicksort iteratively: sort v[0]..v[n-1] into increasing order */
void quicksortiter(int v[], int n)
{
    Stack s = createStack();

    int left = 0, right = n;

    push(left, s);
    push(right, s);

    while (!isEmpty(s))
    {
        right = s->next->element;
        pop(s);
        left = s->next->element;
        pop(s);

        if (left >= right)
            continue;

        swap(v, left, rand() % (right - left) + left);
        int pivot = left;
        for (int i = left + 1; i < right; i++)
            if (v[i] < v[left])
                swap(v, ++pivot, i);
        swap(v, left, pivot);

        push(left, s);
        push(pivot, s);

        push(pivot + 1, s);
        push(right, s);
    }
}

int main(int argc, char const *argv[])
{
    int arr[10] = {3, 4, 2, 1, 5, 6, 0, 2, 10, 7};
    quicksortiter(arr, LENGTH_OF_ARRAY(arr));

    for (size_t i = 0; i < LENGTH_OF_ARRAY(arr); i++)
        printf("%d ", arr[i]);

    return 0;
}
