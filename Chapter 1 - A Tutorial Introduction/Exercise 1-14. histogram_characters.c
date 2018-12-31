/*
Exercise 1-14. Write a program to print a histogram of the frequencies of
different characters in its input.

matxo
*/

#include <stdio.h>
#define OUT 0
#define IN 1

int main(void)
{
    int c;
    int max_num = 0;
    int chars[256] = {};

    // counts every char category and finds the most frequent one
    while ((c = getchar()) != EOF) {
        chars[c]++;
        if (max_num < chars[c])
            max_num = chars[c];
    }

    puts("Histogram - frequencies of characters used:");
    for(int i = 0; i < max_num; i++) {
        for(int j = 0; j < 256; j++){
            if (chars[j] != 0) {
                if (chars[j] >= (max_num - i))
                    printf("%5c", 'o');
                else
                    printf("%5c", ' ');
            }
        }
        putchar('\n');
    }

    // print legend
    putchar(' ');
    for(int i = 0; i < 256; i++){
        if (chars[i] != 0) {
            if (i == 0 || i == 7 || i == 8) {
                printf("  '\\%d'", i);
            }
            else if (i == 13)
                printf(" '\\%d'", 13);
            else if (i == '\t')
                printf("%5s", "'\\t'");
            else if (i == '\n')
                printf("%5s", "'\\n'");
            else
                printf("  '%c'", i);
        }
    }
    putchar('\n');
    return 0;
}
