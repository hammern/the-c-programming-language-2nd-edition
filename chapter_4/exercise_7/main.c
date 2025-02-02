#include <stdio.h>
#include <string.h>

#define BUFFSIZE 100

int getch(void);
void ungets(char[]);

int main(void) {
    int c;

    ungets("this is a test");

    while ((c = getch()) != EOF)
        putchar(c);

    return 0;
}

int bufp = 0;
char buf[BUFFSIZE];

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
    if (bufp >= BUFFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/*
 * ungets should use ungetch as it offers additional validation on top of buf
 * and bufp
 */
void ungets(char s[]) {
    int i;

    for (i = strlen(s); i >= 0; i--)
        ungetch(s[i]);
}
