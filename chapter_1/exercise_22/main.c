#include <stdio.h>

#define COLUMN_LIMIT 80

int main(void) {
    int c, column;

    column = 0;
    while ((c = getchar()) != EOF) {
        if (column < COLUMN_LIMIT)
            putchar(c);
        else if (column == COLUMN_LIMIT && c != ' ' && c != '\t') {
            printf("%c\n", c);
            column = 0;
        } else {
            while ((c = getchar()) == ' ' || c == '\t')
                ;

            if (c != ' ' && c != '\t') {
                printf("\n%c", c);
                column = 1;
            }
        }

        ++column;
    }

    return 0;
}
