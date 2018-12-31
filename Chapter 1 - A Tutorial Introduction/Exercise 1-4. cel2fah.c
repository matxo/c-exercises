/*
Exercise 1-4. Write a program to print the corresponding Celsius to Fahrenheit
table.

matxo
*/

#include <stdio.h>

int main()
{
    printf("The program prints Celsius to Fahrenheit table:\n");
    int step = 20, low = 0, top = 300;
    float cels = low, fahr;

    while (cels <= top) {
    fahr = (cels * 9.0/5.0) + 32.0;
        printf("%5.1f °C  =  %5.1f °F\n", cels, fahr);
        cels += step;
    }
    return 0;
}
