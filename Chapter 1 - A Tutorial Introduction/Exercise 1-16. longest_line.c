/*
Exercise 1-16. Revise the main routine of the longest-line program so it will
correctly print the length of arbitrary long input lines, and as much as
possible of the text.

matxo
*/

#include <stdio.h>
#define MAXLINE 1000    // maximum input line length

int get_line(char line[], int maxline);
void copy_str(char to[], char from[]);

int main()
{
    int len;        // current line length
    int max = 0;    // maximum length seen so far
    char line[MAXLINE];     // current input line
    char longest[MAXLINE];  // longest line saved here

    while ((len = get_line(line, MAXLINE)) > 0) {
        //printf("d %d\n", line[len-1]);
        if (len == MAXLINE-1 && line[len-1] != '\n') {
            int l;
            char tmp[MAXLINE];
            while ((l = get_line(tmp, MAXLINE))==MAXLINE-1 && tmp[l-1] != '\n')
                len += l;
            len += l;
        }
        if (len > max ) {
            max = len;
            copy_str(longest, line);
        }
    }

    if (max > 0)    // there was a line
        printf("length: %d\n%s", max, longest);
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

// copy_str: copy 'from' into 'to'; assume 'to' is big enough
void copy_str(char to[], char from[])
{
    int i;
    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
