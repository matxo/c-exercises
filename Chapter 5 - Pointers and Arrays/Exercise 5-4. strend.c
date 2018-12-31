/*
Exercise 5-4. Write the function strend(s,t), which returns 1 if the string t
occurs at the end of the string s, and zero otherwise.

matxo
*/

#include <stdio.h>
#include <string.h>

#define BUFFER_LINE 1000

int strend(char s[], char t[]);
int get_line(char s[], int lim);

int main()
{
    char s[BUFFER_LINE], t[BUFFER_LINE];
    while (get_line(s, BUFFER_LINE) > 0) {
        if (get_line(t, BUFFER_LINE) <= 0)
            break;
        printf("%s\n", strend(s, t) ? "true" : "false");
    }
    return 0;
}

// strend: returns 1 if the string t occurs at the end of the string s, and zero
//      otherwise
int strend(char s[], char t[])
{
    char *ps = s;
    char *pt = t;
    while (*ps) // find end of s
        ps++;
    while (*pt) // find end of t
        pt++;
    while (ps != s && pt != t && *--ps == *--pt)
        ;
    return (*ps == *pt && pt == t) ? 1 : 0;
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
