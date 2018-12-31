/*
Exercise 1-1. Run the `` hello, world '' program on your system. Experiment with
leaving out parts of the program, to see what error messages you get.

matxo
*/

                            // if a line is left out:
#include <stdio.h>              // header missing, can't recognize puts function
int main(void)                  // main always has to be present in a C program
{                               // syntax error
    printf("Hello World!\n");   // no error, but programm does nothing
}                               // syntax error
