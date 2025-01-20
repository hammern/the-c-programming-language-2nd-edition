#include <stdio.h>

int main(void) {
    int c, prev;

    while ((c = getchar()) != EOF) {
        if (c != ' ' || prev != ' ')
            putchar(c);

        prev = c;
    }

    return 0;
}
