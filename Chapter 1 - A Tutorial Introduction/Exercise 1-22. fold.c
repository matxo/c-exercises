/*
Exercise 1-22. Write a program to ``fold'' long input lines into two or more
shorter lines after the last non-blank character that occurs before the n -th
column of input. Make sure your program does something intelligent with very
long lines, and if there are no blanks or tabs before the specified column.

matxo
*/

#include <stdio.h>
#include <ctype.h>

#define BUFFER_LINE 1000

int tab = 8;
int max_len = 80;
int min_len;

int get_line(char s[], int lim);

int main(void)
{
    min_len = ((max_len + 1) * 4) / 5;
    char line[BUFFER_LINE];
    int len;

    while ((len = get_line(line, BUFFER_LINE)) > 0) {
        int i = 0;
        int pos = 0;
        while (i < len) {
            pos += (line[i] == '\t') ? (tab - (pos % tab)) : 1;

            if (pos < min_len) {
                putchar(line[i]);
                i++;
            } else {
                // find character positions of min and max line length
                int min_i = i;
                int max_i;
                while (pos <= max_len && i < len) {
                    max_i = i;
                    pos += (line[++i] == '\t') ? (tab - (pos % tab)) : 1;
                }
                pos = 0;

                // find best place to fold the lines
                int nl_i = max_i;
                for (i = max_i; i >= min_i; i--) {
                    if (! isalnum(line[i])) {
                        nl_i = i;
                        break;
                    }
                }

                // print folded line
                for (i = min_i; i <= nl_i; i++) {
                    putchar(line[i]);
                }
                putchar('\n');

                // remove spaces after folded position and continute
                while (i < len) {
                    if (! isalnum(line[i]))
                        i++;
                    else
                        break;
                }
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
