/*
Exercise 6-1. Our version of getword does not properly handle underscores,
string constants, comments, or preprocessor control lines. Write a better
version.

matxo
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 1000
#define NKEYS (sizeof keytab / sizeof(struct key))

struct key {
    char *word;
    int count;
};

struct key keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "do", 0,
    "double", 0,
    "else", 0,
    "enum", 0,
    "extern", 0,
    "float", 0,
    "for", 0,
    "goto", 0,
    "if", 0,
    "int", 0,
    "long", 0,
    "register", 0,
    "return", 0,
    "short", 0,
    "signed", 0,
    "sizeof", 0,
    "static", 0,
    "struct", 0,
    "switch", 0,
    "typedef", 0,
    "union", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};

int getword(char *, int);
int binsearch(char *, struct key *, int);

// count C keywords
int main()
{
    int n;
    char word[MAXWORD];
    
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    return 0;
}

// binsearch: find word in tab[0]...tab[n-1]
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;
    
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

// getword: get next word or character from input
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (isalpha(c) || c == '_') { // word starting with letter or underscore
        for ( ; --lim > 0; w++) {
            *w = getch();
            if (!isalnum(*w) && *w != '_') {
                ungetch(*w);
                break;
            }
        }
    } else if (c == '\'') { // character constant
        int escape = 0;
        for ( ; --lim > 0; w++) {
            *w = getch();
            if (*w == '\\') 
                escape = escape == 0 ? 1 : 0;
            else if (*w == '\'' && escape == 0) {
                escape = 0;
                w++;
                break;
            } else
                escape = 0;
        }
    } else if (c == '"') { // string constant
        int escape = 0;
        for ( ; --lim > 0; w++) {
            *w = getch();
            if (*w == '\\') 
                escape = escape == 0 ? 1 : 0;
            else if (*w == '"' && escape == 0) {
                escape = 0;
                w++;
                break;
            } else
                escape = 0;
            
        }
    } else if (c == '#') { // preprocessor
        for ( ; --lim > 0; w++) {
            if ((*w = getch()) == '\n') {
                w++;
                break;
            }
        }
    } else if (c == '/') { // comment
        *w = getch();
        if (*w == '/') { // one line comment
            w++;
            for ( ; --lim > 0; w++) {
                if ((*w = getch()) == '\n') {
                    w++;
                    break;
                }
            }
        } else if (*w == '*') { // multi line comment
            w++;
            int asterisk = 0;
            for ( ; --lim > 0; w++) {
                *w = getch();
                if (*w == '*')
                    asterisk = 1;
                else if (*w == '/' && asterisk) {
                    w++;
                    break;
                } else
                    asterisk = 0;
            }
        } else {
            ungetch(*w);
        }
    } else {
        *w = '\0';
        return c;
    }

    *w = '\0';
    return word[0];
}

#define BUFSIZE 100

char buf[BUFSIZE];  // buffer for ungetch
int bufp = 0;       // next free position in buf

int getch(void)     // get a (possibly pushed-back) character
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) // push character back on input
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}