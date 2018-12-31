/*
Exercise 7-8. Write a program to print a set of files, starting each new one on
a new page, with a title and a running page count for each file.

matxo
*/

#include <stdio.h>
#include <stdlib.h>

// print files formated
int main(int argc, char *argv[]) {
    FILE *fp;
    void filecopy(FILE *, FILE *);
    char *prog = argv[0]; // program name for errors
    
    if (argc == 1 ) { // no args;
        fprintf(stderr, "%s: no files provided as arguments\n", prog);
        exit(3);
    }

    char* lineptr = NULL;
    size_t n;
    int nline, npage, maxline;
    npage = nline = 1;
    maxline = 20;

    while (--argc > 0) {
        if ((fp = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", prog, *argv);
            exit(1);
        }
        while (getline(&lineptr, &n, fp) != EOF) {
            printf("%s", lineptr);
            nline++;
            if (nline > maxline) {
                printf("--- %s -%d.- ---\n\n\n", *argv, npage);
                npage++;
                nline = 1;
            }
        }
        
        while (nline++ <= maxline)
            printf("\n");
        printf("--- %s -%d.- ---\n\n\n", *argv, npage);
        fclose(fp);
        npage = nline = 1;
    }
    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }
    exit(0);
}


