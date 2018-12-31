/*
Exercise 5-5. Write versions of the library functions strncpy, strncat, and
strncmp, which operate on at most the first n characters of their argument
strings. For example, strncpy(s,t,n) copies at most n characters of t to s. Full
descriptions are in Appendix B.

matxo
*/

#include <stdio.h>

#define BUFFER_LINE 1000

char *strncpy(char *s, char *ct, int n);
char *strncat(char *s, char *ct, int n);
int strncmp(char *cs, char *ct, int n);
int get_line(char s[], int lim);

int main()
{
    char s[BUFFER_LINE], t[BUFFER_LINE];
    if (get_line(s, BUFFER_LINE) <= 0)
        return 1;
    if (get_line(t, BUFFER_LINE) <= 0)
        return 1;
    int n;
    if (scanf("%d", &n) <= 0)
        return 1;
    printf("strncpy(s,t,n): %s", strncpy(s,t,n));
    printf("strncat(s,t,n): %s", strncat(s,t,n));
    printf("strncmp(s,t,n): %d", strncmp(s,t,n));
    return 0;
}
char *strncpy(char *s, char *ct, int n)
{
    char *st = s;
    while(*st && st - s < n) {
        if (*ct)
            *st++ = *ct++;
        else
            *st++ = '\0';
    }
    return s;
}
// strncat: concatenate at most n characters of string ct to string s, terminate
//      s with '\0'; return s
char *strncat(char *s, char *ct, int n)
{
    char *st = s;
    char *c = ct;
    while (*st)
        st++;
    while(((ct - c) < n) && (*st++ = *ct++))
        ;
    *st = '\0';
    return s;
}

// strncmp: compare at most n characters of string cs to string ct; return <0 if
//      cs<ct, 0 if cs==ct, or >0 if cs>ct
int strncmp(char *cs, char *ct, int n)
{
    char *s = cs;
    while (*cs && (*cs == *ct) && (cs - s < n))
        cs++, ct++;
    return *ct - *cs;
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
