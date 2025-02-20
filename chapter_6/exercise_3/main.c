#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100

enum { FALSE, TRUE };

struct tnode {
    char *word;
    int linenumbers[MAXWORD];
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
int isnoiseword(char *);

int linenumber = 0;

int main(void) {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) && isnoiseword(word) == FALSE)
            root = addtree(root, word);
        else if (word[0] == '\n')
            linenumber++;
    treeprint(root);

    return 0;
}

void treeprint(struct tnode *p) {
    int i;
    if (p != NULL) {
        treeprint(p->left);
        printf("%s: ", p->word);
        for (i = 0; i <= p->count - 1; i++)
            printf("%d%s", p->linenumbers[i], i == p->count - 1 ? "\n" : ", ");
        treeprint(p->right);
    }
}

struct tnode *talloc(void);
char *strcopy(char *);

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strcopy(w);
        p->linenumbers[0] = linenumber;
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->linenumbers[p->count++] = linenumber;
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

struct tnode *talloc(void) {
    return (struct tnode *)malloc(sizeof(struct tnode));
}

char *strcopy(char *s) {
    char *p;

    p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

int getword(char *word, int lim) {
    int c, d, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()) && c != '\n')
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
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

int isnoiseword(char *w) {
    static char *types[] = {"the", "and", "is", "of", "a", "an"};
    int i;

    for (i = 0; i < sizeof(types) / sizeof(types[0]); i++)
        if (strcmp(types[i], w) == 0)
            return TRUE;
    return FALSE;
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
