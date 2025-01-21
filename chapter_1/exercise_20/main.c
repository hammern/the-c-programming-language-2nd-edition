#include <stdio.h>

void detab(int tabstop) {
    int c, i;

    while ((c = getchar()) != EOF) {
        if (c == '\t')
            for (i = tabstop; i > 0; --i)
                putchar(' ');
        else
            putchar(c);
    }
}

int main(void) {
    detab(4);

    return 0;
}
