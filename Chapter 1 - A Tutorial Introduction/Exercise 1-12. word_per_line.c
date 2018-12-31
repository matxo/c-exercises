/*
Exercise 1-12. Write a program that prints its input one word per line.

matxo
*/

#include <stdio.h>
#define OUT 0
#define IN 1

int main()
{
    int c, word = OUT;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (word == IN){
                word = OUT;
                putchar('\n');
            }
        }
        else {
            putchar(c);
            word = IN;
        }
    }
    return 0;
}
