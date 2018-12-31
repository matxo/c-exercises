/*
Exercise 2-3. Write a function htoi(s) , which converts a string of hexadecimal
digits (including an optional 0x or 0X) into its equivalent integer value. The 
allowable digits are 0 through 9, a through f, and A through F.

matxo
*/

#include <stdio.h>
#include <ctype.h>

#define BUFFER_LINE 1000

int get_line(char s[], int lim);
unsigned long int htoi(char s[]);

int main()
{
    int len;
    char line[BUFFER_LINE];
    while ((len = get_line(line, BUFFER_LINE)) > 0) {
        printf("%lu\n", htoi(line));
    }
    return 0;
}

unsigned long int htoi(char s[])
{
    int i = 0;
    // recognize 0x or 0X at the beginning
    if (s[i] == '0' && (s[i+1] == 'x' || s[i+1] == 'X'))
        i = 2;

    char c;
    unsigned long int number = 0;
    // convert hex number to dec number and store it
    while (isxdigit(c = tolower(s[i]))) {
        if (isdigit(c))
            number = number * 16 + c - '0';
        else
            number = number * 16 + c - 'a' + 10;
        i++;
    }
    return number;
}

// get_line: read a line into s, return length
int get_line(char s[], int lim)
{
    int c, i;
    for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
