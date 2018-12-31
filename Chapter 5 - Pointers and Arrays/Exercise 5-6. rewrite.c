/*
Exercise 5-6. Rewrite appropriate programs from earlier chapters and exercises
with pointers instead of array indexing. Good possibilities include getline
(Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2, 3, and 4), 
reverse (Chapter 3), and strindex and getop(Chapter 4).

matxo
*/

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define BUFFER_LINE 1000

int get_line(char *s, int lim);
int itoa(int n, char *s);
int atoi(char *s);
void itob(int n, char *s, int b);
void reverse(char *s, int len);
int strindex(char *s, char *t);
int strlen(char *s);
int getop(char *s);

int main()
{
    char line[BUFFER_LINE];
    if (get_line(line, BUFFER_LINE) <= 0)
        return 1;
    printf("%s", line);

    int n;
    if (scanf("%d\n", &n) <= 0)
        return 1;
    itoa(n, line);
    n = atoi(line);
    printf("%s %d\n", line, n);
    for (int i=2; i < 36; i++) {
        itob(n, line, i);
        printf("base: %2d\t%s\n", i, line);
    }

    char line2[BUFFER_LINE];
    if (get_line(line, BUFFER_LINE) <= 0)
        return 1;
    if (get_line(line2, BUFFER_LINE) <= 0)
        return 1;
    line2[strlen(line2)-1] = '\0';
    printf("strindex: %d\n", strindex(line, line2));

    int c = getop(line);
    printf("getop: %d %c %s\n", c, c, line);
    return 0;
}

// get_line: read a line into s, return length (pointer version)
int get_line(char *s, int lim)
{
    int c;
    char *sp;
    for (sp = s; sp-s < lim-1 && (c=getchar())!=EOF && c!='\n'; sp++) {
        *sp = c;
    }
    if (c == '\n')
        *sp++ = c;
    *sp = '\0';
    return sp-s;
}

// itoa: convert n to characters in s (pointer version)
int itoa(int n, char *s)
{
    if (n < 0) {
        *s = ('-');
        itoa(-n, s+1);
    } else {
        int i = (n >= 10) ? itoa(n / 10, s) : 0;
        *(s+i) = n%10 + '0';
        *(s+i+1) = 0;
        return i + 1;
    }
}

// atoi: convert string s to int (pointer version)
int atoi(char *s)
{
    int value, sign;
    while (isspace(*s))  // skip white space
        s++;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    for (value = 0; isdigit(*s); s++)
        value = value*10 + *s-'0';
    return value * sign;
}

// itob: convert n to base b character representation in s (pointer version)
void itob(int n, char *s, int b)
{
    if ((b <= 1) || (b > 36)) {
        strcpy(s, "base b is out of range");
        return;
    }

    int i, sign;
    if ((sign = n) > 0)     // record sign
        n = -n;             // make n negative

    char *sp = s;
    do {                    // generate digits in reverse order
        // get next digit and use correct character
        if ((-(n % b)) < 10)
            *sp++ = -(n % b)+'0';
        else
            *sp++ = -(n % b)+'A'-10;
    } while ((n /= b) < 0); // delete it
    if (sign < 0)
        *sp++ = '-';
    *sp = '\0';
    reverse(s, sp-s);
}

// reverse: reverse string s in place (pointer version)
void reverse(char *s, int len)
{
    if (len >= 2) {
        reverse(s+1, len-2);
        int c = *s;
        *s = *(s+len-1);
        *(s+len-1) = c;
    }
}

// strindex: return index of rightmost occurrence of t in s, -1 if none (pointer
//      version)
int strindex(char *s, char *t)
{
    for (char *sp = s + strlen(s)-1; sp-s >= 0; sp--) {
        char *sj, *tj;
        for (sj=sp, tj=t; *tj!='\0' && *sj==*tj; sj++, tj++)
            ;
        if (tj > t && *tj == '\0')
            return sp-s;
    }
    return -1;
}

// strlen: return length of the string s (pointer version)
int strlen(char *s) {
    char *sp = s;
    while (*sp != '\0')
        sp++;
    return sp - s;
}

#define NUMBER 'n'
#define VARIABLE 'v'
#define COMMAND 'c'
// getop: get next character or numeric operand (pointer version)
int getop(char *s)
{
    static char line[BUFFER_LINE];
    static char *line_p = line;
    char *sp = s;
    while (true) {
        if (*line_p == '\0') {
             if (get_line(line, BUFFER_LINE) <= 0)
                return EOF;
            line_p = line;
        } else {
            // skip blanks
            while (isblank(*line_p))
                line_p++;
            // number
            if ((*line_p == '+' || *line_p == '-') &&
                (isdigit(*(line_p+1)) || *(line_p+1) == '.'))
            {
                *sp++ = *line_p++;
            }
            while (isdigit(*line_p))        // collect integer part
                *sp++ = *line_p++;
            if (*line_p == '.') {
                *sp++ = *line_p++;
                while (isdigit(*line_p))    // collect fraction part
                    *sp++ = *line_p++;
            }
            if (sp - s != 0) {
                *sp = '\0';
                return NUMBER;
            }
            // command or variable
            while (isalpha(*line_p))
                *sp++ = *line_p++;
            if (sp-s != 0) {
                *sp = '\0';
                if (sp-s == 1)
                    return VARIABLE;
                return COMMAND;
            }
            // operator
            return *line_p++;
        }
    }
}
