#include <ctype.h>
#include <stdio.h>

#define LINEBREAK 80

int main(void) {
    int c, count;

    count = 0;
    while ((c = getchar()) != EOF) {
        if (count == LINEBREAK) {
            count = 0;
            putchar('\n');
        }

        if (isgraph(c) == 0)
            printf("0x%x", c);
        else
            putchar(c);

        count++;
    }

    putchar('\n');

    return 0;
}
