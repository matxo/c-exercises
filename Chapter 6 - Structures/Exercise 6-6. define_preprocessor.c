/*
Exercise 6-6. Implement a simple version of the #define processor (i.e., no
arguments) suitable for use with C programs, based on the routines of this
section. You may also find getch and ungetch helpful.

matxo
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define HASHSIZE 101
#define MAXWORD 100

static struct nlist *hashtab[HASHSIZE]; // pointer table
int getword(char *word, int lim);
struct nlist *install(char *name, char *defn);
struct nlist *lookup(char *s);
void undef(char *s);
int getch(void);
void ungetch(int c);

struct nlist { // table entry:
    struct nlist *next; // next entry in chain
    char *name;         // defined name
    char *defn;         // replacement text
};

// #define, #undef preprocessor, also removes comments
int main()
{
    char w[MAXWORD];
    char name[MAXWORD];
    char defn[MAXWORD];
    char c;

    while ((c = getch()) != EOF) {
        // word starting with letter or underscore
        if (isalpha(c) || c == '_') {
            w[0] = c;
            for (int i = 1; i < MAXWORD; i++) {
                c = getch();
                if (!isalnum(c) && c != '_') {
                    w[i] = '\0';
                    ungetch(c);
                    struct nlist * l = lookup(w);
                    if (l != NULL)
                        strcpy(w, l->defn); // replace a word if defined
                    break;
                } else
                    w[i] = c;
            }
            printf("%s", w);
        } else if (c == '\'') { // character constant
            putchar(c);
            int escape = 0;
            while (c = getch()) {
                if (c == '\\') {
                    escape = escape == 0 ? 1 : 0;
                } else if (c == '\'' && escape == 0) {
                    putchar(c);
                    break;
                } else {
                    escape = 0;
                }
                putchar(c);
            }
        } else if (c == '"') { // string constant
            putchar(c);
            int escape = 0;
            while (c = getch()) {
                if (c == '\\') 
                    escape = escape == 0 ? 1 : 0;
                else if (c == '"' && escape == 0) {
                    putchar(c);
                    break;
                } else
                    escape = 0;
                putchar(c);
            }
        } else if (c == '#') { // preprocessor
            w[0] = c;
            for (int i = 1; i < MAXWORD; i++) { // get preprocessor directive
                c = getch();
                if (isalpha(c))
                    w[i] = c;
                else {
                    w[i] = '\0';
                    ungetch(c);
                }
            }
            printf("%s", w);
            // validate it preprocessor directive
            int define;
            if (strcmp(w, "#define") == 0)
                define = 1;
            else if (strcmp(w, "#undef") == 0)
                define = -1;
            else
                continue;
            // skip blanks
            while((c = getch()) == ' ' || c == '\t') 
                putchar(c);
            // get defined word
            if (isalpha(c) || c == '_') {
                name[0] = c;
                for (int i = 1; i < MAXWORD; i++) {
                    c = getch();
                    if (isalnum(c) || c == '_')
                        name[i] = c;
                    else {
                        name[i] = '\0';
                        ungetch(c);
                    }
                }
            } else {
                ungetch(c);
                continue;
            }
            printf("%s", name);

            if (define == 1) { // #define
                // skip blanks
                while((c = getch()) == ' ' || c == '\t') 
                    putchar(c);
                ungetch(c);
                // read defn till end of line
                for (int i = 0; i < MAXWORD; i++) {
                    c = getch();
                    if (c == '\n' || c == EOF) {
                        defn[i] = '\0';
                        ungetch(c);
                    } else {
                        defn[i] = c;
                        putchar(c);
                    }
                }
                install(name, defn);
            } else if (define == -1) { // #undef
                undef(name);
                continue;
            }
        } else if (c == '/') { // comment
            int c2 = getch();
            if (c2 == '/') { // one line comment
                while (c = getch()) { // ignore till end of the line
                    if (c == '\n') {
                        ungetch(c);
                        break;
                    } else if (c == EOF) {
                        ungetch(c);
                        break;
                    }
                }
            } else if (c2 == '*') { // multi line comment
                int asterisk = 0;
                while (c = getch()) {
                    if (c == '*')
                        asterisk = 1;
                    else if (asterisk && c == '/')
                        break;
                    else
                        asterisk = 0;
                }
            } else { // just a slash
                ungetch(c2);
                putchar(c);
            }
        } else {
            putchar(c);
        }
    }
    return 0;
}

// hash: form hash value for string s
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

// undef: remove a name and defn from the table hashtab
void undef(char *s)
{
    struct nlist *prev;
    struct nlist *np;
    int hashval = hash(s);

    for (prev = np = hashtab[hashval]; np != NULL; prev = np, np = np->next)
        if (strcmp(s, np->name) == 0) {
            prev->next = np->next;
            free(np->name);
            free(np->defn);
            free(np);
            hashtab[hashval] = NULL;
            break;
        }
}

// lookup: look for s in hashtab
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
        return np; // found
    return NULL;   // not found
}

struct nlist *lookup(char *);
char *stringdup(char *);

// install: put (name, defn) in hashtab
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;
    
    if ((np = lookup(name)) == NULL) { // not found
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else // already there
        free((void *) np->defn); // free previous defn
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
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
