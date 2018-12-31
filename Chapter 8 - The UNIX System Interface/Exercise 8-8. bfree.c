/*
Exercise 8-8. Write a routine bfree(p,n) that will free any arbitrary block p of
n characters into the free list maintained by malloc and free. By using bfree, a
user can add a static or external array to the free list at any time.

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

static char stdfdfdring[] = "Hello World! is equal to Namaste Duniya!";
static Header base; // empty list to get started
static Header *freep = NULL; // start of free list

static Header *morecore(unsigned nu);
void *mymalloc(unsigned nbytes);
void *mycalloc(unsigned objects, unsigned size);
void myfree(void *ap);
int bfree(void *ap, unsigned n);

static int static_array1[20]; 
static int static_array2[20]; 

void print_free_blocks() {
    printf("%-10s%-8p\n", "base: ", &base);
    for (Header *p = base.s.ptr; p != NULL && p != &base ; p = p->s.ptr)
        printf("%-10s%-8p\n", "p: ", p);

}

// test bfree function
int main()
{
    void *p;
    print_free_blocks();
    printf("%-10s%-8p\n", "static_array1: ", static_array1);
    printf("size of static_array1: %ld\n", sizeof(static_array1));
    printf("bfree returns: %d\n", bfree(static_array1, sizeof(static_array1)));
    print_free_blocks();

    printf("\n");
    p = mymalloc(1);
    print_free_blocks();
    printf("%-10s%-8p\n", "mymalloc: ", p);
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

#define NALLOC 1024 // minimum #units to request
#define MAXBYTES (NALLOC*NALLOC)

// mymalloc: general-purpose storage allocator, check max size of nbytes
void *mymalloc(unsigned nbytes)
{
    if (nbytes > MAXBYTES && nbytes == 0)
        return NULL;

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

    if (bp->s.size < NALLOC || bp->s.size > MAXBYTES/sizeof(Header))
        return; // if size is invalid
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
    freep = bp;
}

// bfree: free any arbitrary block p of n characters into the free list
//  returns number of bytes freed;
int bfree(void *ap, unsigned n)
{
    if (ap == NULL || n < sizeof(Header)*2)
        return 0;

    unsigned nunits = ((n-sizeof(Header))+sizeof(Header)-1)/sizeof(Header) + 1;
    while (nunits*(sizeof(Header)) > n)
        nunits--;

    Header *up = (Header *) ap;
    up->s.size = nunits;

    if (freep == NULL) { // no free list yet
        base.s.ptr = up;
        freep = up;
        up->s.ptr = &base;
        base.s.size = 0;
    } else {
        myfree((void *)(up+1));
    }
    return nunits*sizeof(Header);
}