#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define LIMIT 1000

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
int getword(char *, int);
void tree_to_nodes(struct tnode *);
void sort_nodes(void);
void nodes_print(void);

struct tnode *nodes[LIMIT];
int nodenum = 0;

int main(void) {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);

    tree_to_nodes(root);
    sort_nodes();
    nodes_print();

    return 0;
}

void tree_to_nodes(struct tnode *p) {
    if (p != NULL) {
        tree_to_nodes(p->left);
        if (nodenum < LIMIT)
            nodes[nodenum++] = p;
        tree_to_nodes(p->right);
    }
}

int cmp(const void *a, const void *b) {
    struct tnode *nodeA = *(struct tnode **)a;
    struct tnode *nodeB = *(struct tnode **)b;
    return nodeB->count - nodeA->count;
}

void sort_nodes() { qsort(nodes, nodenum, sizeof(struct tnode *), cmp); }

void nodes_print() {
    int i;
    for (i = 0; i < nodenum - i; i++)
        printf("%4d %s\n", nodes[i]->count, nodes[i]->word);
}

struct tnode *talloc(void);
char *strcopy(char *);

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strcopy(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
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

    while (isspace(c = getch()))
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
