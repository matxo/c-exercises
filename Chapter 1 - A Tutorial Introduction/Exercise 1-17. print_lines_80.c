/*
Exercise 1-17. Write a program to print all input lines that are longer than 80
characters.

matxo
*/

#include <stdio.h>

#define MAXLINE_BUFFER 1000 // maximum input line length
#define LENGHT 80           // lenght of lines to be printed

int get_line(char line[], int maxline);

int main()
{
    char line[MAXLINE_BUFFER];
    int len;

    do {
        len = get_line(line, MAXLINE_BUFFER);
        if (len >= LENGHT) {
            printf("%s", line);
        }
    } while (len > 0);
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
