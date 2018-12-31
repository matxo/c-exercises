/*
Exercise 5-7. Rewrite readlines to store lines in an array supplied by main,
rather than calling alloc to maintain storage. How much faster is the program?

matxo
*/

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000           // max #lines to be sorted
#define STORAGE_SIZE 5000000    // max characters to be stored

char storage[STORAGE_SIZE];
char *lineptr[MAXLINES];    // pointers to text lines

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

// sort input lines
int main()
{
    int nlines;     // number of input lines read
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000 // max length of any input line
int get_line(char s[], int lim);

// readlines: read input lines
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p = storage;
    char line[MAXLEN];
    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p+len > p+STORAGE_SIZE-1))
            return -1;
        else {
            line[len-1] = '\0'; // delete newline
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    return nlines;
}

// get_line: read a line into s, return length
int get_line(char s[], int lim)
{
    int c;
    char *sp;
    for (sp = s; sp-s < lim-1 && (c=getchar())!=EOF && c!='\n'; sp++) {
        *sp = c;
    }
    if (c == '\n')
        *sp++ = c;
    *sp = '\0';
    return sp-s;
}

// writelines: write output lines
void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

// qsort: sort v[left]...v[right] into increasing order
void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);
    if (left >= right)  // do nothing if array contains
        return;         // fewer than two elements
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);

    qsort(v, last+1, right);
}

// swap: interchange v[i] and v[j]
void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
