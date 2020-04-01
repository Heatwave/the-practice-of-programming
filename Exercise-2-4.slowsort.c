#include <stdio.h>

#define N 8

void swap(int v[], int i, int j)
{
    int temp = v[i];

    v[i] = v[j];
    v[j] = temp;
}

void slowsort(int v[], int n)
{
    for (size_t i = 0; i < n; i++)
    {
        int minPos = i;
        size_t j;
        for (j = i; j < n; j++)
        {
            if (v[j] < v[minPos])
                minPos = j;
        }
        swap(v, i, minPos);
    }
}

void swapsort(int v[], int n)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = i; j < n; j++)
        {
            if (v[i] > v[j])
            {
                swap(v, i, j);
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    int arr[N] = {2, 6, 4, 1, 7, 9, 3, 0};
    slowsort(arr, N);

    for (size_t i = 0; i < N; i++)
        printf("%d ", arr[i]);

    return 0;
}
