/*
Exercise  3-4. In a two's complement number representation, our version of itoa
does not handle the largest negative number, that is, the value of n equal to
-(pow(2, wordsize-1)). Explain why not. Modify it to print that value correctly,
regardless of the machine on which it runs.

Int range is from +(pow(2, wordsize-1))-1 to -(pow(2, wordsize-1)). For example:
    wordsize = 8 bits   +127            -128
    wordsize = 32 bits  2,147,483,647   -2,147,483,648
Therefore in line n = -n; (make n positive) overflow occures for the largest
negative integer. Workaround is to work with negative number, which can hold
greater value range.

matxo
*/

#include <stdio.h>
#include <string.h>

#define BUFFER_LINE 1000

void itoa(int n, char s[]);
void reverse(char s[]);

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
void itoa(int n, char s[])
{
    int i, sign;
    if ((sign = n) > 0) // record sign
        n = -n;         // make n negative
    i = 0;
    do {                // generate digits in reverse order
        s[i++] = -(n % 10) + '0';   // get next digit
    } while ((n /= 10) < 0);        // delete it
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

// reverse: reverse string s in place
void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
