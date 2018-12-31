/*
Exercise 3-6. Write a version of itoa that accepts three arguments instead of
two. The third argument is a minimum field width; the converted number must be
padded with blanks on the left if necessary to make it wide enough.

matxo
*/

#include <stdio.h>
#include <string.h>

#define BUFFER_LINE 1000

void itoa(int n, char s[], int w);
void reverse(char s[]);

int main()
{
    char line[BUFFER_LINE];
    int n, w;
    while (scanf("%i %i", &n, &w) > 0) {
        itoa(n, line, w);
        printf("%s\n", line);
    }
    return 0;
}

// itoa: convert n to characters in s, optionally left padded to minimal width w
void itoa(int n, char s[], int w)
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
    while(i < w)        // left pad with spaces
        s[i++] = ' ';
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
