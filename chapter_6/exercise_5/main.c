#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

struct nlist *lookup(char *);
struct nlist *install(char *, char *);
void undef(char *);

int main(void) {
    struct nlist *np;

    install("in", "1");
    install("HASHSIZE", "101");
    install("BUFFSIZE", "100");

    np = lookup("HASHSIZE");
    printf("%s: %s\n", np->name, np->defn);

    undef("HASHSIZE");
    np = lookup("HASHSIZE");
    if (np == NULL)
        printf("HASHSIZE not found\n");

    return 0;
}

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else
        free((void *)np->defn);
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

void undef(char *s) {
    struct nlist *np;

    np = lookup(s);
    if (np == NULL)
        return;

    if (np->next != NULL) {
        np->next = np->next->next;
        np = np->next;
    } else {
        hashtab[hash(s)] = NULL;
        free((void *)np->name);
        free((void *)np->defn);
        free((void *)np);
    }
}
