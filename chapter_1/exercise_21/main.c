#include <stdio.h>

void entab(int tabstop) {
    int c, i, blank_count;

    blank_count = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ')
            ++blank_count;
        else {
            if (blank_count < tabstop) {
                for (; blank_count > 0; --blank_count)
                    putchar(' ');
            } else {
                for (i = blank_count / tabstop; i > 0; --i)
                    putchar('\t');

                for (i = blank_count % tabstop; i > 0; --i)
                    putchar(' ');
            }

            blank_count = 0;
            putchar(c);
        }
    }
}

int main(void) {
    entab(4);

    return 0;
}
