#include <stdio.h>

int main(void) {
    int c, blank_count, tab_count, newline_count;

    blank_count = 0;
    tab_count = 0;
    newline_count = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ')
            ++blank_count;
        if (c == '\t')
            ++tab_count;
        if (c == '\n')
            ++newline_count;
    }

    printf("blank count: %d\n", blank_count);
    printf("tab count: %d\n", tab_count);
    printf("newline count: %d\n", newline_count);

    return 0;
}
