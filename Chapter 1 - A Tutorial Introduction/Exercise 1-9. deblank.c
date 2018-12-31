/*
Exercise 1-9. Write a program to copy its input to its output, replacing each
string of one or more blanks by a single blank.

matxo
*/

#include <stdio.h>
#define TRUE 1
#define FALSE 0

int main()
{
    int c, wasblank = FALSE;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (wasblank == FALSE) {
                wasblank = TRUE;
                putchar(c);
            }
        } else {
            wasblank = FALSE;
            putchar(c);
        }
    }
    return 0;
}
