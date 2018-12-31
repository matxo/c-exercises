/*
Exercise 2-5. Write the function any(s1,s2), which returns the first location in
a string s1 where any character from the string s2 occurs, or -1 if s1 contains
no characters from s2. (The standard library function strpbrk does the same job
but returns a pointer to the location.)

matxo
*/

#include <stdio.h>

#define BUFFER_LINE 1000

int get_line(char s[], int lim);
int any(char s1[], char s2[]);

int main()
{
    int len1, len2;
    char line1[BUFFER_LINE], line2[BUFFER_LINE];
    for (;;) {
        printf("any: returns the first location in a string s1 where any "
            "character from the string s2 occurs, or -1 if s1 contains no "
            "characters from s2 in s2\n");
        printf("\ts1: ");
        if ((len1 = get_line(line1, BUFFER_LINE)) <= 0)
            break;
        printf("\ts2: ");
        if ((len2 = get_line(line2, BUFFER_LINE)) <= 0)
            break;
        printf("\tany(s1,s2) = %d\n", any(line1, line2));
    }
    return 0;
}

// any: returns the first location in a string s1 where any character from the
//      string s2 occurs, or -1 if s1 contains no characters from s2
int any(char s1[], char s2[])
{
    for (int i = 0; s1[i] != '\0'; i++) {
        for (int j = 0; s2[j] != '\0'; j++)
            if (s1[i] == s2[j] && s1[i] != '\n')
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
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
