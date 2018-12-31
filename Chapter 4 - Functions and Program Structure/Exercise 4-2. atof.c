/*
Exercise 4-2. Extend atof to handle scientific notation of the form 123.45e-6
where a floating-point number may be followed by e or E and an optionally signed
exponent.

matxo
*/

#include <stdio.h>
#include <ctype.h>

#define BUFFER_LINE 1000

double atof(char s[]);
int get_line(char s[], int lim);

int main()
{
    char line[BUFFER_LINE];
    while (get_line(line, BUFFER_LINE) > 0) {
        printf("%lf\n", atof(line));
    }
    return 0;
}

// atof: convert string s to double
double atof(char s[])
{
    double ret, val, power;
    int i, sign, exponent_sign, exponent = 0;
    for (i = 0; isspace(s[i]); i++) // skip white space
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    // handle exponent
    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        exponent_sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
            i++;
        for (exponent = 0; isdigit(s[i]); i++)
            exponent = 10 * exponent + (s[i] - '0');
    }
    for (ret = sign * val / power; exponent > 0; exponent--)
        ret = (exponent_sign > 0) ? ret*10 : ret/10;
    return ret;
}

// get_line: read a line into s, return length
int get_line(char s[], int lim)
{
    int c, i;
    for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}
