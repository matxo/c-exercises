/*
Exercise 1-24. Write a program to check a C program for rudimentary syntax
errors like unmatched parentheses, brackets and braces. Don't forget about
quotes, both single and double, escape sequences, and comments. (This program is
hard if you do it in full generality.)

matxo
*/

#include <stdio.h>
#include <stdbool.h>

#define BUFFER_LINE 10000

int get_line(char s[], int lim);

int main()
{
    bool string = false;
    bool character = false;
    bool comment_block = false;
    bool comment_line = false;

    bool escape = false;
    bool asterisk = false;  // last character was asterisk
    bool slash = false;     // last character was slash

    int parentheses = 0;    // ()
    int brackets = 0;       // []
    int braces   = 0;       // {}

    char line[BUFFER_LINE];
    int len;
    while ((len = get_line(line, BUFFER_LINE)) > 0) {
        for(int i = 0; line[i] != '\0'; i++) {
            switch (line[i]) {
            case '"':
                if (!comment_block && !comment_line && !character) { // if valid
                    if (!string) {
                        string = true;
                    } else if (string && !escape) {
                        string = false;
                    }
                }
                break;

            case '\'':
                if (!comment_block && !comment_line && !string) { // if valid
                    if (!character) {
                        character = true;
                    } else if (character && !escape) {
                        character = false;
                    }
                }
                break;

            case '/':
                if (!string && !character &&  !comment_block && !comment_line &&
                    !slash) {
                    slash = true;
                } else if (!string && !character && !comment_block &&
                    !comment_line && slash) {
                    comment_line = true;
                } else if (comment_block && asterisk) {
                    comment_block = false;
                }
                break;

            case '\\':
                if (string || character) // if valid
                    escape = (escape) ? false : true;
                break;

            case '*':
                if (!string && !character && !comment_line && !comment_block &&
                    slash) {
                    comment_block = true;
                } else if (comment_block) {
                    asterisk = true;
                }
                break;

            default:
                if (!comment_line && !comment_block && !string && !character) {
                    switch (line[i]) {
                    case '{' :
                        braces++;
                        break;
                    case '}' :
                        braces--;
                        break;
                    case '[' :
                        brackets++;
                        break;
                    case ']' :
                        brackets--;
                        break;
                    case '(' :
                        parentheses++;
                        break;
                    case ')' :
                        parentheses--;
                        break;
                    }
                }
                break;
            }

            // null variables
            if (line[i] != '*')
                asterisk = false;
            if (line[i] != '/')
                slash = false;
            if (line[i] != '\\')
                escape = false;
        }
        comment_line = false;

    } while (len > 0);

    if (parentheses == 0 && brackets == 0 && braces == 0) {
        printf("***There is balance***\n");
    } else {
        printf("***Sorry, there is no balance***\n");
        printf("parentheses () = %2d\n", parentheses);
        printf("   brackets [] = %2d\n", brackets);
        printf("     braces {} = %2d\n", braces);
    }
    return 0;
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
