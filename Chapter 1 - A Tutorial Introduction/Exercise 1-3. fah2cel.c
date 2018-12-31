/*
Exercise 1-3. Modify the temperature conversion program to print a heading above
the table.

matxo
*/

#include <stdio.h>

int main()
{
    printf("The program prints Fahrenheit to Celsius table:\n");
    int step = 20, low = 0, top = 300;
    float fahr = low, cels;
    while (fahr <= top) {
        cels = (5.0/9.0) * (fahr - 32.0);
        printf("%5.1f °F  =  %5.1f °C\n", fahr, cels);
        fahr += step;
    }
    return 0;
}
