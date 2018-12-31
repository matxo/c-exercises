/*
Exercise 6-3. Write a cross-referencer that prints a list of all words in a
document, and for each word, a list of the line numbers on which it occurs.
Remove noise words like ``the,'' ``and,'' and so on.

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
    int lines[MAXWORD];     // number of lines on which it occurs
    struct tnode *left;     // left child
    struct tnode *right;    // right child
    struct tnode *low;      // child with lower count
    struct tnode *high;     // child with higher count
};

struct tnode *addtree(struct tnode *, char *, int nline);
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode * sorttreebycount(struct tnode *root);
void addtreebycount(struct tnode *root, struct tnode *p);
void treeprintbycount(struct tnode *p);

// cross-referencer, exclude words from cli argument list
int main(int argc, char **argv)
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    int line;
    int sort;
    while ((line = getword(word, MAXWORD)) != EOF) {
        if (isalpha(word[0])) {
            sort = 1;
            for (int i = 1; i < argc; i++) { // exclude words like "the, and, a"
                if (strcmp(word, argv[i]) == 0)
                    sort = 0;
            }
            if (sort)
                root = addtree(root, word, line);
        }
    }
    sorttreebycount(root);
    treeprintbycount(root);
    return 0;
}

// getword: get next word from input, return number of line or EOF
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;
    static int nline = 1;

    while (isspace(c = getch())) {
        if (c == '\n')
            nline++;
    }
    if (c != EOF)
        *w++ = c;
    if (isalpha(c)) { // word starting with letter
        for ( ; --lim > 0; w++) {
            *w = getch();
            if (!isalnum(*w) && *w != '_') {
                ungetch(*w);
                break;
            }
        }
    } else if (c == EOF) {
        *w = '\0';
        return EOF;
    } else {
        *w = '\0';
        return nline;
    }

    *w = '\0';
    return nline;
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
struct tnode *addtree(struct tnode *p, char *w, int nline)
{
    int cond;

    if (p == NULL) {    // a new word has arrived
        p = talloc();   // make a new node
        p->word = stringdup(w);
        p->count = 1;
        p->left = p->right = NULL;

        int i = 0;
        while(i < MAXWORD)
            p->lines[i++] = 0;
        p->lines[0] = nline;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;     // repeated word
        int i = 0;
        while(i < MAXWORD && p->lines[i] != 0)
            i++;
        p->lines[i] = nline;
    }
    else if (cond < 0)  // less than into left subtree
        p->left = addtree(p->left, w, nline);
    else                // greater than into right subtree
        p->right = addtree(p->right, w, nline);
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
        printf("%4d %s\t", p->count, p->word);
        for (int i = 0; i < MAXWORD && p->lines[i] != 0; i++) {
            if (p->lines[i+1] == 0)
                printf("%d", p->lines[i]);
            else
                printf("%d, ", p->lines[i]);
        }
        printf("\n");
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
