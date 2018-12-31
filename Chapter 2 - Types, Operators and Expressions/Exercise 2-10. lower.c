/*
Exercise 2-10. Rewrite the function lower, which converts upper case letters to
lower case, with a conditional expression instead of if-else.

matxo
*/

#include <stdio.h>

char lower(char c);

int main()
{
    char c;
    printf("lower: convert c to lower case; ASCII only\n");
    scanf("%c", &c);
    printf("result:\t%c\n", lower(c));
    return 0;
}

// lower: convert c to lower case; ASCII only
char lower(char c)
{
    return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
}
