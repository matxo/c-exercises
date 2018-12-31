/*
Exercise 4-13. Write a recursive version of the function reverse(s), which
reverses the string s in place.

matxo
*/

#include <stdio.h>
#include <string.h>

#define BUFFER_LINE 1000

void reverse(char s[], int len);
int get_line(char s[], int lim);

int main()
{
    char line[BUFFER_LINE];
    while (get_line(line, BUFFER_LINE) > 0) {
        reverse(line, strlen(line) - 1);
        printf("%s", line);
    }
    return 0;
}

// reverse: reverse string s in place
void reverse(char s[], int len)
{
    if (len >= 2) {
        reverse(s + 1, len - 2);
        int c = s[0];
        s[0] = s[len - 1];
        s[len - 1] = c;
    }
}

// get_line: read a line into s, return length
int get_line(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c=getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
