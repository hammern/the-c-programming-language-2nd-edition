#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TABSTOP 8
#define DEFAULT_COLUMN 1

void entab(int, int);
void detab(int, int);

int main(int argc, char *argv[]) {
    int tabstop, start_pos;

    if (argc <= 1) {
        tabstop = DEFAULT_TABSTOP;
        start_pos = DEFAULT_COLUMN;
    } else if (argc == 3 && *argv[1] == '-' && *argv[2] == '+') {
        start_pos = atoi(argv[1]);
        tabstop = atoi(argv[2]);
    } else if (argc == 2) {
        start_pos = atoi(argv[1]);
    }

    entab(tabstop, start_pos);
    detab(tabstop, start_pos);

    return 0;
}

void entab(int tabstop, int start_pos) {
    int c, i, blank_count;

    blank_count = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ')
            ++blank_count;
        else {
            if (blank_count < tabstop) {
                for (; blank_count > start_pos; --blank_count)
                    putchar(' ');
            } else {
                for (i = blank_count / tabstop; i > start_pos; --i)
                    putchar('\t');

                for (i = blank_count % tabstop; i > start_pos; --i)
                    putchar(' ');
            }

            blank_count = 0;
            putchar(c);
        }
    }
}

void detab(int tabstop, int start_pos) {
    int c, i;

    while ((c = getchar()) != EOF) {
        if (c == '\t')
            for (i = tabstop; i > start_pos; --i)
                putchar(' ');
        else
            putchar(c);
    }
}
