/*
Exercise 2-9. In a two's complement number system, x &= (x-1) deletes the
rightmost 1-bit in x. Explain why. Use this observation to write a faster
version of bitcount.

x &= (x-1) is equivalent to x = x & (x-1)
(x-1) inverts all bits from the beginning till and including the first set bit
and x & (x-1) will then effectivly erase this bit:
x   0X          (x-1)   0X          x & (x-1)   0X
32  00100000    32-1=31 00011111    32 & 31=0   00100000 & 00011111 = 00000000
30  00011110    30-1=29 00011101    30 & 29=28  00011110 & 00011101 = 00011100
3   00000011    3-1=2   00000010    3 & 2=2     00000011 & 00000010 = 00000010

matxo
*/

#include <stdio.h>

int bitcount(unsigned int x);

int main()
{
    unsigned int x;
    printf("bitcount: count 1 bits in x\n");
    scanf("%u", &x);
    printf("result:\t%u\n", bitcount(x));
    return 0;
}

// bitcount: count 1 bits in x
int bitcount(unsigned int x)
{
    int b;
    for (b = 0; x != 0; b++)
        x &= (x-1);
    return b;
}
