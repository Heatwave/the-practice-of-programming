#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 10000
int arr[N];
int before[N];
int result[N];

int icmp(const void *p1, const void *p2)
{
    int v1, v2;

    v1 = *(int *)p1;
    v2 = *(int *)p2;
    if (v1 > v2)
        return 1;
    else if (v1 < v2)
        return -1;
    else
        return 0;
}

int main(int argc, char const *argv[])
{
    clock_t last = 0;
    for (size_t i = 0; i < 10000; i++)
    {
        for (size_t i = 0; i < N; i++)
        {
            arr[i] = rand();
            before[i] = arr[i];
        }

        clock_t t;
        t = clock();
        qsort(arr, N, sizeof(arr[0]), icmp);
        t = clock() - t;
        if (t > last)
        {
            printf("t: %d > last: %d\n", t, last);
            last = t;
            for (size_t i = 0; i < N; i++)
            {
                result[i] = before[i];
            }
        }
    }

    for (size_t i = 0; i < N; i++)
        printf("%d ", result[i]);

    printf("\nIt took %d clocks (%f seconds).\n", last, ((float)last) / CLOCKS_PER_SEC);

    return 0;
}
