/*
Exercise 7-4. Write a private version of scanf analogous to minprintf from the
previous section.

matxo
*/

#include <stdarg.h>
#include <stdio.h>
#include <wchar.h>

void minscanf(char *fmt, ...);
void minprintf(char *fmt, ...);

// test minprintf and minscanf
int main(int argc, char **argv) 
{
    printf("%s\n", "[integer] [integer] [float] [char] [string] [enter]");
    int d, i, c;
    double f;
    char s[100];
    minscanf("%d %i %f %c %s\n", &d, &i, &f, &c, s);
    minprintf("%d %i %f %c %s\n", d, i, f, c, s);
    return 0;
}

// minprintf: minimal printf with variable argument list
void minprintf(char *fmt, ...)
{
    va_list ap; // points to each unnamed arg in turn
    char *p, *sval;
    int ival;
    double dval;

    va_start(ap, fmt); // make ap point to 1st unnamed arg
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
        case 'd':
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;
        case 'i':
            ival = va_arg(ap, int);
            printf("%i", ival);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%lf", dval);
            break;
        case 'c':
            ival = va_arg(ap, int);
            putchar(ival);
            break;
        case 's':
            sval = va_arg(ap, char*);
            printf("%s", sval);
            break;
        default:
            putchar(*p);
            break;
        }
    }
    va_end(ap); // clean up when done
}

void minscanf(char *fmt, ...)
{
    va_list ap; // points to each unnamed arg in turn
    char *p, *sval;
    int *iptr;
    double *dptr;
    char *cptr;

    va_start(ap, fmt); // make ap point to 1st unnamed arg
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
        case 'd':
            iptr = va_arg(ap, int*);
            scanf("%d", iptr);
            break;
        case 'i':
            iptr = va_arg(ap, int*);
            scanf("%i", iptr);
            break;
        case 'f':
            dptr = va_arg(ap, double*);
            scanf("%lf", dptr);
            break;
        case 'c':
            cptr = va_arg(ap, char*);
            scanf("%ls", (wchar_t*)cptr);
            break;
        case 's':
            sval = va_arg(ap, char*);
            scanf("%s", sval);
            break;
        default:
            break;
        }
    }
    va_end(ap); // clean up when done
}