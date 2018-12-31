/*
Exercise 1-23. Write a program to remove all comments from a C program. Don't
forget to handle quoted strings and character constants properly. C comments
don't nest.

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
    bool escape_seq = false;
    bool asterisk = false;          // last character was asterisk
    bool slash = false;             // last character was slash
    char remebered_char = '\0';     // last character - asterisk or slash
    bool comment_line = false;
    bool change_from_block = false; // change from block comment to normal text
    bool comment_block = false;

    char line[BUFFER_LINE];
    int len;
    while ((len = get_line(line, BUFFER_LINE)) > 0) {
        for(int i = 0; line[i] != '\0'; i++) {
            switch (line[i]) {
            case '"':
                if (!comment_block && !comment_line && !character) { // if valid
                    if (!string)
                        string = true;
                    else if (string && !escape_seq)
                        string = false;
                }
                break;

            case '\'':
                if (!comment_block && !comment_line && !string) { // if valid
                    if (!character)
                        character = true;
                    else if (character && !escape_seq)
                        character = false;
                }
                break;

            case '/':
                if (!string && !character && !comment_block && !comment_line &&
                    !slash) {
                    slash = true;
                } else if (!string && !character && !comment_block &&
                    !comment_line && slash) {
                    comment_line = true;
                    remebered_char = '\0';
                } else if (comment_block && asterisk) {
                    comment_block = false;
                    change_from_block = true;
                }
                break;

            case '\\':
                if (string || character) // if valid
                    escape_seq = (escape_seq) ? false : true;
                break;

            case '*':
                if (!string && !character && !comment_line && !comment_block
                    && slash) {
                    comment_block = true;
                    remebered_char = '\0';
                } else if (comment_block) {
                    asterisk = true;
                }
                break;
            }

            // null variables
            if (line[i] != '*')
                asterisk = false;
            if (line[i] != '/')
                slash = false;
            if (line[i] != '\\')
                escape_seq = false;

            // putchar if outside any comment
            if (!comment_block && !comment_line && !slash && !asterisk && 
                    !change_from_block) 
            {
                if (remebered_char != '\0') {
                    putchar(remebered_char);
                    remebered_char = '\0';
                }
                putchar(line[i]);
            } else if (!comment_line && slash == true) {
                remebered_char = '/';
            } else if (!comment_block && asterisk == true) {
                remebered_char = '*';
            } 
        }
        if (comment_line) {
            comment_line = false;
            putchar('\n');
        } 
        change_from_block = false;
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
