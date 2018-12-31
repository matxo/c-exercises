/*
Exercise 5-17. Add a field-searching capability, so sorting may bee done on
fields within lines, each field sorted according to an independent set of
options. (The index for this book was sorted with -df for the index category and
-n for the page numbers.)

matxo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 1000     // max length of line
#define MAXLINES 5000   // max lines to be sorted
#define ALLOCSIZE 10000 // size of available space
#define MAX_FIELDS 100  // max fields within line

enum flag {FIELD, NUMERIC, REVERSE, FOLD, DIRECTORY, NUM_OF_FLAGS};
// FIELD number
// NUMERIC 1 if numeric sort
// REVERSE 1 if reverse sort
// FOLD 1 if fold sort (upper and lower case compare equal)
// DIRECTORY 1 if compares only letters, numbers and blanks

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void quicksort(void *v[], int left, int right, int (*comp)(void*, void*));
int number_cmp(char *s1, char *s2);
int string_cmp(char *s, char *t);
int string_fold_cmp(char *s, char *t);
int string_dir_cmp(char *s, char *t);
int string_dir_fold_cmp(char *s, char *t);
int field_cmp(char *s, char *t);
void get_flags(int field, char * s);
void find_field(char *field_str, char *str, int field);

char allocbuf[ALLOCSIZE]; // storage for alloc
char *allocp = allocbuf;  // next free position
char *lineptr[MAXLINES];  // pointers to text lines

int nlines; // number of input lines read
int flags[MAX_FIELDS][NUM_OF_FLAGS];
int nfields; // number of field specified for sorting

char * help = "sort -FIELDFLAGS \te.g.: sort -3fd -2n -5";

// sort input lines
int main(int argc, char *argv[])
{
    // set flags according the cli arguments
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && isdigit(argv[i][1])) {
                int field = atoi(argv[i] + 1);
                if (field < 1) {
                    printf("%s\n", help);
                    return 1;
                }
                int j = 1;
                while (isdigit(argv[i][j]))
                    j++;
                get_flags(field, argv[i] + j);
        } else {
            printf("%s\n", help);
            return 1;
        }
    }

    // sort according the set flags
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        quicksort((void**) lineptr, 0, nlines-1, 
            (int (*)(void*,void*))field_cmp);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

void get_flags(int field, char * s)
{
    nfields++;
    flags[nfields-1][FIELD] = field;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == 'n')
            flags[nfields-1][NUMERIC] = 1;
        else if (s[i] == 'r')
            flags[nfields-1][REVERSE] = 1;
        else if (s[i] == 'f')
            flags[nfields-1][FOLD] = 1;
        else if (s[i] == 'd')
            flags[nfields-1][DIRECTORY] = 1;
        else
            return;
    }
}

int field_cmp(char *s, char *t)
{
    static char s1[MAXLEN];
    static char s2[MAXLEN];
    int diff = 0;

    for (int i = 0; i < nfields && diff == 0; i++) {
        find_field(s1, s, flags[i][FIELD]);
        find_field(s2, t, flags[i][FIELD]);

        
        if (flags[i][NUMERIC])
            diff = number_cmp(s1, s2);
        else if (flags[i][FOLD] && flags[i][DIRECTORY])
            diff = string_dir_fold_cmp(s1, s2);
        else if (flags[i][FOLD] && !flags[i][DIRECTORY])
            diff = string_fold_cmp(s1, s2);
        else if (!flags[i][FOLD] && !flags[i][DIRECTORY])
            diff = string_cmp(s1, s2);
        else if (!flags[i][FOLD] && flags[i][DIRECTORY])
            diff = string_dir_cmp(s1, s2);

        if (flags[i][REVERSE])
            diff = -diff;
    }
    return diff;
}

void find_field(char *field_str, char *str, int field)
{
    int i = 0;
    while (isspace(str[i]))
        i++; // skip blanks
    if (str[i] == '\0') {
        field_str[0] = '\0'; // empty field
        return;
    } else {
        for (int f = 1; f < field; f++) {
            while (!isspace(str[i]) && str[i] != '\0') 
                i++; // skip field
            while (isspace(str[i]))
                i++; // skip blanks
        }
        if (str[i] == '\0') {
            field_str[0] = '\0'; // empty field
            return;
        } else {
            int j = 0;
            while (!isspace(str[i]) && str[i] != '\0') 
                field_str[j++] = str[i++]; // copy field
            field_str[j] = '\0';
        }
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
void quicksort(void *v[], int left, int right, int (*comp)(void*, void*))
{
    int i, last;
    void swap(void *v[], int, int);
    if (left >= right) // do nothing if array contains fewer than two elements
        return;
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    quicksort(v, left, last-1, comp);
    quicksort(v, last+1, right, comp);
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

