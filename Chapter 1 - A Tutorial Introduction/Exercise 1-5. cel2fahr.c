/*
Exercise 1-5. Modify the temperature conversion program to print the table in
reverse order, that is, from 300 degrees to 0.

matxo
*/

#include <stdio.h>

#define LOWER   0
#define UPPER   300
#define STEP    20

int main()
{
    printf("The program prints Celsius to Fahrenheit table in reverse order ");
    printf("- from 300 degrees to 0:\n");

    for (float cels = UPPER; cels >= LOWER; cels -= STEP) {
        printf("%5.1f °C  =  %5.1f °F\n", cels, (cels * 9.0/5.0) + 32.0);
    }
    return 0;
}
