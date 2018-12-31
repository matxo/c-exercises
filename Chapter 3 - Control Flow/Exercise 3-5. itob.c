/*
Exercise 3-5. Write the function itob(n,s,b) that converts the integer n into a
base b character representation in the string. In particular, itob(n,s,16)
formats s as a hexadecimal integer in s.

matxo
*/

#include <stdio.h>
#include <string.h>

#define BUFFER_LINE 1000

void itob(int n, char s[], int b);
void reverse(char s[]);

int main()
{
    char line[BUFFER_LINE];
    int n, b;
    while (scanf("%i %i", &n, &b) > 0) {
        itob(n, line, b);
        printf("%s\n", line);
    }
    return 0;
}

// itob: convert n to base b character representation in s
void itob(int n, char s[], int b)
{
    if ((b <= 1) || (b > 36)) {
        strcpy(s, "base b is out of range");
        return;
    }

    int i, sign;
    if ((sign = n) > 0)     // record sign
        n = -n;             // make n negative
    i = 0;
    do {                    // generate digits in reverse order
        // get next digit and use correct character
        if ((-(n % b)) < 10)
            s[i++] = -(n % b)+'0';
        else
            s[i++] = -(n % b)+'A'-10;
    } while ((n /= b) < 0); // delete it
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
