/*
Exercise 7-7. Modify the pattern finding program of Chapter 5 to take its input
from a set of named files or, if no files are named as arguments, from the
standard input. Should the file name be printed when a matching line is found?

matxo
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// find: print lines that match pattern from 1st arg, use files or stdin
int main(int argc, char *argv[])
{
    char *line = NULL;
    size_t size;
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;

    while (--argc > 0 && (*++argv)[0] == '-'){
        while (c = *++argv[0]) {
            switch (c) {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                printf("find: illegal option %c\n", c);
                argc = 0;
                found = -1;
                break;
            }
        }
    }
    if (argc < 1)
        printf("Usage: find -x -n pattern [file1] [file2] [...]\n");
    else {
        char *pattern = *argv;
        argc--;
        FILE* file;
        int file_name = 0;

        if (argc == 0) // use stdin
            file = stdin;
        if (argc > 1) // print also file names 
            file_name = 1;

        do {
            if (argc >= 1) { // at least one file
                if ((file = fopen(*++argv, "r")) == NULL) {
                    fprintf(stderr, "error: can't open file %s\n", *argv);
                    exit(1);
                }
                argc--;
            }
            while (getline(&line, &size, file) > 0) {
                lineno++;
                if ((strstr(line, pattern) != NULL) != except) {
                    if (file_name)
                        printf("%s: ", *argv);
                    if (number)
                        printf("%ld:", lineno);
                    printf("%s", line);
                    found++;
                }
            }
        } while (argc >= 1);
    }
    return found;
}