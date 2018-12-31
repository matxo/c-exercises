/*
Exercise 1-20. Write a program detab that replaces tabs in the input with the
proper number of blanks to space to the next tab stop. Assume a fixed set of tab
stops, say every n columns. Should n be a variable or a symbolic parameter?

I have choosen n(tab) to be a global variable. That way the program can be
extended easely in the future.

matxo
*/

#include <stdio.h>

#define BUFFER_LINE 1000

int tab = 8;
int get_line(char s[], int lim);

int main(void)
{
    int len;
    char line[BUFFER_LINE];

    while ((len = get_line(line, BUFFER_LINE)) > 0) {
        for (int i=0, j=0; line[i] != '\0'; i++, j++) {
            if (line[i] == '\t') {
                int n_tab_spaces = tab - j%tab;
                j += n_tab_spaces - 1;
                while (n_tab_spaces--)
                    putchar(' ');
            } else {
                putchar(line[i]);
            }
        }
    }
    return 0;
}

// get_line: read a line into s, return length
int get_line(char s[], int lim)
{
    int c, i;
    for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
