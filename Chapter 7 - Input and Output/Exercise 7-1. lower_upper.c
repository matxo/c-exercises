/*
Exercise 7-1. Write a program that converts upper case to lower or lower case to
upper, depending on the name it is invoked with, as found in argv[0].

matxo
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

// convert input to lower/upper case depending on argv[0]
int main(int argc, char **argv) 
{
    int c;
    char *lower = "lower";
    char *upper = "upper";
    if (strcmp(argv[0], lower) == 0) {
        while ((c = getchar()) != EOF)
            putchar(tolower(c));
    } else if (strcmp(argv[0], upper) == 0) {
        while ((c = getchar()) != EOF)
            putchar(toupper(c));
    } else {
        printf("error: program should be named and invoked either: %s or %s\n",
            lower, upper);
    }
    return 0;
}
