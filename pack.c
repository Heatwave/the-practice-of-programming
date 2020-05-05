#include <stdarg.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "eprintf.h"

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

#define NELEMS(arr) (sizeof(arr) / sizeof(arr[0]))

#define PACK0 0x00
#define PACK1 0x01
#define PACK0_FORMAT "cscl"
#define PACK1_FORMAT "csll"

// pack: pack binary items into buf, return length
int pack(uchar *buf, char *fmt, ...)
{
    va_list args;
    char *p;
    uchar *bp;
    ushort s;
    ulong l;

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
            s = va_arg(args, int);
            *bp++ = s >> 8;
            *bp++ = s;
            break;
        case 'l': // long
            l = va_arg(args, ulong);
            *bp++ = l >> 24;
            *bp++ = l >> 16;
            *bp++ = l >> 8;
            *bp++ = l;
            break;
        default: // illegal type character
            va_end(args);
            return -1;
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
        case 's': // short
            ps = va_arg(args, ushort *);
            *ps = *bp++ << 8;
            *ps |= *bp++;
            break;
        case 'l': // long
            pl = va_arg(args, ulong *);
            *pl = *bp++ << 24;
            *pl |= *bp++ << 16;
            *pl |= *bp++ << 8;
            *pl |= *bp++;
            break;
        default: // illegal type character
            va_end(args);
            return -1;
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
    else
    {
        return 0;
    }
}

int (*unpackfn[])(int, uchar *) = {unpack_type0,
                                   unpack_type1};

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
