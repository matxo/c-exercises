/*
Exercise 1-11. How would you test the word count program? What kinds of input
are most likely to uncover bugs if there are any?

It should be tested:
    with no input - program shoud behave rationally
    input with very long words and very short ones
    with empty lines
    words separated by tabs and combination of tabs and blanks
    combination of all above

matxo
*/

#include <stdio.h>
#define OUT 0
#define IN 1

int main()
{
    int c, word = OUT, n_words = 0, n_nl = 0, n_char = 0;
    while ((c = getchar()) != EOF) {
        n_char++;
        if (c == '\n')
            n_nl++;
        if (c == ' ' || c == '\n' || c == '\t') {
            if (word == IN){
                word = OUT;
            }
        }
        else if (word == OUT){
            word = IN;
            n_words++;
        }
    }
    printf("lines: %d\nwords: %d\ncharacters: %d\n", n_nl, n_words, n_char);
    return 0;
}
