/*
Exercise 6-4. Write a program that prints the distinct words in its input sorted
into decreasing order of frequency of occurrence. Precede each word by its
count.

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
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode * sorttreebycount(struct tnode *root);
void addtreebycount(struct tnode *root, struct tnode *p);
void treeprintbycount(struct tnode *p);

// word frequency count
int main()
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);
    sorttreebycount(root);
    treeprintbycount(root);
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

// sorttreebycount: walk the tree and make binari tree by count
struct tnode * sorttreebycount(struct tnode *root)
{
    static struct tnode * realroot = NULL;
    if (realroot == NULL)
        realroot = root;
    if (root != NULL) {
        if (root->left != NULL) {
            addtreebycount(realroot, root->left);
            sorttreebycount(root->left);
        }
        if (root->right != NULL) {
            addtreebycount(realroot, root->right);
            sorttreebycount(root->right);
        }
    }
    return realroot;
}

// addtree: add a node with count, and then word, at or below root
void addtreebycount(struct tnode *root, struct tnode *p)
{
    if (p != NULL && root != NULL && root != p) {
        if (root->count < p->count) {
            if (root->high == NULL)
                root->high = p;
            else
                addtreebycount(root->high, p);
        } else if (root->count > p->count) {
            if (root->low == NULL)
                root->low = p;
            else
                addtreebycount(root->low, p);
        } else { // sort by word
            if (strcmp(root->word, p->word) >= 0) {
                if (root->high == NULL)
                    root->high = p;
                else
                    addtreebycount(root->high, p);
            } else {
                if (root->low == NULL)
                    root->low = p;
                else
                    addtreebycount(root->low, p);
            }
        }
    }
}

// treeprint: in-order print of tree p
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

// treeprintbycount: in (count)-order print of tree p
void treeprintbycount(struct tnode *p)
{
    if (p != NULL) {
        treeprintbycount(p->high);
        printf("%4d %s\n", p->count, p->word);
        treeprintbycount(p->low);
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
