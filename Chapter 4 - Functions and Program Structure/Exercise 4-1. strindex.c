/*
Exercise 4-1. Write the function strindex(s,t) which returns the position of the
rightmost occurrence of t in s, or -1 if there is none.

matxo
*/

#include <stdio.h>
#include <string.h>

#define BUFFER_LINE 1000

int strindex(char s[], char t[]);
int get_line(char s[], int lim);

int main()
{
    char line1[BUFFER_LINE];
    char line2[BUFFER_LINE];
    int len;
    while ((len = get_line(line1, BUFFER_LINE)) > 0) {
        if (get_line(line2, BUFFER_LINE) <= 0)
            break;
        // remove newline from the search pattern
        int i = 0;
        while (line2[i++] != '\n')
            ;
        if (line2[--i] == '\n')
            line2[i] = '\0';
        printf("%d\n", strindex(line1, line2));
    }
    return 0;
}

// strindex: return index of rightmost occurrence of t in s, -1 if none
int strindex(char s[], char t[])
{
    int i, j, k;
    for (i = strlen(s)-1; i >= 0; i--) {
        for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

// get_line: read a line into s, return length
int get_line(char s[], int lim)
{
    int c, i;
    for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}
