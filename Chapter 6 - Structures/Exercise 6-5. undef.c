/*
Exercise 6-5. Write a function undef that will remove a name and definition from
the table maintained by lookup and install.

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

struct nlist { // table entry:
    struct nlist *next; // next entry in chain
    char *name;         // defined name
    char *defn;         // replacement text
};

// test function undef that will remove a name and defn from the table hashtab
int main()
{

    char test1[] = "test1";
    char test2[] = "test2";

    install(test1, test2);
    printf("install: \"%s\" \"%s\"\n", test1, test2);

    struct nlist *l1 = lookup(test1);
    printf("lookup: \"%s\" \"%s\"\n", l1->name, l1->defn);

    undef(test1);
    printf("undef: \"%s\"\n", test1);
    
    struct nlist *l2 = lookup(test1);
    if (l2 == NULL)
        printf("lookup: NULL\n");
    else
        printf("lookup: \"%s\" \"%s\"\n", l2->name, l2->defn);
    
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

