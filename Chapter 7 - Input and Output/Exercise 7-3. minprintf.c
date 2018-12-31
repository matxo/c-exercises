/*
Exercise 7-3. Revise minprintf to handle more of the other facilities of printf.

matxo
*/

#include <stdarg.h>
#include <stdio.h>

void minprintf(char *fmt, ...);

// test minprintf
int main(int argc, char **argv) 
{
    minprintf("%d %i %f %c %s\n", 10, 20, 2.3, 'c', "string");
    
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