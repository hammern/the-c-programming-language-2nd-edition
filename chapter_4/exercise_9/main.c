#include <stdio.h>

#define BUFFSIZE 100

int getch(void);

int main(void) {
    int c;

    while ((c = getch()) != EOF)
        putchar(c);

    return 0;
}

/*
 * getch and ungetch do not handle a pushed-back EOF because buf is a char[]
 * which can only store positive ints while EOF is equal to -1. By changing buf
 * to an int[] we can handle EOF.
 */
int bufp = 0;
int buf[BUFFSIZE];

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
    if (bufp >= BUFFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
