/*
Exercise 2-2. Write a loop equivalent to the for loop above without using && or
||.

matxo
*/

#include <stdio.h>

#define BUFFER_LINE 10000

int get_line(char s[], int lim);

int main()
{
    int len;
    char line[BUFFER_LINE];
    while ((len = get_line(line, BUFFER_LINE)) > 0) {
        printf("%s", line);
    }
    return 0;
}

// get_line: read a line into s, return length
int get_line(char s[], int lim)
{
    int c, i;
/*
    for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
        s[i] = c;
    }
*/
    for (int i=0; i < lim-1; i++) {
        if ((c = getchar()) == EOF) {
            s[i] = '\0';
            return i;
        }
        s[i] = c;
        if (c == '\n') {
            s[++i] = '\0';
            return i;
        }
    }

}
