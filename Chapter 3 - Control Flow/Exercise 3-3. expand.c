/*
Exercise 3-3. Write a function expand(s1,s2) that expands shorthand notations
like a-z in the string s1 into the equivalent complete list abc...xyz in s2.
Allow for letters of either case and digits, and be prepared to handle cases
like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken 
literally.

matxo
*/

#include <stdio.h>
#include <ctype.h>

#define BUFFER_LINE 1000

void expand(char s1[], char s2[]);
int get_line(char s[], int lim);

int main()
{
    char line1[BUFFER_LINE];
    char line2[BUFFER_LINE];
    int len;
    while ((len = get_line(line1, BUFFER_LINE)) > 0) {
        expand(line1, line2);
        printf("%s", line2);
    }
    return 0;
}

// expand: expands shorthand notations like a-z in the string s1 into the 
//      equivalent complete list abc...xyz in s2
void expand(char s1[], char s2[])
{
    int i, j;
    for (i = 0, j = 0; s1[i] != '\0'; i++, j++) {
        if (s1[i] == '-' && i > 0) {
            char start = s1[i - 1];
            char end = s1[i + 1];
            if (start != end &&
                ((isdigit(start) && isdigit(end)) ||
                (isupper(end) && isupper(start)) ||
                (islower(end) && islower(start))))
            {
                while (start+1 != end && start-1 != end)
                    s2[j++] = start = (start > end) ? (start - 1) : (start + 1);
                j--;
            } else {
                s2[j] = s1[i];
            }
        }
        else
            s2[j] = s1[i];
    }
    s2[j] = '\0';
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
