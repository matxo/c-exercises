/*
Exercise 5-2. Write getfloat, the floating-point analog of getint. What type
does getfloat return as its function value?

matxo
*/

#include <stdio.h>
#include <ctype.h>

int getfloat(float *pn);
int getch(void);
void ungetch(int);

int main()
{
    float f;
    while (getfloat(&f) > 0)
        printf("%f\n", f);

    return 0;
}

// getfloat: get next float from input into *pn
int getfloat(float *pn)
{
    int c, s, dot, sign, fraction, exponent_sign, exponent;
    while (isspace(c = getch())) // skip white space
        ;
    if (!isdigit(c) && tolower(c) != 'e' && c != EOF && c != '+' && c != '-' &&
        c != '.') {
        ungetch(c); // it is not a number
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        s = c;
        c = getch();
    }

    if (!isdigit(c) && c != '.') {
        ungetch(c); // it is not a number
        ungetch(s);
        return 0;
    }
    if (isdigit(c)) {
        for (*pn = 0; isdigit(c); c = getch())
            *pn = 10 * *pn + (c - '0');
    } else {
        c = getch();
        if (!isdigit(c)) {
            ungetch(c);  // it is not a number
            ungetch('.');
            return 0;
        } else {
            *pn = 0;
            ungetch(c);
            c = '.';
        }
    }

    if (c == '.')
        c = getch();
    for (fraction = 1; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c-'0');
        fraction *= 10;
    }
    *pn *= sign;
    *pn /= fraction;

    // handle exponent
    if (tolower(c) == 'e') {
        c = getch();
        exponent_sign = (c == '-') ? -1 : 1;
        if (c == '+' || c == '-')
            c = getch();
        for (exponent = 0; isdigit(c); c = getch())
            exponent = 10 * exponent + (c - '0');
    }
    while (exponent-- > 0)
        *pn = (exponent_sign > 0) ? (*pn)*10 : (*pn)/10;

    if (c != EOF)
        ungetch(c);
    return c;
}

#define BUFSIZE 100

char buf[BUFSIZE];  // buffer for ungetch
int bufp = 0;       // next free position in buf

int getch(void)     // get a (possibly pushed-back) character
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) // push character back on input
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
