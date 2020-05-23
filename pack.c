#include <stdarg.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "eprintf.h"

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

#define NELEMS(arr) (sizeof(arr) / sizeof(arr[0]))

#define PACK0 0x00
#define PACK1 0x01
#define PACK2 0x02
#define PACK3 0x03
#define PACK0_FORMAT "cscl"
#define PACK1_FORMAT "csll"
#define PACK2_FORMAT "cSLS"
#define PACK3_FORMAT "c4sll"

// pack: pack binary items into buf, return length
int pack(uchar *buf, char *fmt, ...)
{
    va_list args;
    char *p;
    uchar *bp;
    ushort s;
    ulong l;
    int count = 0;

    bp = buf;
    va_start(args, fmt);
    for (p = fmt; *p != '\0'; p++)
    {
        switch (*p)
        {
        case 'c': // char
            *bp++ = va_arg(args, int);
            break;
        case 's': // short
        case 'S': // signed short
            if (count > 0)
            {
                ushort *usp = va_arg(args, ushort *);
                int tmp = count;
                while (count > 0)
                {
                    *bp++ = *(usp + (tmp - count)) >> 8;
                    *bp++ = *(usp + (tmp - count));
                    count--;
                }
            }
            else
            {
                s = va_arg(args, int);
                *bp++ = s >> 8;
                *bp++ = s;
            }
            break;
        case 'l': // long
        case 'L': // signed long
            l = va_arg(args, ulong);
            *bp++ = l >> 24;
            *bp++ = l >> 16;
            *bp++ = l >> 8;
            *bp++ = l;
            break;
        default: // illegal type character
            if (isdigit(*p))
            {
                count = atoi(p);

                while (isdigit(*(p + 1)))
                {
                    p++;
                }
            }
            else
            {
                va_end(args);
                return -1;
            }
        }
    }
    va_end(args);
    return bp - buf;
}

// unpack: unpack packed items from buf, return length
int unpack(uchar *buf, char *fmt, ...)
{
    va_list args;
    char *p;
    uchar *bp, *pc;
    ushort *ps;
    ulong *pl;
    int count = 0;

    bp = buf;
    va_start(args, fmt);
    for (p = fmt; *p != '\0'; p++)
    {
        switch (*p)
        {
        case 'c': // char
            pc = va_arg(args, uchar *);
            *pc = *bp++;
            break;
        case 's': // unsigned short
            ps = va_arg(args, ushort *);
            if (*(p) == 'S')
                *ps = ((signed char)*bp++) << 8;
            else
                *ps = *bp++ << 8;
            *ps |= *bp++;
            if (count > 0)
            {
                int tmp = count--;

                while (count > 0)
                {
                    if (*(p) == 'S')
                        *(ps + (tmp - count)) = ((signed char)*bp++) << 8;
                    else
                        *(ps + (tmp - count)) = *bp++ << 8;
                    *(ps + (tmp - count)) |= *bp++;
                    count--;
                }
            }
            break;
        case 'S': // signed short
            ps = va_arg(args, ushort *);
            *ps = ((signed char)*bp++) << 8;
            *ps |= *bp++;
            break;
        case 'l': // unsigned long
            pl = va_arg(args, ulong *);
            *pl = *bp++ << 24;
            *pl |= *bp++ << 16;
            *pl |= *bp++ << 8;
            *pl |= *bp++;
            break;
        case 'L': // signed long
            pl = va_arg(args, ulong *);
            *pl = ((signed char)*bp++) << 24;
            *pl |= *bp++ << 16;
            *pl |= *bp++ << 8;
            *pl |= *bp++;
            break;
        default: // illegal type character
            if (isdigit(*p))
            {
                count = atoi(p);

                while (isdigit(*(p + 1)))
                {
                    p++;
                }
            }
            else
            {
                va_end(args);
                return -1;
            }
        }
    }
    va_end(args);
    return bp - buf;
}

