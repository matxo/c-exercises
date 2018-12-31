/*
Exercise 5-16. Add the -d (``directory order'') option, which makes comparisons
only on letters, numbers and blanks. Make sure it works in conjunction with -f.

matxo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 1000
#define MAXLINES 5000    // max lines to be sorted
#define ALLOCSIZE 10000  // size of available space

char *lineptr[MAXLINES]; // pointers to text lines

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void quicksort(void *lineptr[], int left, int right,
    int (*comp)(void *, void *), int reverse);
int number_cmp(char *s1, char *s2);
int string_cmp(char *s, char *t);
int string_fold_cmp(char *s, char *t);
int string_dir_cmp(char *s, char *t);
int string_dir_fold_cmp(char *s, char *t);

char allocbuf[ALLOCSIZE]; // storage for alloc
char *allocp = allocbuf;  // next free position
char *lineptr[MAXLINES];  // pointers to text lines

// sort input lines
int main(int argc, char *argv[])
{
    int nlines;        // number of input lines read
    int numeric = 0;   // 1 if numeric sort
    int reverse = 0;   // 1 if reverse sort
    int fold = 0;      // 1 if fold sort (upper and lower case compare equal)
    int directory = 0; // 1 if compares only letters, numbers and blanks
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (int j = 1; argv[i][j] != '\0'; j++) {
                if (argv[i][j] == 'n')
                    numeric = 1;
                else if (argv[i][j] == 'r')
                    reverse = 1;
                else if (argv[i][j] == 'f')
                    fold = 1;
                else if (argv[i][j] == 'd')
                    directory = 1;
            }
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        if (fold && directory)
            quicksort((void**) lineptr, 0, nlines-1,
            (int (*)(void*,void*))(numeric ? number_cmp : string_dir_fold_cmp),
            reverse);
        else if (fold && !directory)
            quicksort((void**) lineptr, 0, nlines-1,
            (int (*)(void*,void*))(numeric ? number_cmp : string_fold_cmp),
            reverse);
        else if (!fold && !directory)
            quicksort((void**) lineptr, 0, nlines-1, 
            (int (*)(void*,void*))(numeric ? number_cmp : string_cmp), 
            reverse);
        else if (!fold && directory)
            quicksort((void**) lineptr, 0, nlines-1, 
            (int (*)(void*,void*))(numeric ? number_cmp : string_dir_cmp), 
            reverse);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

// number_cmp: compare s1 and s2 numerically
int number_cmp(char *s1, char *s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

// string_cmp: return <0 if s<t, 0 if s==t, >0 if s>t
int string_cmp(char *s, char *t)
{
    for ( ; *s == *t; s++, t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}

// string_fold_cmp: return <0 if s<t, 0 if s==t, >0 if s>t
//      fold upper and lower case together, so that case difference is ignored
int string_fold_cmp(char *s, char *t)
{
    for ( ; tolower(*s) == tolower(*t); s++, t++)
        if (*s == '\0')
            return 0;
    return tolower(*s) - tolower(*t);
}

// string_dir_cmp: return <0 if s<t, 0 if s==t, >0 if s>t
//      directory order - compares only letters, numbers and blanks
int string_dir_cmp(char *s, char *t)
{
    for(;;) {
        // skip other than letters, numbers and blanks
        while (!isalnum(*s) && *s != ' ' && *s != '\0')
            s++;
        while (!isalnum(*t) && *t != ' ' && *t != '\0')
            t++;
        if (*s == '\0')
            return 0;
        if (*s == *t) {
            s++, t++;
            continue;
        } else {
            break;
        }
    } 
    return *s - *t;
}

// string_dir_fold_cmp: return <0 if s<t, 0 if s==t, >0 if s>t
//      fold upper and lower case together, so that case difference is ignored
//      directory order - compares only letters, numbers and blanks
int string_dir_fold_cmp(char *s, char *t)
{
    for(;;) {
        // skip other than letters, numbers and blanks
        while (!isalnum(*s) && *s != ' ' && *s != '\0')
            s++;
        while (!isalnum(*t) && *t != ' ' && *t != '\0')
            t++;
        if (*s == '\0')
            return 0;
        if (tolower(*s) == tolower(*t)) {
            s++, t++;
            continue;
        } else {
            break;
        }
    } 
    return tolower(*s) - tolower(*t);
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

// quicksort: sort v[left]...v[right] into increasing order(r=0)/decreasing(r=1)
void quicksort(void *v[], int left, int right, int (*comp)(void *, void *), 
    int reverse)
{
    int i, last;
    void swap(void *v[], int, int);
    if (left >= right) // do nothing if array contains fewer than two elements
        return;
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (reverse) {
            if ((*comp)(v[i], v[left]) > 0)
                swap(v, ++last, i);
        } else {
            if ((*comp)(v[i], v[left]) < 0)
                swap(v, ++last, i);
        }
    swap(v, left, last);
    quicksort(v, left, last-1, comp, reverse);
    quicksort(v, last+1, right, comp, reverse);
}

void swap(void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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
            line[len-1] = '\0'; // delete newline
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

