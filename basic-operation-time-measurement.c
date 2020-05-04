#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const size_t count = 10000000;

void int_plus_plus()
{
    size_t i = 0;
    while (i < count)
        i++;
}

void plus_plus_int()
{
    size_t i = 0;
    while (i < count)
        ++i;
}

void int_equal_plus()
{
    size_t i = 0;
    size_t i1 = 0, i2 = 1, i3 = 2;

    while (i++ < count)
        i1 = i2 + i3;
}

void int_equal_minus()
{
    size_t i = 0;
    size_t i1 = 0, i2 = 1, i3 = 2;

    while (i++ < count)
        i1 = i3 - i2;
}

void int_equal_multi()
{
    size_t i = 0;
    size_t i1 = 0, i2 = 1, i3 = 2;

    while (i++ < count)
        i1 = i2 * i3;
}

void int_equal_division()
{
    size_t i = 0;
    size_t i1 = 0, i2 = 1, i3 = 2;

    while (i++ < count)
        i1 = i3 / i2;
}

void int_equal_mod()
{
    size_t i = 0;
    size_t i1 = 0, i2 = 1, i3 = 2;

    while (i++ < count)
        i1 = i3 % i2;
}

void float_equal()
{
    size_t i = 0;
    float f1 = 1.2, f2 = 1.2;
    while (i++ < count)
        f1 = f2;
}

void float_equal_plus()
{
    size_t i = 0;
    float f1 = 1.2, f2 = 1.2, f3 = 2.4;
    while (i++ < count)
        f1 = f2 + f3;
}

void float_equal_minus()
{
    size_t i = 0;
    float f1 = 1.2, f2 = 1.2, f3 = 2.4;
    while (i++ < count)
        f1 = f3 - f2;
}

void float_equal_multi()
{
    size_t i = 0;
    float f1 = 1.2, f2 = 1.2, f3 = 2.4;
    while (i++ < count)
        f1 = f2 * f3;
}

void float_equal_division()
{
    size_t i = 0;
    float f1 = 1.2, f2 = 1.2, f3 = 2.4;
    while (i++ < count)
        f1 = f3 / f2;
}

void double_equal()
{
    size_t i = 0;
    double f1 = 1.2, f2 = 1.2;
    while (i++ < count)
        f1 = f2;
}

void double_equal_plus()
{
    size_t i = 0;
    double f1 = 1.2, f2 = 1.2, f3 = 2.4;
    while (i++ < count)
        f1 = f2 + f3;
}

void double_equal_minus()
{
    size_t i = 0;
    double f1 = 1.2, f2 = 1.2, f3 = 2.4;
    while (i++ < count)
        f1 = f3 - f2;
}

void double_equal_multi()
{
    size_t i = 0;
    double f1 = 1.2, f2 = 1.2, f3 = 2.4;
    while (i++ < count)
        f1 = f2 * f3;
}

void double_equal_division()
{
    size_t i = 0;
    double f1 = 1.2, f2 = 1.2, f3 = 2.4;
    while (i++ < count)
        f1 = f3 / f2;
}

void numeric_conversions()
{
    size_t j = 0;
    int i = 1;
    float f = 2.0;
    while (j++ < count)
        i = f;
}

void numeric_conversions_reverse()
{
    size_t j = 0;
    int i = 1;
    float f = 2.0;
    while (j++ < count)
        f = i;
}

void int_vector_operations_one()
{
    size_t j = 0;
    int v[1] = {0};
    int i = 0;
    while (j++ < count)
        v[i] = i;
}

void int_vector_operations_two()
{
    size_t j = 0;
    int v[1] = {0};
    int i = 0;
    while (j++ < count)
        v[v[i]] = i;
}

void int_vector_operations_three()
{
    size_t j = 0;
    int v[1] = {0};
    int i = 0;
    while (j++ < count)
        v[v[v[i]]] = i;
}

void control_if_equal()
{
    size_t j = 0;
    int i = 5;
    int i1 = 0;
    while (j++ < count)
        if (i == 5)
            i1++;
}

void control_if_not_equal()
{
    size_t j = 0;
    int i = 5;
    int i1 = 0;
    while (j++ < count)
        if (i != 0)
            i1++;
}

void malloc_free()
{
    size_t j = 0;
    while (j++ < count)
        free(malloc(sizeof(int)));
}

void atoi_measure()
{
    size_t j = 0;
    int i1 = 0;
    while (j++ < count)
        i1 = atoi("1234");
}

void sscanf_measure()
{
    size_t j = 0;
    int i1 = 0;
    while (j++ < count)
        sscanf("1234", "%d", &i1);
}

void sprintf_measure()
{
    size_t j = 0;
    int i = 1234;
    char s[10];
    while (j++ < count)
        sprintf(s, "%d", i);
}

double time_measurement(void (*fn)())
{
    clock_t before = clock();
    fn();
    return (clock() - before) / (double)count;
}

int main()
{
    double elapsed;

    elapsed = time_measurement(int_plus_plus);
    printf("int_plus_plus used \t\t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(plus_plus_int);
    printf("plus_plus_int used \t\t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(int_equal_plus);
    printf("int_equal_plus used \t\t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(int_equal_minus);
    printf("int_equal_minus used \t\t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(int_equal_multi);
    printf("int_equal_multi used \t\t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(int_equal_division);
    printf("int_equal_division used \t\t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(int_equal_mod);
    printf("int_equal_mod used \t\t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(float_equal);
    printf("float_equal used \t\t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(float_equal_plus);
    printf("float_equal_plus used \t\t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(float_equal_minus);
    printf("float_equal_minus used \t\t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(float_equal_multi);
    printf("float_equal_multi used \t\t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(float_equal_division);
    printf("float_equal_division used \t\t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(double_equal);
    printf("double_equal used \t\t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(double_equal_plus);
    printf("double_equal_plus used \t\t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(double_equal_minus);
    printf("double_equal_minus used \t\t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(double_equal_multi);
    printf("double_equal_multi used \t\t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(double_equal_division);
    printf("double_equal_division used \t\t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(numeric_conversions);
    printf("numeric_conversions used \t\t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(numeric_conversions_reverse);
    printf("numeric_conversions_reverse used \t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(int_vector_operations_one);
    printf("int_vector_operations_one used \t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(int_vector_operations_two);
    printf("int_vector_operations_two used \t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(int_vector_operations_three);
    printf("int_vector_operations_three used \t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(control_if_equal);
    printf("control_if_equal used \t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(control_if_not_equal);
    printf("control_if_not_equal used \t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(malloc_free);
    printf("malloc_free used \t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(atoi_measure);
    printf("atoi_measure used \t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(sscanf_measure);
    printf("sscanf_measure used \t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    elapsed = time_measurement(sprintf_measure);
    printf("sprintf_measure used \t%.4f nanoseconds\n", elapsed / CLOCKS_PER_SEC * 1E9);

    return 0;
}
