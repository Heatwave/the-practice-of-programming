#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const size_t VOLUME = sizeof(char) * 1024;

typedef struct pre_alloc_data
{
    char *data;
    size_t pos;
} pre_alloc_data;

pre_alloc_data *s;

char *smalloc(size_t size)
{
    printf("smalloc size: %u\n", size);
    if (size >= VOLUME)
    {
        printf("directly malloc size: %u\n", size);
        return malloc(size);
    }

    if (s == NULL || s->pos + size >= VOLUME)
    {
        printf("pre malloc size: %u\n", VOLUME);
        s = (pre_alloc_data *)malloc(sizeof(pre_alloc_data));
        s->data = malloc(VOLUME);
        s->pos = 0;
        s->data[s->pos] = '\0';
    }

    char *p = (char *)s->data;

    char *allocPos = &(p[s->pos]);

    s->pos += size;
    s->data[s->pos] = '\0';

    return allocPos;
}

int main()
{
    char *s = smalloc(sizeof(char) * 64);
    printf("%s\n", s);
    strcat(s, "hello");
    strcat(s, ", ");
    strcat(s, "world");
    printf("%s\n", s);
    char *t = smalloc(sizeof(char) * 512);
    printf("%s\n", t);
    strcat(t, "smalloc");
    strcat(t, " ");
    strcat(t, "good");
    printf("%s\n", t);
    printf("%s\n", s);
    char *k = smalloc(sizeof(char) * 8192);
    k[0] = '\0';
    printf("%s\n", k);
    strcat(k, "long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long string");
    printf("%s\n", k);
    return 0;
}
