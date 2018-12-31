/*
Exercise 1-18. Write a program to remove trailing blanks and tabs from each line
of input, and to delete entirely blank lines.

matxo
*/

#include <stdio.h>
#define MAXLINE 1000 // maximum input line length

int get_line(char line[], int maxline);

int main(void)
{
    char line[MAXLINE];
    int len, i;

    // check line from end to beginning and remove all trailing spaces and tabs
    while ((len = get_line(line, MAXLINE)) > 0) {
        for (i = len - 2; i >= 0 && line[i] != '\n'; i--) {
            if (line[i] != ' ' && line[i] != '\t') {
                line[i + 1] = '\n';
                line[i + 2] = '\0';
                break;
            }
        }
        if (i >= 0)
            printf("%s", line);
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
