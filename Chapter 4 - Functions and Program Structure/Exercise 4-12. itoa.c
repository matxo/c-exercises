/*
Exercise 4-12. Adapt the ideas of printd to write a recursive version of itoa;
that is, convert an integer into a string by calling a recursive routine.

matxo
*/

#include <stdio.h>

#define BUFFER_LINE 1000

int itoa(int n, char s[]);

int main()
{
    char line[BUFFER_LINE];
    int n;
    while (scanf("%i", &n) > 0) {
        itoa(n, line);
        printf("%s\n", line);
    }
    return 0;
}

// itoa: convert n to characters in s
int itoa(int n, char s[])
{
    if (n < 0) {
        s[0] = ('-');
        itoa(-n, s + 1);
    } else {
        int i = (n >= 10) ? itoa(n / 10, s) : 0;
        s[i] = n % 10 + '0';
        s[i+1] = 0;
        return i + 1;
    }
}
