/*
Exercise  3-2. Write a function escape(s,t) that converts characters like
newline and tab into visible escape sequences like \n and \t as it copies the
string t to s. Use a switch. Write a function for the other direction as well,
converting escape sequences into the real characters.

matxo
*/

#include <stdio.h>

#define BUFFER_LINE 1000

void escape(char s[], char t[]);
void escape_rev(char s[], char t[]);
int get_line(char s[], int lim);

int main()
{
    char line1[BUFFER_LINE];
    char line2[BUFFER_LINE];
    char line3[BUFFER_LINE];
    int len;
    while ((len = get_line(line1, BUFFER_LINE)) > 0) {
        escape(line2, line1);
        escape_rev(line3, line2);
        printf("line1: %s\nline2: %s\nline3: %s\n", line1, line2, line3);
    }
    return 0;
}

// escape: copies string t to s, replacing \n and \t by visible escape sequences
void escape(char s[], char t[])
{
    int i, j;
    for (i = 0, j = 0; t[j] != '\0'; i++, j++) {
        switch (t[j]) {
            case '\t':
                s[i++] = '\\';
                s[i] = 't';
                break;
            case '\n':
                s[i++] = '\\';
                s[i] = 'n';
                break;
            default:
                s[i] = t[j];
                break;
        }
    }
    s[i] = '\0';
}

// escape_rev: copies string t to s, replacing '\n' and '\t' by real characters
void escape_rev(char s[], char t[])
{
    int i, j;
    for (i = 0, j = 0; t[j] != '\0'; i++, j++) {
        switch (t[j]) {
            case '\\':
                switch (t[j+1]) {
                    case 't':
                        s[i] = '\t';
                        j++;
                        break;
                    case 'n':
                        s[i] = '\n';
                        j++;
                        break;
                    default:
                        s[i] = t[j];
                        break;
                }
                break;
            default:
                s[i] = t[j];
                break;
        }
    }
    s[i] = '\0';
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
