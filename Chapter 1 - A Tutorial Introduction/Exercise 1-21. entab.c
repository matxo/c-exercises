/*
Exercise 1-21. Write a program entab that replaces strings of blanks by the
minimum number of tabs and blanks to achieve the same spacing. Use the same tab
stops as for detab. When either a tab or a single blank would suffice to reach a
tab stop, which should be given preference?

Tab should be given preference over space.

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
    int n_spaces = 0;

    while ((len = get_line(line, BUFFER_LINE)) > 0) {
        int i; // position in original line
        int j; // number of spaces in original line
        int k; // number of spaces in resulting line
        for (i = j = k = 0; line[i] != '\0'; i++) {
            if (line[i] == ' ') {
                n_spaces++;
                j++;
            } else if (line[i] == '\t') {
                n_spaces += tab - j%tab;
                j += tab - j%tab;
            } else {
                if (n_spaces) {
                    while (tab - k%tab <= n_spaces) { // print tabs
                        putchar('\t');
                        n_spaces -= tab - k%tab;
                        k += tab - k%tab;
                    }
                    while (n_spaces) { // print spaces
                        putchar(' ');
                        n_spaces--;
                        k++;
                    }
                }
                putchar(line[i]); // print other chars
                j++;
                k++;
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
