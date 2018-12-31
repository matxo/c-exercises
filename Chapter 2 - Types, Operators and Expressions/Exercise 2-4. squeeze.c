/*
Exercise 2-4. Write an alternative version of squeeze(s1,s2) that deletes each
character in s1 that matches any character in the string s2.

matxo
*/

#include <stdio.h>

#define BUFFER_LINE 1000

int get_line(char s[], int lim);
void squeeze(char s1[], char s2[]);

int main()
{
    int len1, len2;
    char line1[BUFFER_LINE], line2[BUFFER_LINE];
    for (;;) {
        printf("squeeze: delete each character in s1 that matches any character"
                " in s2\n");
        printf("\ts1: ");
        if ((len1 = get_line(line1, BUFFER_LINE)) <= 0)
            break;
        printf("\ts2: ");
        if ((len2 = get_line(line2, BUFFER_LINE)) <= 0)
            break;
        squeeze(line1, line2);
        printf("\tsqueeze(s1, s2);\n");
        printf("\ts1: %s\n", line1);
    }
    return 0;
}

// squeeze: delete each character in s1 that matches any character in s2
void squeeze(char s1[], char s2[])
{
    int i, j, k;
    for (i = j = 0; s1[i] != '\0'; i++) {
        for (k = 0; s2[k] != '\0' && s1[i] != s2[k]; k++)
            ;
        if (s1[i] != s2[k])
            s1[j++] = s1[i];
    }
    s1[j] = '\0';
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
