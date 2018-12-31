/*
Exercise 1-19. Write a function reverse(s) that reverses the character string s.
Use it to write a program that reverses its input a line at a time.

matxo
*/

#include <stdio.h>

#define MAXLINE 1000 // maximum input line length

int reverse_str(char s[]);
int get_line(char line[], int maxline);

int main(void)
{
    char line[MAXLINE];
    int len;

    while ((len = get_line(line, MAXLINE)) > 0) {
        reverse_str(line);
        printf("%s", line);
    }
    return 0;
}

// reverse_str: reverse string passed as argument, return string length
int reverse_str(char str[])
{
    int len;
    for (len = 0; str[len] != '\0'; len++)
        ;
    for (int i = 0; i < len-2 - i; i++) {
        char c = str[i];
        str[i] = str[len-2 - i];
        str[len-2 - i] = c;
    }
    return len;
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
