/*
Exercise 2-8. Write a function rightrot(x,n) that returns the value of the
integer x rotated to the right by n positions.

matxo
*/

#include <stdio.h>

unsigned int rightrot(unsigned int x, int n);

int main()
{
    printf("rightrot: returns the value of the integer x rotated to the right"
        "by n positions..\n");
    printf("rightrot(unsigned int x, int n)\n");
    int n;
    unsigned int x;
    scanf("%u %i", &x, &n);
    printf("result:\t%u\n", rightrot(x, n));
    return 0;
}

// rightrot: returns the value of the integer x rotated to the right by n
//      positions
unsigned int rightrot(unsigned int x, int n)
{
    return x >> n;
}
