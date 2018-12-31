/*
Exercise 7-6. Write a program to compare two files, printing the first line
where they differ.

matxo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// compare two files and print first line where they differ
int main(int argc, char**argv)
{
    FILE *file1, *file2;

    if (argc < 3) {
        fprintf(stderr, "%s", "compare: [file1] [file2]\n");
        exit(2);
    }
    if ((file1 = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "error: can't open file %s\n", argv[1]);
        exit(1);
    }
    if ((file2 = fopen(argv[2], "r")) == NULL) {
        fprintf(stderr, "error: can't open file %s\n", argv[2]);
        exit(1);
    }

    char *lineptr1 = NULL;
    char *lineptr2 = NULL;
    size_t n1, n2;
    int isEOF = 0;
    while (!isEOF) {
        if (getline(&lineptr1, &n1, file1) == EOF)
            isEOF = 1;
        if (getline(&lineptr2, &n2, file2) == EOF) 
            isEOF = 1;
        if (strcmp(lineptr1, lineptr2) != 0) {
            printf("%s: %s", argv[1], lineptr1);
            printf("%s: %s", argv[2], lineptr2);
            exit(3);
        }
    }

    fclose(file1);
    fclose(file2);
    exit(0);
}
