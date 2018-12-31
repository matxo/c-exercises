/*
Exercise 5-13. Write the program tail, which prints the last n lines of its
input. By default, n is set to 10, let us say, but it can be changed by an
optional argument so that tail -n prints the last n lines. The program should
behave rationally no matter how unreasonable the input or the value of n. Write
the program so it makes the best use of available storage; lines should be
stored as in the sorting program of Section 5.6, not in a two-dimensional array
of fixed size.

matxo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_N_LINES 10
#define MAXLEN 1000
#define MAXLINES 5000
#define ALLOCSIZE 10000 // size of available space

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
int get_line(char s[], int lim);

char allocbuf[ALLOCSIZE]; // storage for alloc
char *allocp = allocbuf;  // next free position
char *lineptr[MAXLINES];  // pointers to text lines
int n_lines;

int main(int argc, char *argv[])
{
    char help[] = "tail [-n]\tprint last n lines of the input\n";
    if (argc == 1) {
        n_lines = DEFAULT_N_LINES;
    } else if (argv[1][0] == '-') {
        n_lines = -(atoi(argv[1]));
        if (n_lines <= 0) {
            printf("%s", help);
            return -1;
        }
    } else {
        printf("%s", help);
        return -1;
    }

    int read_lines = readlines(lineptr, MAXLINES);
    if (read_lines < 0) {
        printf("%s", "error: not enough memory");
        return -2;
    }
    if (read_lines >= n_lines)
        writelines(lineptr + read_lines - n_lines, n_lines);
    else
        writelines(lineptr, read_lines);
    return 0;
}

// return pointer to n characters 
char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) { // it fits
        allocp += n;
        return allocp - n; // old p
    } else // not enough room
        return 0;
}

// free storage pointed to by p
void afree(char *p)
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
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

// readlines: read input lines
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

// writelines: write output lines
void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}
