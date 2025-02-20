#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define CHARNUM 6

struct tnode {
    char match[MAXWORD];
    char *words[MAXWORD];
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

int charnum;

int main(int argc, char *argv[]) {
    struct tnode *root;
    char word[MAXWORD];

    switch (argc) {
    case 1:
        charnum = CHARNUM;
        break;
    case 2:
        charnum = atoi(argv[1]);
        break;
    default:
        printf("error: incorrect number of arguments\n");
        return 1;
    }

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) && strlen(word) >= charnum)
            root = addtree(root, word);
    treeprint(root);

    return 0;
}

void treeprint(struct tnode *p) {
    int i;
    if (p != NULL) {
        treeprint(p->left);
        printf("matched on %s %d %s: ", p->match, p->count,
               p->count == 1 ? "time" : "times");
        for (i = 0; i <= p->count - 1; i++)
            printf("%s%s", p->words[i], i == p->count - 1 ? "\n" : ", ");
        treeprint(p->right);
    }
}

struct tnode *talloc(void);
char *strcopy(char *);

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;
    char s[charnum];

    strncpy(s, w, charnum);
    s[charnum] = '\0';

    if (p == NULL) {
        p = talloc();
        p->words[0] = strcopy(w);
        strncpy(p->match, w, charnum);
        p->match[charnum] = '\0';
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(s, p->match)) == 0)
        p->words[p->count++] = strcopy(w);
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
    if (isalpha(c) || c == '_' || c == '#') {
        for (; --lim > 0; w++)
            if (!isalnum(*w = getch())) {
                ungetch(*w);
                break;
            }
    } else if (c == '\'' || c == '"') {
        for (; --lim > 0; w++) {
            if ((*w = getch()) == '\\') {
                *++w = getch();
            } else if (*w == c) {
                w++;
                break;
            } else if (*w == EOF)
                break;
        }
    } else if (c == '/') {
        if ((d = getch()) == '*')
            while ((c = getch()) != EOF) {
                if (c == '*') {
                    if ((c = getch()) == '/')
                        break;
                    else
                        ungetch(c);
                }
            }
        else
            ungetch(d);
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
