/*
Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n bits
that begin at position p set to the rightmost n bits of y, leaving the other
bits unchanged.

matxo
*/

#include <stdio.h>

unsigned int setbits(unsigned int x, int p, int n, unsigned int y);

int main()
{
    printf("setbits: returns x with the n bits that begin at position p set to "
        "the rightmost n bits of y, leaving the other bits unchanged\n");
    printf("setbits(unsigned int x, int p, int n, unsigned int y)\n");
    int p, n;
    unsigned int x, y;
    scanf("%u %i %i %u", &x, &p, &n, &y);
    printf("result:\t%u\n", setbits(x, p, n, y));
    return 0;
}

// setbits: returns x with the n bits that begin at position p set to the
//      rightmost n bits of y, leaving the other bits unchanged
unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{
    return (x & ~(~(~0 << n) << (p+1-n))) | ((y & ~(~0 << n)) << (p+1-n));
}
