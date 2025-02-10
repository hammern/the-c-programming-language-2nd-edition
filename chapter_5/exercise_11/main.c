#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TAB 8

void entab(int);
void detab(int);

int main(int argc, char *argv[]) {
    int i;

    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            entab(atoi(argv[i]));
            detab(atoi(argv[i]));
        }
    } else {
        entab(DEFAULT_TAB);
        detab(DEFAULT_TAB);
    }

    return 0;
}

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
