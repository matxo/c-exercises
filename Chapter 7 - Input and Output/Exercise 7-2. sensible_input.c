/*
Exercise 7-2. Write a program that will print arbitrary input in a sensible way.
As a minimum, it should print non-graphic characters in octal or hexadecimal
according to local custom, and break long text lines.

matxo
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 20

int c;
int length;
char binary[MAX_LENGTH*10];
char text[MAX_LENGTH*2];
char tmp[MAX_LENGTH];

// copy input to output, break long text lines, non printable characters will be
// converted to hexadecimal or octal according the cli argument, default 0x
int main(int argc, char **argv) 
{
    char *conversion = "%02x ";
    if (argc >= 2 && strcmp(argv[1], "-o") == 0)
        conversion = "%03o ";

    while ((c = getchar()) != EOF) {
        sprintf(tmp, conversion, (int)c);
        strcat(binary, tmp);
        if (isprint(c))
            text[length] = c;
        else
            text[length] = ' ';
        
        if (c == '\n' || (length >= MAX_LENGTH)) {
            printf("%-70s\t%s\n", binary, text);
            binary[0] = '\0';
            length = 0;
        } else
            length++;
    }
    
    return 0;
}