int process_type0(ushort count, uchar val, ulong data)
{
    printf("process type0, count: %u, val: %u, data: %lu\n", count, val, data);
    return 0;
}

int pack_type0(uchar *buf, ushort count, uchar val, ulong data)
{
    return pack(buf, PACK0_FORMAT, PACK0, count, val, data);
}

int unpack_type0(int n, uchar *buf)
{
    uchar c;
    ushort count;
    uchar val;
    ulong data;

    if (unpack(buf, PACK0_FORMAT, &c, &count, &val, &data) != n)
        return -1;
    assert(c == PACK0);
    return process_type0(count, val, data);
}

int process_type1(ushort count, ulong dw1, ulong dw2)
{
    printf("process type1, count: %u, dw1: %lu, dw2: %lu\n", count, dw1, dw2);
    return 0;
}

int pack_type1(uchar *buf, ushort count, ulong dw1, ulong dw2)
{
    return pack(buf, PACK1_FORMAT, PACK1, count, dw1, dw2);
}

int unpack_type1(int n, uchar *buf)
{
    uchar c;
    ushort count;
    ulong dw1, dw2;

    if (unpack(buf, PACK1_FORMAT, &c, &count, &dw1, &dw2) != n)
        return -1;
    assert(c == PACK1);
    return process_type1(count, dw1, dw2);
}

int process_type2(short count, long dw1, ushort us1)
{
    printf("process type2, count: %d, dw1: %ld, us1: %u\n", count, dw1, us1);
    return 0;
}

int pack_type2(uchar *buf, short count, long dw1, ushort us1)
{
    return pack(buf, PACK2_FORMAT, PACK2, count, dw1, us1);
}

int unpack_type2(int n, uchar *buf)
{
    uchar c;
    short count;
    long dw1;
    ushort us1;

    if (unpack(buf, PACK2_FORMAT, &c, &count, &dw1, &us1) != n)
        return -1;
    assert(c == PACK2);
    return process_type2(count, dw1, us1);
}

int process_type3(ushort us1[4], ulong dw1, ulong dw2)
{
    printf("process type3, ");
    printf("us1: ");

    for (size_t i = 0; i < 4; i++)
    {
        printf("%u ", us1[i]);
    }

    printf(", dw1: %ld, dw2: %ld\n", dw1, dw2);
    return 0;
}

int pack_type3(uchar *buf, ushort us1[4], ulong dw1, ulong dw2)
{
    return pack(buf, PACK3_FORMAT, PACK3, us1, dw1, dw2);
}

int unpack_type3(int n, uchar *buf)
{
    uchar c;
    ushort us1[4];
    ulong dw1, dw2;

    if (unpack(buf, PACK3_FORMAT, &c, us1, &dw1, &dw2) != n)
        return -1;
    assert(c == PACK3);
    return process_type3(us1, dw1, dw2);
}

int readpacket(int network, uchar *buf, size_t bufsize)
{
    if (network == 0)
    {
        return pack_type0(buf, 2, 4, 1234);
    }
    else if (network == 1)
    {
        return pack_type1(buf, 4, 1234, 5678);
    }
    else if (network == 2)
    {
        return pack_type2(buf, -1234, -854775807, 32767);
    }
    else if (network == 3)
    {
        ushort us1[4] = {1, 12, 123, 1234};
        return pack_type3(buf, us1, 12345678, 12345678);
    }
    else
    {
        return 0;
    }
}

int (*unpackfn[])(int, uchar *) = {
    unpack_type0,
    unpack_type1,
    unpack_type2,
    unpack_type3};

void receive(int network)
{
    uchar type, buf[BUFSIZ];
    int n;

    while ((n = readpacket(network++, buf, BUFSIZ)) > 0)
    {
        type = buf[0];
        if (type >= NELEMS(unpackfn))
            eprintf("bad packet type 0x%x", type);
        if ((*unpackfn[type])(n, buf) < 0)
            eprintf("protocol error, type %x length %d", type, n);
    }
}

int main()
{
    receive(0);
    return 0;
}
