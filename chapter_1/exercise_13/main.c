#include <stdio.h>

#define LONGEST_WORD_LENGTH 45

int main(void) {
    int c, i, j, current_word_length;
    int word_length_count[LONGEST_WORD_LENGTH + 1];

    for (i = 0; i < LONGEST_WORD_LENGTH + 1; ++i)
        word_length_count[i] = 0;

    current_word_length = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            ++word_length_count[current_word_length];
            current_word_length = 0;
        } else
            ++current_word_length;
    }

    for (i = 0; i < LONGEST_WORD_LENGTH + 1; ++i) {
        printf("%2d", i);

        for (j = 0; j < word_length_count[i]; ++j)
            putchar('*');

        putchar('\n');
    }

    return 0;
}
