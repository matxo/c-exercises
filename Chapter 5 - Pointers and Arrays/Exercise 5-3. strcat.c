/*
Exercise 5-3. Write a pointer version of the function strcat that we showed in
Chapter 2: strcat(s,t) copies the string t to the end of s.

matxo
*/

#include <stdio.h>

#define BUFFER_LINE 1000

void strcat(char s[], char t[]);
int get_line(char s[], int lim);

int main()
{
    char line[BUFFER_LINE];
    char s[BUFFER_LINE];
    *s = '\0';
    while (get_line(line, BUFFER_LINE) > 0) {
        int i = 0;
        while (line[i] != '\0')
            i++;
        line[i-1] = '\0'; // remove newline
        strcat(s, line);
        printf("%s\n", s);
    }
    return 0;
}

// strcat: concatenate t to end of s; s must be big enough
void strcat(char s[], char t[])
{
    while (*s) // find end of s
        s++;
    while (*s++ = *t++) // copy t
        ;
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
