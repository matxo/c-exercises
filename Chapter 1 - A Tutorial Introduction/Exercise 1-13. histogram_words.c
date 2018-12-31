/*
Exercise 1-13. Write a program to print a histogram of the lengths of words in
its input. It is easy to draw the histogram with the bars horizontal; a vertical
orientation is more challenging.

matxo
*/

#include <stdio.h>
#define OUT 0
#define IN 1

int main(void)
{
    int c;
    int max_len = 0;
    int n_word = 0;
    int is_word = OUT;
    int words[10000] = {};

    while ((c = getchar()) != EOF) {
        // count letters of each word and find the longest word
        if (c != ' ' && c != '\n' && c != '\t') {
            if (is_word == OUT) {
                is_word = IN;
                n_word++;
            }
            (words[n_word-1])++;
        } else {
            if (max_len < words[n_word-1])
                max_len = words[n_word-1];
            is_word = OUT;
        }
    }

    puts("Histogram - lengths of numbered words:");
    for(int i = 0; i < max_len; i++) {
        for(int x = 0; x < n_word; x++) {
            if (words[x] >= (max_len - i)) {
                printf("%5c", 'o');
            }
            else
                printf("%5c", ' ');
        }
        putchar('\n');
    }

    // print legend
    putchar(' ');
    for(int i = 0; i < n_word; i++) {
        printf("%4d.", i+1);
    }
    putchar('\n');

    return 0;
}
