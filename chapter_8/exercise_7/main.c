#include <stdio.h>

#define MAXBYTES 1024

void *mymalloc(unsigned);
void myfree(void *);

int main(void) {
    int *p = (int *)mymalloc(MAXBYTES + 1);

    if (p != NULL) {
        printf("address: %p, value: %d\n", &p, *p);
        myfree(p);
    }

    return 0;
}

typedef long Align;

union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;

static unsigned maxalloc;

void *mymalloc(unsigned nbytes) {
    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned nunits;

    if (nbytes > MAXBYTES) {
        fprintf(stderr, "malloc: can't allocate more than %d bytes\n",
                MAXBYTES);
        return NULL;
    }

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {
            if (p->s.size == nunits)
                prevp->s.ptr = p->s.ptr;
            else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep)
            if ((p = morecore(nunits)) == NULL)
                return NULL;
    }
}

#define NALLOC 1024

Header *morecore(unsigned nu) {
    char *cp, *sbrk(int);
    Header *up;
    void myfree(void *);

    if (nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *)-1)
        return NULL;
    up = (Header *)cp;
    up->s.size = nu;
    if (up->s.size > maxalloc)
        maxalloc = up->s.size;
    myfree((void *)(up + 1));
    return freep;
}

void myfree(void *ap) {
    Header *bp, *p;

    bp = (Header *)ap - 1;

    if (bp->s.size == 0 || bp->s.size > maxalloc) {
        fprintf(stderr, "free: can't free %d bytes\n", bp->s.size);
        return;
    }

    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;

    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
}
