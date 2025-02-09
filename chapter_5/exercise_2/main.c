#include <ctype.h>
#include <stdio.h>

#define SIZE 1
#define BUFFSIZE 100

int getch(void);
void ungetch(int);
int getfloat(float *);

int main(void) {
    int n;
    float array[SIZE];

    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
        ;

    for (n = 0; n < SIZE; n++)
        printf("%f\n", array[n]);

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

int getfloat(float *pf) {
    int c, sign, prev;
    float power;

    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        prev = c;

        if (!isdigit(c = getch()) && c != '.') {
            ungetch(prev);
            return 0;
        }
    }
    for (*pf = 0; isdigit(c); c = getch())
        *pf = 10 * *pf + (c - '0');

    if (c == '.')
        c = getch();

    for (power = 1.0; isdigit(c); c = getch()) {
        *pf = 10.0 * *pf + (c - '0');
        power *= 10.0;
    }

    *pf *= sign / power;
    if (c != EOF)
        ungetch(c);
    return c;
};
