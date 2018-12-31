/*
Exercise 8-6. The standard library function calloc(n, size) returns a pointer to
n objects of size size, with the storage initialized to zero. Write calloc, by
calling malloc or by modifying it.

matxo
*/

#include <stdio.h>
#include <string.h>

typedef long Align; // for alignment to long boundary
union header { // block header
    struct {
        union header *ptr;  // next block if on free list
        unsigned size;      // size of this block
    } s;
    Align x; // force alignment of blocks
};
typedef union header Header;

static Header base; // empty list to get started
static Header *freep = NULL; // start of free list

static Header *morecore(unsigned nu);
void *mymalloc(unsigned nbytes);
void *mycalloc(unsigned objects, unsigned size);
void myfree(void *ap);

void print_free_blocks() {
    printf("%-10s%-8p\n", "base: ", &base);
    for (Header *p = base.s.ptr; p != NULL && p != &base ; p = p->s.ptr)
        printf("%-10s%-8p\n", "p: ", p);

}

// test mycalloc function
int main()
{
    char *string = "Hello World!";
    int size = strlen(string) + 1;
    void *p;

    p = mymalloc(size);
    print_free_blocks();
    printf("%-10s%-8p\n", "mymalloc: ", p);
    sprintf((char*)p, "%s", string);
    for (int i = 0; i < size; i++)
        printf("%8p: %4d\t'%c'\n", p+i, *((char *)p+i), *((char *)p+i));

    printf("\n");
    myfree(p);
    p = mymalloc(size);
    print_free_blocks();
    printf("%-10s%-8p\n", "mymalloc: ", p);
    for (int i = 0; i < size; i++)
        printf("%8p: %4d\t'%c'\n", p+i, *((char *)p+i), *((char *)p+i));
    
    printf("\n");
    myfree(p);
    p = mycalloc(size, 1);
    print_free_blocks();
    printf("%-10s%-8p\n", "mycalloc: ", p);
    for (int i = 0; i < size; i++)
        printf("%8p: %4d\t'%c'\n", p+i, *((char *)p+i), *((char *)p+i));
    return 0;
}

// mycalloc: returns a pointer to objects of size, storage initialized to zero
void *mycalloc(unsigned objects, unsigned size)
{
    void *p = mymalloc(objects * size);
    char *ptr = (char*)p;
    if (p != NULL) {
        for (int i = 0; i < (objects*size); i++)
            *(ptr++) = '\0';
    }
    return p;
}

// mymalloc: general-purpose storage allocator
void *mymalloc(unsigned nbytes)
{
    Header *p, *prevp;
    Header *moreroce(unsigned);
    unsigned nunits;

    nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;
    if ((prevp = freep) == NULL) { // no free list yet
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) { // big enough
            if (p->s.size == nunits) // exactly
                prevp->s.ptr = p->s.ptr;
            else { // allocate tail end
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p+1);
        }
        if (p == freep) // wrapped around free list
            if ((p = morecore(nunits)) == NULL)
            return NULL; // none left
    }
}

#define NALLOC 1024 // minimum #units to request

// morecore: ask system for more memory
static Header *morecore(unsigned nu)
{
    char *cp, *sbrk(int);
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1) // no space at all
        return NULL;
    up = (Header *) cp;
    up->s.size = nu;
    myfree((void *)(up+1));
    return freep;
}

// myfree: put block ap in free list
void myfree(void *ap)
{
    Header *bp, *p;

    bp = (Header *)ap - 1; // point to block header
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break; // freed block at start or end of arena

    if (bp + bp->s.size == p->s.ptr) { // join to upper nbr
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp) { // join to lower nbr
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
}