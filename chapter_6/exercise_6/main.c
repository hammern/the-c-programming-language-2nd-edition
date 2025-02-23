#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100

#define NOTDEFINED 42
#undef NOTDEFINED

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

int getword(char *, int);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
void undef(char *);
void print_hashtable(void);

int main(void) {
    struct nlist *np;
    char word[MAXWORD];
    char *key;

    while (getword(word, MAXWORD) != EOF)
        if (strcmp(word, "#") == 0) {
            getword(word, MAXWORD);
            if (strcmp(word, "define") == 0) {
                getword(word, MAXWORD);
                key = strdup(word);
                getword(word, MAXWORD);
                install(key, word);
            } else if (strcmp(word, "undef") == 0) {
                getword(word, MAXWORD);
                undef(word);
            }
        }

    print_hashtable();

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

int getword(char *word, int lim) {
    int c, d, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalnum(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return c;
}

void print_hashtable(void) {
    int i;
    for (i = 0; i < HASHSIZE; i++)
        if (hashtab[i] != NULL)
            printf("%s->%s\n", hashtab[i]->name, hashtab[i]->defn);
}

#define BUFFSIZE 100

int bufp = 0;
char buf[BUFFSIZE];

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
    if (bufp >= BUFFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
