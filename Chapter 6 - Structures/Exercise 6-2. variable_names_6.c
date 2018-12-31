/*
Exercise 6-2. Write a program that reads a C program and prints in alphabetical
order each group of variable names that are identical in the first 6 characters,
but different somewhere thereafter. Don't count words within strings and
comments. Make 6 a parameter that can be set from the command line.

matxo
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct tnode {          // the tree node:
    char *word;             // points to the text
    int count;              // number of occurrences
    struct tnode *left;     // left child
    struct tnode *right;    // right child
    struct tnode *low;      // child with lower count
    struct tnode *high;     // child with higher count
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *p, int chars_to_match);
int getword(char *, int);

// print variables that are identical in first "chars_to_match"
int main(int argc, char **argv)
{
    int chars_to_match = 6;
    if (argc >= 2) {
        int n;
        if ((n = atoi(argv[1])) > 0 )
            chars_to_match = n;
    }
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);
    treeprint(root, chars_to_match);
    return 0;
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

struct tnode *talloc(void);
char *stringdup(char *);

// addtree: add a node with w, at or below p
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {    // a new word has arrived
        p = talloc();   // make a new node
        p->word = stringdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;     // repeated word
    else if (cond < 0)  // less than into left subtree
        p->left = addtree(p->left, w);
    else                // greater than into right subtree
        p->right = addtree(p->right, w);
    return p;
}

void print_node(char* word, int chars_to_match)
{
    static char *previous;
    static int wasprinted; // 1 if last word was printed
    
    int lenght = strlen(word);
    
    if (previous == NULL) {
        if (lenght > chars_to_match)
            previous = word;
        wasprinted = 0;
        return;
    } else { 
        if (lenght > chars_to_match && // word long enough
            strncmp(previous, word, chars_to_match) == 0 && // first chars same
            strcmp(previous, word) != 0) // but different somewhere thereafter
        {
            printf("%s\n", previous);
            previous = word;
            wasprinted = 1;
        } else {
            if (wasprinted) {
                printf("%s\n\n", previous);
                wasprinted = 0;
            } else {
                if (lenght > chars_to_match)
                    previous = word;
            }
        }
    }
}

// treeprint: in-order print of tree p
void treeprint(struct tnode *p, int chars_to_match)
{
    if (p != NULL) {
        treeprint(p->left, chars_to_match);
        print_node(p->word, chars_to_match);
        treeprint(p->right, chars_to_match);
    }
}

// talloc: make a tnode
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

// stringdup: make a duplicate of s
char *stringdup(char *s)
{
    char *p;
    
    p = (char *) malloc(strlen(s)+1); // +1 for '\0'
    if (p != NULL)
        strcpy(p, s);
    return p;
}
