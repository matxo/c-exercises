/*
Exercise  2-7. Write  a  function invert(x,p,n) that returns x with the n bits
that begin at position p inverted (i.e., 1 changed into 0 and vice versa),
leaving the others unchanged.

matxo
*/

#include <stdio.h>

unsigned int invert(unsigned int x, int p, int n);

int main()
{
    printf("invert: returns x with the n bits that begin at position p inverted"
        "(i.e., 1 changed into 0 and vice versa), leaving the others unchanged"
        "\n");
    printf("setbits(unsigned int x, int p, int n)\n");
    int p, n;
    unsigned int x;
    scanf("%u %i %i", &x, &p, &n);
    printf("result:\t%u\n", invert(x, p, n));
    return 0;
}

// invert: returns x with the n bits that begin at position p inverted (i.e., 1
//      changed into 0 and vice versa), leaving the others unchanged
unsigned int invert(unsigned int x, int p, int n)
{
    return x ^ (~(~0 << n) << (p+1-n));
}
