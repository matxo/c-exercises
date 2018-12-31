/*
Exercise 1.15. Rewrite the temperature conversion program of Section 1.2 to use
a function for conversion.

matxo
*/

#include <stdio.h>
#define LOWER   0
#define UPPER   300
#define STEP    20

float fah2cel(float fahr); // converts Fahrenheit to Celsius

int main()
{
    printf("The program prints Fahrenheit to Celsius table:\n");
    for (float fahr = LOWER; fahr <= UPPER; fahr += STEP) {
        printf("%5.1f °F  =  %5.1f °C\n", fahr, fah2cel(fahr));
    }
    return 0;
}

float fah2cel(float fahr)
{
    return (5.0/9.0) * (fahr - 32.0);
}
