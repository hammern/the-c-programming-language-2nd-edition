#include <stdio.h>

int getch(void);

int main(void) {
    int c;

    while ((c = getch()) != EOF)
        putchar(c);

    return 0;
}

char buf = -1;

int getch(void) {
    int temp;

    if (buf != -1) {
        temp = buf;
        buf = -1;
        return temp;
    }

    return getchar();
}

void ungetch(int c) {
    if (buf != -1)
        printf("ungetch: too many characters\n");
    else
        buf = c;
}
